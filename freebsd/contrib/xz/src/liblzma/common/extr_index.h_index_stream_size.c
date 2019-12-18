#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ lzma_vli ;

/* Variables and functions */
 scalar_t__ LZMA_STREAM_HEADER_SIZE ; 
 scalar_t__ index_size (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline lzma_vli
index_stream_size(lzma_vli blocks_size,
		lzma_vli count, lzma_vli index_list_size)
{
	return LZMA_STREAM_HEADER_SIZE + blocks_size
			+ index_size(count, index_list_size)
			+ LZMA_STREAM_HEADER_SIZE;
}