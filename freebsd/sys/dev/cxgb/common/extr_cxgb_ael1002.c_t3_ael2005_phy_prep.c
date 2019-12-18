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
struct cphy {int modtype; } ;
struct TYPE_4__ {int /*<<< orphan*/  adapter; struct cphy phy; } ;
typedef  TYPE_1__ pinfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  AEL_OPT_SETTINGS ; 
 int /*<<< orphan*/  MDIO_DEV_PMA_PMD ; 
 int SUPPORTED_10000baseT_Full ; 
 int SUPPORTED_AUI ; 
 int SUPPORTED_FIBRE ; 
 int SUPPORTED_IRQ ; 
 int ael2005_get_module_type (struct cphy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ael2005_ops ; 
 int /*<<< orphan*/  ael_laser_down (struct cphy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cphy_init (struct cphy*,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ *,struct mdio_ops const*,int,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int t3_mdio_change_bits (struct cphy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int t3_ael2005_phy_prep(pinfo_t *pinfo, int phy_addr,
			const struct mdio_ops *mdio_ops)
{
	int err;
	struct cphy *phy = &pinfo->phy;

	cphy_init(phy, pinfo->adapter, pinfo, phy_addr, &ael2005_ops, mdio_ops,
		  SUPPORTED_10000baseT_Full | SUPPORTED_AUI | SUPPORTED_FIBRE |
		  SUPPORTED_IRQ, "10GBASE-R");
	msleep(125);
	ael_laser_down(phy, 0);

	err = ael2005_get_module_type(phy, 0);
	if (err >= 0)
		phy->modtype = err;

	return t3_mdio_change_bits(phy, MDIO_DEV_PMA_PMD, AEL_OPT_SETTINGS, 0,
				   1 << 5);
}