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
typedef  int fp_except ;

/* Variables and functions */
 int FP_X_MASK ; 

fp_except
fpgetsticky(void)
{
	fp_except old;

	__asm __volatile("vmrs %0, fpscr" : "=&r"(old));

	return (old & FP_X_MASK);
}