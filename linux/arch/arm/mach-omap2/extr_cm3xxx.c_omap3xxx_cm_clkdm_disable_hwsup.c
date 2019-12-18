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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  s16 ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP34XX_CLKSTCTRL_DISABLE_AUTO ; 
 int /*<<< orphan*/  _write_clktrctrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap3xxx_cm_clkdm_disable_hwsup(s16 module, u32 mask)
{
	_write_clktrctrl(OMAP34XX_CLKSTCTRL_DISABLE_AUTO, module, mask);
}