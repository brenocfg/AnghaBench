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
struct al_hal_eth_adapter {scalar_t__ rev_id; int /*<<< orphan*/  name; } ;
struct al_eth_an_adv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AL_ETH_AN_REGS ; 
 int /*<<< orphan*/  AL_ETH_AN__LT_LANE_0 ; 
 int /*<<< orphan*/  AL_ETH_KR_AN_STATUS ; 
 scalar_t__ AL_ETH_REV_ID_2 ; 
 int /*<<< orphan*/  al_dbg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  al_eth_an_lt_reg_read (struct al_hal_eth_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  al_eth_an_lt_unit_config (struct al_hal_eth_adapter*) ; 
 int al_eth_kr_an_validate_adv (struct al_hal_eth_adapter*,struct al_eth_an_adv*) ; 
 int al_eth_kr_an_write_adv (struct al_hal_eth_adapter*,struct al_eth_an_adv*) ; 

int al_eth_kr_an_init(struct al_hal_eth_adapter *adapter,
		      struct al_eth_an_adv *an_adv)
{
	int		rc;

	if (adapter->rev_id > AL_ETH_REV_ID_2)
		al_eth_an_lt_unit_config(adapter);

	rc = al_eth_kr_an_validate_adv(adapter, an_adv);
	if (rc)
		return rc;

	rc = al_eth_kr_an_write_adv(adapter, an_adv);
	if (rc)
		return rc;

	/* clear status */
	al_eth_an_lt_reg_read(adapter, AL_ETH_KR_AN_STATUS, AL_ETH_AN_REGS, AL_ETH_AN__LT_LANE_0);

	al_dbg("[%s]: autonegotiation initialized successfully", adapter->name);
	return 0;
}