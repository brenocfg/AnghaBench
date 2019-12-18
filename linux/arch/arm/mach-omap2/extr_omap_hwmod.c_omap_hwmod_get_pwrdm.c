#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct powerdomain {int dummy; } ;
struct omap_hwmod_ocp_if {struct clk* _clk; } ;
struct omap_hwmod {struct clk* _clk; TYPE_3__* clkdm; } ;
struct TYPE_4__ {struct powerdomain* ptr; } ;
struct clockdomain {TYPE_1__ pwrdm; } ;
struct clk_hw_omap {struct clockdomain* clkdm; } ;
struct clk {int dummy; } ;
struct TYPE_5__ {struct powerdomain* ptr; } ;
struct TYPE_6__ {TYPE_2__ pwrdm; } ;

/* Variables and functions */
 int /*<<< orphan*/  __clk_get_hw (struct clk*) ; 
 struct omap_hwmod_ocp_if* _find_mpu_rt_port (struct omap_hwmod*) ; 
 struct clk_hw_omap* to_clk_hw_omap (int /*<<< orphan*/ ) ; 

struct powerdomain *omap_hwmod_get_pwrdm(struct omap_hwmod *oh)
{
	struct clk *c;
	struct omap_hwmod_ocp_if *oi;
	struct clockdomain *clkdm;
	struct clk_hw_omap *clk;

	if (!oh)
		return NULL;

	if (oh->clkdm)
		return oh->clkdm->pwrdm.ptr;

	if (oh->_clk) {
		c = oh->_clk;
	} else {
		oi = _find_mpu_rt_port(oh);
		if (!oi)
			return NULL;
		c = oi->_clk;
	}

	clk = to_clk_hw_omap(__clk_get_hw(c));
	clkdm = clk->clkdm;
	if (!clkdm)
		return NULL;

	return clkdm->pwrdm.ptr;
}