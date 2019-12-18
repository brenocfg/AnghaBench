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
typedef  int fp_rnd_t ;

/* Variables and functions */

fp_rnd_t
fpsetround(fp_rnd_t rnd_dir)
{
	fp_rnd_t old;
	fp_rnd_t new;

	__asm("cfc1 %0,$31" : "=r" (old));

	new = old;
	new &= ~0x03;
	new |= (rnd_dir & 0x03);

	__asm("ctc1 %0,$31" : : "r" (new));

	return old & 0x03;
}