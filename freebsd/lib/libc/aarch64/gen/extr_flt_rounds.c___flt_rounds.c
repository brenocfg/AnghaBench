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

/* Variables and functions */
 int* map ; 

int
__flt_rounds(void)
{
	uint64_t fpcr;

	asm volatile("mrs	%0, fpcr" : "=r" (fpcr));
	return map[(fpcr >> 22) & 3];
}