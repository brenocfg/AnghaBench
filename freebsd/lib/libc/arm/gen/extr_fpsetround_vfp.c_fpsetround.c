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
typedef  int uint32_t ;
typedef  int fp_rnd_t ;

/* Variables and functions */

fp_rnd_t
fpsetround(fp_rnd_t rnd_dir)
{
	uint32_t old, new;

	__asm __volatile("vmrs %0, fpscr" : "=&r"(old));
	new = old & ~(3 << 22);
	new |= rnd_dir << 22;
	__asm __volatile("vmsr fpscr, %0" : : "r"(new));

	return ((old >> 22) & 3);
}