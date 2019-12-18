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
struct xgbe_prv_data {int dummy; } ;
typedef  enum xgbe_rx { ____Placeholder_xgbe_rx } xgbe_rx ;
typedef  enum xgbe_an { ____Placeholder_xgbe_an } xgbe_an ;

/* Variables and functions */
 scalar_t__ MDIO_AN_ADVERTISE ; 
 scalar_t__ MDIO_AN_LPA ; 
 int /*<<< orphan*/  MDIO_MMD_AN ; 
 int XGBE_AN_INCOMPAT_LINK ; 
 unsigned int XGBE_XNP_NP_EXCHANGE ; 
 unsigned int XMDIO_READ (struct xgbe_prv_data*,int /*<<< orphan*/ ,scalar_t__) ; 
 int xgbe_an_tx_training (struct xgbe_prv_data*,int*) ; 
 int xgbe_an_tx_xnp (struct xgbe_prv_data*,int*) ; 
 scalar_t__ xgbe_in_kr_mode (struct xgbe_prv_data*) ; 

__attribute__((used)) static enum xgbe_an xgbe_an_rx_bpa(struct xgbe_prv_data *pdata,
				   enum xgbe_rx *state)
{
	unsigned int link_support;
	unsigned int reg, ad_reg, lp_reg;

	/* Read Base Ability register 2 first */
	reg = XMDIO_READ(pdata, MDIO_MMD_AN, MDIO_AN_LPA + 1);

	/* Check for a supported mode, otherwise restart in a different one */
	link_support = xgbe_in_kr_mode(pdata) ? 0x80 : 0x20;
	if (!(reg & link_support))
		return XGBE_AN_INCOMPAT_LINK;

	/* Check Extended Next Page support */
	ad_reg = XMDIO_READ(pdata, MDIO_MMD_AN, MDIO_AN_ADVERTISE);
	lp_reg = XMDIO_READ(pdata, MDIO_MMD_AN, MDIO_AN_LPA);

	return ((ad_reg & XGBE_XNP_NP_EXCHANGE) ||
		(lp_reg & XGBE_XNP_NP_EXCHANGE))
	       ? xgbe_an_tx_xnp(pdata, state)
	       : xgbe_an_tx_training(pdata, state);
}