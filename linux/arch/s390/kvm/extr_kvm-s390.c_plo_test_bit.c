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

/* Variables and functions */

__attribute__((used)) static inline int plo_test_bit(unsigned char nr)
{
	register unsigned long r0 asm("0") = (unsigned long) nr | 0x100;
	int cc;

	asm volatile(
		/* Parameter registers are ignored for "test bit" */
		"	plo	0,0,0,0(0)\n"
		"	ipm	%0\n"
		"	srl	%0,28\n"
		: "=d" (cc)
		: "d" (r0)
		: "cc");
	return cc == 0;
}