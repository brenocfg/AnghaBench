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
struct TYPE_2__ {scalar_t__ autoneg; int tx_pause; int rx_pause; int /*<<< orphan*/  speed; int /*<<< orphan*/  lp_advertising; scalar_t__ pause_autoneg; } ;
struct xgbe_prv_data {int speed_set; TYPE_1__ phy; scalar_t__ parallel_detect; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADVERTISED_10000baseKR_Full ; 
 int /*<<< orphan*/  ADVERTISED_1000baseKX_Full ; 
 int /*<<< orphan*/  ADVERTISED_2500baseX_Full ; 
 int /*<<< orphan*/  ADVERTISED_Asym_Pause ; 
 int /*<<< orphan*/  ADVERTISED_Autoneg ; 
 int /*<<< orphan*/  ADVERTISED_Backplane ; 
 int /*<<< orphan*/  ADVERTISED_Pause ; 
 scalar_t__ AUTONEG_ENABLE ; 
 scalar_t__ MDIO_AN_ADVERTISE ; 
 scalar_t__ MDIO_AN_LPA ; 
 int /*<<< orphan*/  MDIO_MMD_AN ; 
 int /*<<< orphan*/  SPEED_1000 ; 
 int /*<<< orphan*/  SPEED_10000 ; 
 int /*<<< orphan*/  SPEED_2500 ; 
 int /*<<< orphan*/  SPEED_UNKNOWN ; 
 int /*<<< orphan*/  XGBE_MODE_KR ; 
 int /*<<< orphan*/  XGBE_MODE_KX ; 
#define  XGBE_SPEEDSET_1000_10000 129 
#define  XGBE_SPEEDSET_2500_10000 128 
 unsigned int XMDIO_READ (struct xgbe_prv_data*,int /*<<< orphan*/ ,scalar_t__) ; 
 void xgbe_phy_status_force (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_set_mode (struct xgbe_prv_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xgbe_phy_status_aneg(struct xgbe_prv_data *pdata)
{
	unsigned int ad_reg, lp_reg;

	pdata->phy.lp_advertising = 0;

	if ((pdata->phy.autoneg != AUTONEG_ENABLE) || pdata->parallel_detect)
		return xgbe_phy_status_force(pdata);

	pdata->phy.lp_advertising |= ADVERTISED_Autoneg;
	pdata->phy.lp_advertising |= ADVERTISED_Backplane;

	/* Compare Advertisement and Link Partner register 1 */
	ad_reg = XMDIO_READ(pdata, MDIO_MMD_AN, MDIO_AN_ADVERTISE);
	lp_reg = XMDIO_READ(pdata, MDIO_MMD_AN, MDIO_AN_LPA);
	if (lp_reg & 0x400)
		pdata->phy.lp_advertising |= ADVERTISED_Pause;
	if (lp_reg & 0x800)
		pdata->phy.lp_advertising |= ADVERTISED_Asym_Pause;

	if (pdata->phy.pause_autoneg) {
		/* Set flow control based on auto-negotiation result */
		pdata->phy.tx_pause = 0;
		pdata->phy.rx_pause = 0;

		if (ad_reg & lp_reg & 0x400) {
			pdata->phy.tx_pause = 1;
			pdata->phy.rx_pause = 1;
		} else if (ad_reg & lp_reg & 0x800) {
			if (ad_reg & 0x400)
				pdata->phy.rx_pause = 1;
			else if (lp_reg & 0x400)
				pdata->phy.tx_pause = 1;
		}
	}

	/* Compare Advertisement and Link Partner register 2 */
	ad_reg = XMDIO_READ(pdata, MDIO_MMD_AN, MDIO_AN_ADVERTISE + 1);
	lp_reg = XMDIO_READ(pdata, MDIO_MMD_AN, MDIO_AN_LPA + 1);
	if (lp_reg & 0x80)
		pdata->phy.lp_advertising |= ADVERTISED_10000baseKR_Full;
	if (lp_reg & 0x20) {
		switch (pdata->speed_set) {
		case XGBE_SPEEDSET_1000_10000:
			pdata->phy.lp_advertising |= ADVERTISED_1000baseKX_Full;
			break;
		case XGBE_SPEEDSET_2500_10000:
			pdata->phy.lp_advertising |= ADVERTISED_2500baseX_Full;
			break;
		}
	}

	ad_reg &= lp_reg;
	if (ad_reg & 0x80) {
		pdata->phy.speed = SPEED_10000;
		xgbe_set_mode(pdata, XGBE_MODE_KR);
	} else if (ad_reg & 0x20) {
		switch (pdata->speed_set) {
		case XGBE_SPEEDSET_1000_10000:
			pdata->phy.speed = SPEED_1000;
			break;

		case XGBE_SPEEDSET_2500_10000:
			pdata->phy.speed = SPEED_2500;
			break;
		}

		xgbe_set_mode(pdata, XGBE_MODE_KX);
	} else {
		pdata->phy.speed = SPEED_UNKNOWN;
	}

	/* Compare Advertisement and Link Partner register 3 */
	ad_reg = XMDIO_READ(pdata, MDIO_MMD_AN, MDIO_AN_ADVERTISE + 2);
	lp_reg = XMDIO_READ(pdata, MDIO_MMD_AN, MDIO_AN_LPA + 2);
}