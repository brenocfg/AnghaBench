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

/* Variables and functions */
 int SCALE_SHIFT ; 
 size_t curcpu ; 
 int mftb () ; 
 int nsec_scale ; 
 int* timebase_skew ; 

uint64_t
dtrace_gethrtime()
{
	uint64_t timebase;
	uint32_t lo;
	uint32_t hi;

	/*
	 * We split timebase value into lower and higher 32-bit halves and separately
	 * scale them with nsec_scale, then we scale them down by 2^28
	 * (see nsec_scale calculations) taking into account 32-bit shift of
	 * the higher half and finally add.
	 */
	timebase = mftb() - timebase_skew[curcpu];
	lo = timebase;
	hi = timebase >> 32;
	return (((lo * nsec_scale) >> SCALE_SHIFT) +
	    ((hi * nsec_scale) << (32 - SCALE_SHIFT)));
}