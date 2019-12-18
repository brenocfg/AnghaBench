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
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  lzma_ret ;

/* Variables and functions */
 int BUF_SIZE_MAX ; 
 int /*<<< orphan*/  LZMA_OK ; 
 int /*<<< orphan*/  LZMA_OPTIONS_ERROR ; 
 int LZMA_THREADS_MAX ; 

__attribute__((used)) static lzma_ret
get_options(uint64_t *bufs_alloc_size, uint32_t *bufs_count,
		uint64_t buf_size_max, uint32_t threads)
{
	if (threads > LZMA_THREADS_MAX || buf_size_max > BUF_SIZE_MAX)
		return LZMA_OPTIONS_ERROR;

	// The number of buffers is twice the number of threads.
	// This wastes RAM but keeps the threads busy when buffers
	// finish out of order.
	//
	// NOTE: If this is changed, update BUF_SIZE_MAX too.
	*bufs_count = threads * 2;
	*bufs_alloc_size = *bufs_count * buf_size_max;

	return LZMA_OK;
}