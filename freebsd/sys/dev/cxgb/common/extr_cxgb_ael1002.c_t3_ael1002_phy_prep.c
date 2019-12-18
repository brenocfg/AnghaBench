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
 int SUPPORTED_10000baseT_Full ; 
 int SUPPORTED_AUI ; 
 int SUPPORTED_FIBRE ; 
 int ael1002_get_module_type (struct cphy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ael1002_ops ; 
 int /*<<< orphan*/  ael100x_txon (struct cphy*) ; 
 int /*<<< orphan*/  ael_laser_down (struct cphy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cphy_init (struct cphy*,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ *,struct mdio_ops const*,int,char*) ; 

int t3_ael1002_phy_prep(pinfo_t *pinfo, int phy_addr,
			const struct mdio_ops *mdio_ops)
{
	int err;
	struct cphy *phy = &pinfo->phy;

	cphy_init(phy, pinfo->adapter, pinfo, phy_addr, &ael1002_ops, mdio_ops,
		  SUPPORTED_10000baseT_Full | SUPPORTED_AUI | SUPPORTED_FIBRE,
		  "10GBASE-R");
	ael100x_txon(phy);
	ael_laser_down(phy, 0);

	err = ael1002_get_module_type(phy, 0);
	if (err >= 0)
		phy->modtype = err;

	return 0;
}