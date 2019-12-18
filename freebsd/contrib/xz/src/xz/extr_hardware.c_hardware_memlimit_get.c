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
typedef  scalar_t__ uint64_t ;
typedef  enum operation_mode { ____Placeholder_operation_mode } operation_mode ;

/* Variables and functions */
 int MODE_COMPRESS ; 
 scalar_t__ UINT64_MAX ; 
 scalar_t__ memlimit_compress ; 
 scalar_t__ memlimit_decompress ; 

extern uint64_t
hardware_memlimit_get(enum operation_mode mode)
{
	// Zero is a special value that indicates the default. Currently
	// the default simply disables the limit. Once there is threading
	// support, this might be a little more complex, because there will
	// probably be a special case where a user asks for "optimal" number
	// of threads instead of a specific number (this might even become
	// the default mode). Each thread may use a significant amount of
	// memory. When there are no memory usage limits set, we need some
	// default soft limit for calculating the "optimal" number of
	// threads.
	const uint64_t memlimit = mode == MODE_COMPRESS
			? memlimit_compress : memlimit_decompress;
	return memlimit != 0 ? memlimit : UINT64_MAX;
}