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
 int /*<<< orphan*/  lv1_pause (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ps3_power_save(void)
{
	/*
	 * lv1_pause() puts the PPE thread into inactive state until an
	 * irq on an unmasked plug exists. MSR[EE] has no effect.
	 * flags: 0 = wake on DEC interrupt, 1 = ignore DEC interrupt.
	 */

	lv1_pause(0);
}