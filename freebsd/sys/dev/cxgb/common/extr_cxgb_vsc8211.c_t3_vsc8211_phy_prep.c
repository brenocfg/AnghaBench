#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mdio_ops {int dummy; } ;
struct cphy {int caps; char* desc; int /*<<< orphan*/ * ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  adapter; struct cphy phy; } ;
typedef  TYPE_1__ pinfo_t ;

/* Variables and functions */
 int SUPPORTED_1000baseT_Full ; 
 int SUPPORTED_100baseT_Full ; 
 int SUPPORTED_10baseT_Full ; 
 int SUPPORTED_Autoneg ; 
 int SUPPORTED_FIBRE ; 
 int SUPPORTED_IRQ ; 
 int SUPPORTED_MII ; 
 int SUPPORTED_TP ; 
 int /*<<< orphan*/  VSC8211_EXT_CTRL ; 
 int /*<<< orphan*/  VSC8211_EXT_PAGE_AXS ; 
 int /*<<< orphan*/  VSC8211_LED_CTRL ; 
 int /*<<< orphan*/  VSC8211_SIGDET_CTRL ; 
 unsigned int VSC_CTRL_CLAUSE37_VIEW ; 
 unsigned int VSC_CTRL_MEDIA_MODE_HI ; 
 int /*<<< orphan*/  cphy_init (struct cphy*,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ *,struct mdio_ops const*,int,char*) ; 
 int mdio_read (struct cphy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int mdio_write (struct cphy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  vsc8211_fiber_ops ; 
 int /*<<< orphan*/  vsc8211_ops ; 
 int vsc8211_reset (struct cphy*,int /*<<< orphan*/ ) ; 

int t3_vsc8211_phy_prep(pinfo_t *pinfo, int phy_addr,
			const struct mdio_ops *mdio_ops)
{
	struct cphy *phy = &pinfo->phy;
	int err;
	unsigned int val;

	cphy_init(&pinfo->phy, pinfo->adapter, pinfo, phy_addr, &vsc8211_ops, mdio_ops,
		  SUPPORTED_10baseT_Full | SUPPORTED_100baseT_Full |
		  SUPPORTED_1000baseT_Full | SUPPORTED_Autoneg | SUPPORTED_MII |
		  SUPPORTED_TP | SUPPORTED_IRQ, "10/100/1000BASE-T");
	msleep(20);       /* PHY needs ~10ms to start responding to MDIO */

	err = mdio_read(phy, 0, VSC8211_EXT_CTRL, &val);
	if (err)
		return err;
	if (val & VSC_CTRL_MEDIA_MODE_HI) {
		/* copper interface, just need to configure the LEDs */
		return mdio_write(phy, 0, VSC8211_LED_CTRL, 0x100);
	}

	phy->caps = SUPPORTED_1000baseT_Full | SUPPORTED_Autoneg |
		    SUPPORTED_MII | SUPPORTED_FIBRE | SUPPORTED_IRQ;
	phy->desc = "1000BASE-X";
	phy->ops = &vsc8211_fiber_ops;

	if ((err = mdio_write(phy, 0, VSC8211_EXT_PAGE_AXS, 1)) != 0 ||
	    (err = mdio_write(phy, 0, VSC8211_SIGDET_CTRL, 1)) != 0 ||
	    (err = mdio_write(phy, 0, VSC8211_EXT_PAGE_AXS, 0)) != 0 ||
	    (err = mdio_write(phy, 0, VSC8211_EXT_CTRL,
			      val | VSC_CTRL_CLAUSE37_VIEW)) != 0 ||
	    (err = vsc8211_reset(phy, 0)) != 0)
		return err;

	udelay(5); /* delay after reset before next SMI */
	return 0;
}