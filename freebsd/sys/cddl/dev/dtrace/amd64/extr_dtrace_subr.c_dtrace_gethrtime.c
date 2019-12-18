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
typedef  int /*<<< orphan*/  register_t ;

/* Variables and functions */
 int SCALE_SHIFT ; 
 size_t curcpu ; 
 int /*<<< orphan*/  intr_disable () ; 
 int /*<<< orphan*/  intr_restore (int /*<<< orphan*/ ) ; 
 int nsec_scale ; 
 int rdtsc () ; 
 int* tsc_skew ; 

uint64_t
dtrace_gethrtime(void)
{
	uint64_t tsc;
	uint32_t lo, hi;
	register_t rflags;

	/*
	 * We split TSC value into lower and higher 32-bit halves and separately
	 * scale them with nsec_scale, then we scale them down by 2^28
	 * (see nsec_scale calculations) taking into account 32-bit shift of
	 * the higher half and finally add.
	 */
	rflags = intr_disable();
	tsc = rdtsc() - tsc_skew[curcpu];
	intr_restore(rflags);

	lo = tsc;
	hi = tsc >> 32;
	return (((lo * nsec_scale) >> SCALE_SHIFT) +
	    ((hi * nsec_scale) << (32 - SCALE_SHIFT)));
}