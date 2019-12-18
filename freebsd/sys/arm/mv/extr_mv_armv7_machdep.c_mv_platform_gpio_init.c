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
typedef  int /*<<< orphan*/  platform_t ;

/* Variables and functions */
 scalar_t__ platform_mpp_init () ; 

__attribute__((used)) static void
mv_platform_gpio_init(platform_t plate)
{

	/*
	 * Re-initialise MPP. It is important to call this prior to using
	 * console as the physical connection can be routed via MPP.
	 */
	if (platform_mpp_init() != 0)
		while (1);
}