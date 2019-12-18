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

void
platform_reset(void)
{

	/* XXX SMP will likely require us to do more. */
	__asm__ __volatile__(
		"mfc0 $k0, $12\n\t"
		"li $k1, 0x00100000\n\t"
		"or $k0, $k0, $k1\n\t"
		"mtc0 $k0, $12\n");
	for( ; ; )
		__asm__ __volatile("wait");
}