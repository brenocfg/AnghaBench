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
 int /*<<< orphan*/  cpu_is_omap16xx () ; 
 int /*<<< orphan*/  omap1_rng_device ; 
 int /*<<< orphan*/  platform_device_register (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void omap1_init_rng(void)
{
	if (!cpu_is_omap16xx())
		return;

	(void) platform_device_register(&omap1_rng_device);
}