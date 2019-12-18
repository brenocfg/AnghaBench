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
struct TYPE_4__ {int /*<<< orphan*/  adapter; int /*<<< orphan*/  phy; } ;
typedef  TYPE_1__ pinfo_t ;

/* Variables and functions */
 int SUPPORTED_10000baseT_Full ; 
 int SUPPORTED_AUI ; 
 int SUPPORTED_TP ; 
 int /*<<< orphan*/  cphy_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ *,struct mdio_ops const*,int,char*) ; 
 int /*<<< orphan*/  xaui_direct_ops ; 

int t3_xaui_direct_phy_prep(pinfo_t *pinfo, int phy_addr,
			    const struct mdio_ops *mdio_ops)
{
	cphy_init(&pinfo->phy, pinfo->adapter, pinfo, phy_addr, &xaui_direct_ops, mdio_ops,
		  SUPPORTED_10000baseT_Full | SUPPORTED_AUI | SUPPORTED_TP,
		  "10GBASE-CX4");
	return 0;
}