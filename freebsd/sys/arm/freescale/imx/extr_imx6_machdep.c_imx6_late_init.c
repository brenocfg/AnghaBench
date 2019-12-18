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
typedef  int /*<<< orphan*/  platform_t ;

/* Variables and functions */
 int /*<<< orphan*/  imx_wdog_init_last_reset (int const) ; 

__attribute__((used)) static void
imx6_late_init(platform_t plat)
{
	const uint32_t IMX6_WDOG_SR_PHYS = 0x020bc004;

	imx_wdog_init_last_reset(IMX6_WDOG_SR_PHYS);
}