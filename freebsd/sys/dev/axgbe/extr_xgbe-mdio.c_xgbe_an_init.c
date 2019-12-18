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
struct TYPE_2__ {int advertising; } ;
struct xgbe_prv_data {TYPE_1__ phy; } ;

/* Variables and functions */
 int ADVERTISED_10000baseKR_Full ; 
 int ADVERTISED_1000baseKX_Full ; 
 int ADVERTISED_2500baseX_Full ; 
 int ADVERTISED_Asym_Pause ; 
 int ADVERTISED_Pause ; 
 scalar_t__ MDIO_AN_ADVERTISE ; 
 int /*<<< orphan*/  MDIO_MMD_AN ; 
 unsigned int XGBE_XNP_NP_EXCHANGE ; 
 unsigned int XMDIO_READ (struct xgbe_prv_data*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  XMDIO_WRITE (struct xgbe_prv_data*,int /*<<< orphan*/ ,scalar_t__,unsigned int) ; 

__attribute__((used)) static void xgbe_an_init(struct xgbe_prv_data *pdata)
{
	unsigned int reg;

	/* Set up Advertisement register 3 first */
	reg = XMDIO_READ(pdata, MDIO_MMD_AN, MDIO_AN_ADVERTISE + 2);
	reg &= ~0xc000;

	XMDIO_WRITE(pdata, MDIO_MMD_AN, MDIO_AN_ADVERTISE + 2, reg);

	/* Set up Advertisement register 2 next */
	reg = XMDIO_READ(pdata, MDIO_MMD_AN, MDIO_AN_ADVERTISE + 1);
	if (pdata->phy.advertising & ADVERTISED_10000baseKR_Full)
		reg |= 0x80;
	else
		reg &= ~0x80;

	if ((pdata->phy.advertising & ADVERTISED_1000baseKX_Full) ||
	    (pdata->phy.advertising & ADVERTISED_2500baseX_Full))
		reg |= 0x20;
	else
		reg &= ~0x20;

	XMDIO_WRITE(pdata, MDIO_MMD_AN, MDIO_AN_ADVERTISE + 1, reg);

	/* Set up Advertisement register 1 last */
	reg = XMDIO_READ(pdata, MDIO_MMD_AN, MDIO_AN_ADVERTISE);
	if (pdata->phy.advertising & ADVERTISED_Pause)
		reg |= 0x400;
	else
		reg &= ~0x400;

	if (pdata->phy.advertising & ADVERTISED_Asym_Pause)
		reg |= 0x800;
	else
		reg &= ~0x800;

	/* We don't intend to perform XNP */
	reg &= ~XGBE_XNP_NP_EXCHANGE;

	XMDIO_WRITE(pdata, MDIO_MMD_AN, MDIO_AN_ADVERTISE, reg);
}