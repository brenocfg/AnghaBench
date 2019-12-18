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
struct TYPE_2__ {scalar_t__ autoneg; int advertising; } ;
struct xgbe_prv_data {void* kx_state; void* kr_state; void* an_state; void* an_result; TYPE_1__ phy; int /*<<< orphan*/  link_check; int /*<<< orphan*/  dev_state; } ;

/* Variables and functions */
 int ADVERTISED_10000baseKR_Full ; 
 int ADVERTISED_1000baseKX_Full ; 
 int ADVERTISED_2500baseX_Full ; 
 scalar_t__ AUTONEG_ENABLE ; 
 int EINVAL ; 
 int /*<<< orphan*/  MDIO_AN_INT ; 
 int /*<<< orphan*/  MDIO_AN_INTMASK ; 
 int /*<<< orphan*/  MDIO_MMD_AN ; 
 void* XGBE_AN_READY ; 
 int /*<<< orphan*/  XGBE_LINK_INIT ; 
 int /*<<< orphan*/  XGBE_MODE_KR ; 
 int /*<<< orphan*/  XGBE_MODE_KX ; 
 void* XGBE_RX_BPA ; 
 int /*<<< orphan*/  XMDIO_WRITE (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ticks ; 
 int /*<<< orphan*/  xgbe_an_init (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_disable_an (struct xgbe_prv_data*) ; 
 int xgbe_phy_config_fixed (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_restart_an (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_set_mode (struct xgbe_prv_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __xgbe_phy_config_aneg(struct xgbe_prv_data *pdata)
{
	set_bit(XGBE_LINK_INIT, &pdata->dev_state);
	pdata->link_check = ticks;

	if (pdata->phy.autoneg != AUTONEG_ENABLE)
		return xgbe_phy_config_fixed(pdata);

	/* Disable auto-negotiation interrupt */
	XMDIO_WRITE(pdata, MDIO_MMD_AN, MDIO_AN_INTMASK, 0);

	/* Clear any auto-negotitation interrupts */
	XMDIO_WRITE(pdata, MDIO_MMD_AN, MDIO_AN_INT, 0);

	/* Start auto-negotiation in a supported mode */
	if (pdata->phy.advertising & ADVERTISED_10000baseKR_Full) {
		xgbe_set_mode(pdata, XGBE_MODE_KR);
	} else if ((pdata->phy.advertising & ADVERTISED_1000baseKX_Full) ||
		   (pdata->phy.advertising & ADVERTISED_2500baseX_Full)) {
		xgbe_set_mode(pdata, XGBE_MODE_KX);
	} else {
		XMDIO_WRITE(pdata, MDIO_MMD_AN, MDIO_AN_INTMASK, 0x07);
		return -EINVAL;
	}

	/* Disable and stop any in progress auto-negotiation */
	xgbe_disable_an(pdata);

	/* Clear any auto-negotitation interrupts */
	XMDIO_WRITE(pdata, MDIO_MMD_AN, MDIO_AN_INT, 0);

	pdata->an_result = XGBE_AN_READY;
	pdata->an_state = XGBE_AN_READY;
	pdata->kr_state = XGBE_RX_BPA;
	pdata->kx_state = XGBE_RX_BPA;

	/* Re-enable auto-negotiation interrupt */
	XMDIO_WRITE(pdata, MDIO_MMD_AN, MDIO_AN_INTMASK, 0x07);

	/* Set up advertisement registers based on current settings */
	xgbe_an_init(pdata);

	/* Enable and start auto-negotiation */
	xgbe_restart_an(pdata);

	return 0;
}