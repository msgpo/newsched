/* -*- c++ -*- */
/*
 * Copyright 2004,2008,2010,2013,2018,2020 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#ifndef INCLUDED_VECTOR_SINK_HPP
#define INCLUDED_VECTOR_SINK_HPP

#include "sync_block.hpp"
#include <cstdint>
#include <mutex>
namespace gr {
namespace blocks {

template <class T>
class vector_sink : virtual public sync_block
{
private: 
    std::vector<T> d_data;
    std::vector<tag_t> d_tags;
    mutable std::mutex d_data_mutex; // protects internal data access.
    unsigned int d_vlen;

public:
    vector_sink(unsigned int vlen, const int reserve_items);
    ~vector_sink() = default;

    //! Clear the data and tags containers.
    virtual void reset() = 0;
    virtual const std::vector<T> data();
    virtual const std::vector<tag_t> tags();

    virtual work_return_code_t work(std::vector<block_work_input>& work_input,
                                    std::vector<block_work_output>& work_output);
};

typedef vector_sink<std::uint8_t> vector_sink_b;
typedef vector_sink<std::int16_t> vector_sink_s;
typedef vector_sink<std::int32_t> vector_sink_i;
typedef vector_sink<float> vector_sink_f;
typedef vector_sink<gr_complex> vector_sink_c;
} /* namespace blocks */
} /* namespace gr */

#endif