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
struct cphy {int dummy; } ;
struct TYPE_4__ {struct cphy phy; int /*<<< orphan*/ * adapter; } ;
typedef  TYPE_1__ pinfo_t ;
typedef  int /*<<< orphan*/  adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  AQ_FW_VERSION ; 
 int /*<<< orphan*/  AQ_XAUI_KX_CFG ; 
 int /*<<< orphan*/  AQ_XAUI_RX_CFG ; 
 int /*<<< orphan*/  AQ_XAUI_TX_CFG ; 
 int /*<<< orphan*/  A_T3DBG_GPIO_EN ; 
 unsigned int BMCR_PDOWN ; 
 unsigned int BMCR_RESET ; 
 int /*<<< orphan*/  CH_WARN (int /*<<< orphan*/ *,char*,int,...) ; 
 unsigned int F_GPIO10_OUT_VAL ; 
 unsigned int F_GPIO6_OUT_VAL ; 
 int /*<<< orphan*/  MDIO_DEV_PMA_PMD ; 
 int /*<<< orphan*/  MDIO_DEV_VEND1 ; 
 int /*<<< orphan*/  MDIO_DEV_XGXS ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int SUPPORTED_10000baseT_Full ; 
 int SUPPORTED_1000baseT_Full ; 
 int SUPPORTED_AUI ; 
 int SUPPORTED_Autoneg ; 
 int SUPPORTED_MISC_IRQ ; 
 int SUPPORTED_TP ; 
 int /*<<< orphan*/  aq100x_ops ; 
 int /*<<< orphan*/  aq100x_set_defaults (struct cphy*) ; 
 int /*<<< orphan*/  cphy_init (struct cphy*,int /*<<< orphan*/ *,TYPE_1__*,int,int /*<<< orphan*/ *,struct mdio_ops const*,int,char*) ; 
 int mdio_read (struct cphy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  t3_set_reg_field (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

int
t3_aq100x_phy_prep(pinfo_t *pinfo, int phy_addr,
		       const struct mdio_ops *mdio_ops)
{
	struct cphy *phy = &pinfo->phy;
	unsigned int v, v2, gpio, wait;
	int err;
	adapter_t *adapter = pinfo->adapter;

	cphy_init(&pinfo->phy, adapter, pinfo, phy_addr, &aq100x_ops, mdio_ops,
		  SUPPORTED_1000baseT_Full | SUPPORTED_10000baseT_Full |
		  SUPPORTED_TP | SUPPORTED_Autoneg | SUPPORTED_AUI |
		  SUPPORTED_MISC_IRQ, "1000/10GBASE-T");

	/*
	 * Hard reset the PHY.
	 */
	gpio = phy_addr ? F_GPIO10_OUT_VAL : F_GPIO6_OUT_VAL;
	t3_set_reg_field(adapter, A_T3DBG_GPIO_EN, gpio, 0);
	msleep(1);
	t3_set_reg_field(adapter, A_T3DBG_GPIO_EN, gpio, gpio);

	/*
	 * Give it enough time to load the firmware and get ready for mdio.
	 */
	msleep(1000);
	wait = 500; /* in 10ms increments */
	do {
		err = mdio_read(phy, MDIO_DEV_PMA_PMD, MII_BMCR, &v);
		if (err || v == 0xffff) {

			/* Allow prep_adapter to succeed when ffff is read */

			CH_WARN(adapter, "PHY%d: reset failed (0x%x, 0x%x).\n",
				phy_addr, err, v);
			goto done;
		}

		v &= BMCR_RESET;
		if (v)
			msleep(10);
	} while (v && --wait);
	if (v) {
		CH_WARN(adapter, "PHY%d: reset timed out (0x%x).\n",
			phy_addr, v);

		goto done; /* let prep_adapter succeed */
	}

	/* Firmware version check. */
	(void) mdio_read(phy, MDIO_DEV_VEND1, AQ_FW_VERSION, &v);
	if (v < 0x115)
		CH_WARN(adapter, "PHY%d: unknown firmware %d.%d\n", phy_addr,
		    v >> 8, v & 0xff);

	/* The PHY should start in really-low-power mode. */
	(void) mdio_read(phy, MDIO_DEV_PMA_PMD, MII_BMCR, &v);
	if ((v & BMCR_PDOWN) == 0)
		CH_WARN(adapter, "PHY%d does not start in low power mode.\n",
			phy_addr);

	/*
	 * Verify XAUI and 1000-X settings, but let prep succeed no matter what.
	 */
	v = v2 = 0;
	(void) mdio_read(phy, MDIO_DEV_XGXS, AQ_XAUI_RX_CFG, &v);
	(void) mdio_read(phy, MDIO_DEV_XGXS, AQ_XAUI_TX_CFG, &v2);
	if (v != 0x1b || v2 != 0x1b)
		CH_WARN(adapter, "PHY%d: incorrect XAUI settings "
		    "(0x%x, 0x%x).\n", phy_addr, v, v2);
	v = 0;
	(void) mdio_read(phy, MDIO_DEV_XGXS, AQ_XAUI_KX_CFG, &v);
	if ((v & 0xf) != 0xf)
		CH_WARN(adapter, "PHY%d: incorrect 1000-X settings "
		    "(0x%x).\n", phy_addr, v);

	(void) aq100x_set_defaults(phy);
done:
	return (err);
}