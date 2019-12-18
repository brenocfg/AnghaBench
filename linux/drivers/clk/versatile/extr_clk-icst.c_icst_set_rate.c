#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct icst_vco {int dummy; } ;
struct clk_icst {scalar_t__ ctype; TYPE_1__* params; int /*<<< orphan*/  rate; int /*<<< orphan*/  lockreg_off; int /*<<< orphan*/  map; int /*<<< orphan*/  vcoreg_off; } ;
struct clk_hw {int dummy; } ;
struct TYPE_3__ {unsigned long ref; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ ICST_INTEGRATOR_AP_PCI ; 
 unsigned int INTEGRATOR_AP_PCI_25_33_MHZ ; 
 int /*<<< orphan*/  VERSATILE_LOCK_VAL ; 
 int /*<<< orphan*/  icst_hz (TYPE_1__*,struct icst_vco) ; 
 struct icst_vco icst_hz_to_vco (TYPE_1__*,unsigned long) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned long) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct clk_icst* to_icst (struct clk_hw*) ; 
 int vco_set (struct clk_icst*,struct icst_vco) ; 

__attribute__((used)) static int icst_set_rate(struct clk_hw *hw, unsigned long rate,
			 unsigned long parent_rate)
{
	struct clk_icst *icst = to_icst(hw);
	struct icst_vco vco;

	if (icst->ctype == ICST_INTEGRATOR_AP_PCI) {
		/* This clock is especially primitive */
		unsigned int val;
		int ret;

		if (rate == 25000000) {
			val = 0;
		} else if (rate == 33000000) {
			val = INTEGRATOR_AP_PCI_25_33_MHZ;
		} else {
			pr_err("ICST: cannot set PCI frequency %lu\n",
			       rate);
			return -EINVAL;
		}
		ret = regmap_write(icst->map, icst->lockreg_off,
				   VERSATILE_LOCK_VAL);
		if (ret)
			return ret;
		ret = regmap_update_bits(icst->map, icst->vcoreg_off,
					 INTEGRATOR_AP_PCI_25_33_MHZ,
					 val);
		if (ret)
			return ret;
		/* This locks the VCO again */
		ret = regmap_write(icst->map, icst->lockreg_off, 0);
		if (ret)
			return ret;
		return 0;
	}

	if (parent_rate)
		icst->params->ref = parent_rate;
	vco = icst_hz_to_vco(icst->params, rate);
	icst->rate = icst_hz(icst->params, vco);
	return vco_set(icst, vco);
}