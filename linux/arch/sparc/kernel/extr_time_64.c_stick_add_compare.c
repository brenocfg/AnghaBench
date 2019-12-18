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
 unsigned long TICKCMP_IRQ_BIT ; 

__attribute__((used)) static int stick_add_compare(unsigned long adj)
{
	unsigned long orig_tick, new_tick;

	__asm__ __volatile__("rd	%%asr24, %0"
			     : "=r" (orig_tick));
	orig_tick &= ~TICKCMP_IRQ_BIT;

	__asm__ __volatile__("wr	%0, 0, %%asr25"
			     : /* no outputs */
			     : "r" (orig_tick + adj));

	__asm__ __volatile__("rd	%%asr24, %0"
			     : "=r" (new_tick));
	new_tick &= ~TICKCMP_IRQ_BIT;

	return ((long)(new_tick - (orig_tick+adj))) > 0L;
}