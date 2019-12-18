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
struct cphy {int /*<<< orphan*/  modtype; } ;
struct TYPE_4__ {int /*<<< orphan*/  adapter; struct cphy phy; } ;
typedef  TYPE_1__ pinfo_t ;

/* Variables and functions */
 int SUPPORTED_10000baseT_Full ; 
 int SUPPORTED_AUI ; 
 int SUPPORTED_FIBRE ; 
 int /*<<< orphan*/  ael1006_ops ; 
 int /*<<< orphan*/  ael100x_txon (struct cphy*) ; 
 int /*<<< orphan*/  cphy_init (struct cphy*,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ *,struct mdio_ops const*,int,char*) ; 
 int /*<<< orphan*/  phy_modtype_sr ; 

int t3_ael1006_phy_prep(pinfo_t *pinfo, int phy_addr,
			const struct mdio_ops *mdio_ops)
{
	struct cphy *phy = &pinfo->phy;

	cphy_init(phy, pinfo->adapter, pinfo, phy_addr, &ael1006_ops, mdio_ops,
		  SUPPORTED_10000baseT_Full | SUPPORTED_AUI | SUPPORTED_FIBRE,
		  "10GBASE-SR");
	phy->modtype = phy_modtype_sr;
	ael100x_txon(phy);
	return 0;
}