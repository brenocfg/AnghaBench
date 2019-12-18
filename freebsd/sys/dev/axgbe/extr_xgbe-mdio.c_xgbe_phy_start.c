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
struct xgbe_prv_data {int /*<<< orphan*/  an_irq_tag; int /*<<< orphan*/  an_irq_res; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_NET ; 
 int /*<<< orphan*/  MDIO_AN_INTMASK ; 
 int /*<<< orphan*/  MDIO_MMD_AN ; 
 int /*<<< orphan*/  XMDIO_WRITE (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct xgbe_prv_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgbe_an_init (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_an_isr ; 
 int /*<<< orphan*/  xgbe_gmii_2500_mode (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_gmii_mode (struct xgbe_prv_data*) ; 
 int xgbe_phy_config_aneg (struct xgbe_prv_data*) ; 
 scalar_t__ xgbe_use_gmii_2500_mode (struct xgbe_prv_data*) ; 
 scalar_t__ xgbe_use_gmii_mode (struct xgbe_prv_data*) ; 
 scalar_t__ xgbe_use_xgmii_mode (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_xgmii_mode (struct xgbe_prv_data*) ; 

__attribute__((used)) static int xgbe_phy_start(struct xgbe_prv_data *pdata)
{
	int ret;

	ret = bus_setup_intr(pdata->dev, pdata->an_irq_res,
	    INTR_MPSAFE | INTR_TYPE_NET, NULL, xgbe_an_isr, pdata,
	    &pdata->an_irq_tag);
	if (ret) {
		return -ret;
	}

	/* Set initial mode - call the mode setting routines
	 * directly to insure we are properly configured
	 */
	if (xgbe_use_xgmii_mode(pdata)) {
		xgbe_xgmii_mode(pdata);
	} else if (xgbe_use_gmii_mode(pdata)) {
		xgbe_gmii_mode(pdata);
	} else if (xgbe_use_gmii_2500_mode(pdata)) {
		xgbe_gmii_2500_mode(pdata);
	} else {
		ret = -EINVAL;
		goto err_irq;
	}

	/* Set up advertisement registers based on current settings */
	xgbe_an_init(pdata);

	/* Enable auto-negotiation interrupts */
	XMDIO_WRITE(pdata, MDIO_MMD_AN, MDIO_AN_INTMASK, 0x07);

	return xgbe_phy_config_aneg(pdata);

err_irq:
	bus_teardown_intr(pdata->dev, pdata->an_irq_res, pdata->an_irq_tag);

	return ret;
}