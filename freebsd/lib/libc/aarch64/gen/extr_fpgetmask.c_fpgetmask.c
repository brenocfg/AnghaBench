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
typedef  int fp_except_t ;

/* Variables and functions */
 int FP_X_MASK ; 

fp_except_t
fpgetmask(void)
{
	uint64_t mask;

	/* Read the current mask */
	__asm __volatile("mrs %0, fpcr" : "=&r"(mask));

	return (mask & FP_X_MASK);
}