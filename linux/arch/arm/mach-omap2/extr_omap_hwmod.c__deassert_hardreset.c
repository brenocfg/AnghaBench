#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct omap_hwmod_rst_info {int dummy; } ;
struct omap_hwmod {TYPE_2__* clkdm; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
struct TYPE_6__ {int (* deassert_hardreset ) (struct omap_hwmod*,struct omap_hwmod_rst_info*) ;int /*<<< orphan*/  (* disable_module ) (struct omap_hwmod*) ;int /*<<< orphan*/  (* enable_module ) (struct omap_hwmod*) ;} ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOSYS ; 
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _disable_clocks (struct omap_hwmod*) ; 
 int /*<<< orphan*/  _enable_clocks (struct omap_hwmod*) ; 
 int _lookup_hardreset (struct omap_hwmod*,char const*,struct omap_hwmod_rst_info*) ; 
 int /*<<< orphan*/  clkdm_allow_idle (TYPE_2__*) ; 
 int /*<<< orphan*/  clkdm_deny_idle (TYPE_2__*) ; 
 int /*<<< orphan*/  clkdm_hwmod_disable (TYPE_2__*,struct omap_hwmod*) ; 
 int clkdm_hwmod_enable (TYPE_2__*,struct omap_hwmod*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__ soc_ops ; 
 int /*<<< orphan*/  stub1 (struct omap_hwmod*) ; 
 int stub2 (struct omap_hwmod*,struct omap_hwmod_rst_info*) ; 
 int /*<<< orphan*/  stub3 (struct omap_hwmod*) ; 

__attribute__((used)) static int _deassert_hardreset(struct omap_hwmod *oh, const char *name)
{
	struct omap_hwmod_rst_info ohri;
	int ret = -EINVAL;

	if (!oh)
		return -EINVAL;

	if (!soc_ops.deassert_hardreset)
		return -ENOSYS;

	ret = _lookup_hardreset(oh, name, &ohri);
	if (ret < 0)
		return ret;

	if (oh->clkdm) {
		/*
		 * A clockdomain must be in SW_SUP otherwise reset
		 * might not be completed. The clockdomain can be set
		 * in HW_AUTO only when the module become ready.
		 */
		clkdm_deny_idle(oh->clkdm);
		ret = clkdm_hwmod_enable(oh->clkdm, oh);
		if (ret) {
			WARN(1, "omap_hwmod: %s: could not enable clockdomain %s: %d\n",
			     oh->name, oh->clkdm->name, ret);
			return ret;
		}
	}

	_enable_clocks(oh);
	if (soc_ops.enable_module)
		soc_ops.enable_module(oh);

	ret = soc_ops.deassert_hardreset(oh, &ohri);

	if (soc_ops.disable_module)
		soc_ops.disable_module(oh);
	_disable_clocks(oh);

	if (ret == -EBUSY)
		pr_warn("omap_hwmod: %s: failed to hardreset\n", oh->name);

	if (oh->clkdm) {
		/*
		 * Set the clockdomain to HW_AUTO, assuming that the
		 * previous state was HW_AUTO.
		 */
		clkdm_allow_idle(oh->clkdm);

		clkdm_hwmod_disable(oh->clkdm, oh);
	}

	return ret;
}