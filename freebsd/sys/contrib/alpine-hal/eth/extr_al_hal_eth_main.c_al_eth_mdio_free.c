#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct al_hal_eth_adapter {scalar_t__ shared_mdio_if; TYPE_2__* mac_regs_base; } ;
struct TYPE_3__ {int /*<<< orphan*/  mdio_ctrl_1; } ;
struct TYPE_4__ {TYPE_1__ gen; } ;

/* Variables and functions */
 int AL_ETH_MDIO_DELAY_PERIOD ; 
 scalar_t__ AL_FALSE ; 
 int /*<<< orphan*/  al_reg_write32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  al_udelay (int) ; 

__attribute__((used)) static int al_eth_mdio_free(struct al_hal_eth_adapter *adapter)
{
	if (adapter->shared_mdio_if == AL_FALSE)
		return 0; /* nothing to do when interface is not shared */

	al_reg_write32(&adapter->mac_regs_base->gen.mdio_ctrl_1, 0);

	/*
	 * Addressing RMN: 2917
	 *
	 * RMN description:
	 * The HW spin-lock is stateless and doesn't maintain any scheduling
	 * policy.
	 *
	 * Software flow:
	 * After getting the lock wait 2 times the delay period in order to give
	 * the other port chance to take the lock and prevent starvation.
	 * This is not scalable to more than two ports.
	 */
	al_udelay(2 * AL_ETH_MDIO_DELAY_PERIOD);

	return 0;
}