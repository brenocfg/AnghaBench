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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct al_hal_eth_adapter {scalar_t__ mdio_if; scalar_t__ mdio_type; } ;

/* Variables and functions */
 scalar_t__ AL_ETH_MDIO_IF_1G_MAC ; 
 scalar_t__ AL_ETH_MDIO_TYPE_CLAUSE_22 ; 
 int /*<<< orphan*/  al_dbg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int al_eth_mdio_10g_mac_type22 (struct al_hal_eth_adapter*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int al_eth_mdio_10g_mac_type45 (struct al_hal_eth_adapter*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int al_eth_mdio_1g_mac_read (struct al_hal_eth_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  al_eth_mdio_free (struct al_hal_eth_adapter*) ; 
 int al_eth_mdio_lock (struct al_hal_eth_adapter*) ; 

int al_eth_mdio_read(struct al_hal_eth_adapter *adapter, uint32_t phy_addr, uint32_t device, uint32_t reg, uint16_t *val)
{
	int rc;
	rc = al_eth_mdio_lock(adapter);

	/*"interface ownership taken"*/
	if (rc)
		return rc;

	if (adapter->mdio_if == AL_ETH_MDIO_IF_1G_MAC)
		rc = al_eth_mdio_1g_mac_read(adapter, phy_addr, reg, val);
	else
		if (adapter->mdio_type == AL_ETH_MDIO_TYPE_CLAUSE_22)
			rc = al_eth_mdio_10g_mac_type22(adapter, 1, phy_addr, reg, val);
		else
			rc = al_eth_mdio_10g_mac_type45(adapter, 1, phy_addr, device, reg, val);

	al_eth_mdio_free(adapter);
	al_dbg("eth mdio read: phy_addr %x, device %x, reg %x val %x\n", phy_addr, device, reg, *val);
	return rc;
}