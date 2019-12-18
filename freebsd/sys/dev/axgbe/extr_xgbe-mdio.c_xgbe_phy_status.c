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
struct TYPE_2__ {int link; scalar_t__ autoneg; } ;
struct xgbe_prv_data {int /*<<< orphan*/  dev_state; TYPE_1__ phy; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 int /*<<< orphan*/  MDIO_MMD_PCS ; 
 int /*<<< orphan*/  MDIO_STAT1 ; 
 unsigned int MDIO_STAT1_LSTATUS ; 
 int /*<<< orphan*/  XGBE_LINK_ERR ; 
 int /*<<< orphan*/  XGBE_LINK_INIT ; 
 unsigned int XMDIO_READ (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xgbe_check_link_timeout (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_phy_adjust_link (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_phy_aneg_done (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_phy_status_aneg (struct xgbe_prv_data*) ; 

__attribute__((used)) static void xgbe_phy_status(struct xgbe_prv_data *pdata)
{
	unsigned int reg, link_aneg;

	if (test_bit(XGBE_LINK_ERR, &pdata->dev_state)) {
		pdata->phy.link = 0;
		goto adjust_link;
	}

	link_aneg = (pdata->phy.autoneg == AUTONEG_ENABLE);

	/* Get the link status. Link status is latched low, so read
	 * once to clear and then read again to get current state
	 */
	reg = XMDIO_READ(pdata, MDIO_MMD_PCS, MDIO_STAT1);
	reg = XMDIO_READ(pdata, MDIO_MMD_PCS, MDIO_STAT1);
	pdata->phy.link = (reg & MDIO_STAT1_LSTATUS) ? 1 : 0;

	if (pdata->phy.link) {
		if (link_aneg && !xgbe_phy_aneg_done(pdata)) {
			xgbe_check_link_timeout(pdata);
			return;
		}

		xgbe_phy_status_aneg(pdata);

		if (test_bit(XGBE_LINK_INIT, &pdata->dev_state))
			clear_bit(XGBE_LINK_INIT, &pdata->dev_state);
	} else {
		if (test_bit(XGBE_LINK_INIT, &pdata->dev_state)) {
			xgbe_check_link_timeout(pdata);

			if (link_aneg)
				return;
		}

		xgbe_phy_status_aneg(pdata);
	}

adjust_link:
	xgbe_phy_adjust_link(pdata);
}