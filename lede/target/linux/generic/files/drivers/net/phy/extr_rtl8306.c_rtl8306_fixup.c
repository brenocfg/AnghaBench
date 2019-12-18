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
typedef  int u16 ;
struct rtl_priv {int fixup; int page; int /*<<< orphan*/  dev; int /*<<< orphan*/  bus; } ;
struct TYPE_2__ {int addr; int /*<<< orphan*/  bus; } ;
struct phy_device {int /*<<< orphan*/  phy_id; TYPE_1__ mdio; } ;
typedef  int /*<<< orphan*/  priv ;

/* Variables and functions */
 int /*<<< orphan*/  RTL8306_MAGIC ; 
 int /*<<< orphan*/  RTL_REG_CHIPID ; 
 int /*<<< orphan*/  memset (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 
 int rtl_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rtl8306_fixup(struct phy_device *pdev)
{
	struct rtl_priv priv;
	u16 chipid;

	/* Attach to primary LAN port and WAN port */
	if (pdev->mdio.addr != 0 && pdev->mdio.addr != 4)
		return 0;

	memset(&priv, 0, sizeof(priv));
	priv.fixup = true;
	priv.page = -1;
	priv.bus = pdev->mdio.bus;
	chipid = rtl_get(&priv.dev, RTL_REG_CHIPID);
	if (chipid == 0x5988)
		pdev->phy_id = RTL8306_MAGIC;

	return 0;
}