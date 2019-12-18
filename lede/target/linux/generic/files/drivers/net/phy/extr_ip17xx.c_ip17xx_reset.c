#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct switch_dev {int dummy; } ;
struct ip17xx_state {TYPE_1__* regs; scalar_t__ vlan_enabled; scalar_t__ router_mode; } ;
struct TYPE_2__ {int NUM_PORTS; int (* reset ) (struct ip17xx_state*) ;int /*<<< orphan*/  RESET_REG; int /*<<< orphan*/  RESET_VAL; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMCR_RESET ; 
 int /*<<< orphan*/  MII_BMCR ; 
 scalar_t__ REG_SUPP (int /*<<< orphan*/ ) ; 
 int getPhy (struct ip17xx_state*,int /*<<< orphan*/ ) ; 
 struct ip17xx_state* get_state (struct switch_dev*) ; 
 int /*<<< orphan*/  ip17xx_reset_vlan_config (struct ip17xx_state*) ; 
 int ip_phy_write (struct ip17xx_state*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int setPhy (struct ip17xx_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct ip17xx_state*) ; 

__attribute__((used)) static int ip17xx_reset(struct switch_dev *dev)
{
	struct ip17xx_state *state = get_state(dev);
	int i, err;

	if (REG_SUPP(state->regs->RESET_REG)) {
		err = setPhy(state, state->regs->RESET_REG, state->regs->RESET_VAL);
		if (err < 0)
			return err;
		err = getPhy(state, state->regs->RESET_REG);

		/*
		 *  Data sheet specifies reset period to be 2 msec.
		 *  (I don't see any mention of the 2ms delay in the IP178C spec, only
		 *  in IP175C, but it can't hurt.)
		 */
		mdelay(2);
	}

	/* reset switch ports */
	for (i = 0; i < state->regs->NUM_PORTS-1; i++) {
		err = ip_phy_write(state, i, MII_BMCR, BMCR_RESET);
		if (err < 0)
			return err;
	}

	state->router_mode = 0;
	state->vlan_enabled = 0;
	ip17xx_reset_vlan_config(state);

	return state->regs->reset(state);
}