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
typedef  void* u32 ;

/* Variables and functions */

__attribute__((used)) static void omap34xx_save_context(u32 *save)
{
	u32 val;

	/* Read Auxiliary Control Register */
	asm("mrc p15, 0, %0, c1, c0, 1" : "=r" (val));
	*save++ = 1;
	*save++ = val;

	/* Read L2 AUX ctrl register */
	asm("mrc p15, 1, %0, c9, c0, 2" : "=r" (val));
	*save++ = 1;
	*save++ = val;
}