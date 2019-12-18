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
struct TYPE_2__ {unsigned int addn_mac; } ;
struct xgbe_prv_data {int /*<<< orphan*/ * mac_addr; TYPE_1__ hw_feat; } ;

/* Variables and functions */
 unsigned int MAC_MACA1HR ; 
 int /*<<< orphan*/  xgbe_set_mac_reg (struct xgbe_prv_data*,int /*<<< orphan*/ *,unsigned int*) ; 

__attribute__((used)) static void xgbe_set_mac_addn_addrs(struct xgbe_prv_data *pdata)
{
	unsigned int mac_reg;
	unsigned int addn_macs;

	mac_reg = MAC_MACA1HR;
	addn_macs = pdata->hw_feat.addn_mac;

	xgbe_set_mac_reg(pdata, pdata->mac_addr, &mac_reg);
	addn_macs--;

	/* Clear remaining additional MAC address entries */
	while (addn_macs--)
		xgbe_set_mac_reg(pdata, NULL, &mac_reg);
}