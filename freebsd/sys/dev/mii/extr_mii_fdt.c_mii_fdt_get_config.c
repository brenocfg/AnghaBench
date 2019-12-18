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
typedef  int /*<<< orphan*/  val ;
typedef  int /*<<< orphan*/  pcell_t ;
struct TYPE_4__ {int macnode; int phynode; int /*<<< orphan*/  flags; int /*<<< orphan*/  max_speed; int /*<<< orphan*/  con_type; } ;
typedef  TYPE_1__ mii_fdt_phy_config_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  MIIF_FDT_BROKEN_TURNAROUND ; 
 int /*<<< orphan*/  MIIF_FDT_COMPAT_CLAUSE45 ; 
 int /*<<< orphan*/  MIIF_FDT_EEE_BROKEN_1000KX ; 
 int /*<<< orphan*/  MIIF_FDT_EEE_BROKEN_1000T ; 
 int /*<<< orphan*/  MIIF_FDT_EEE_BROKEN_100TX ; 
 int /*<<< orphan*/  MIIF_FDT_EEE_BROKEN_10GKR ; 
 int /*<<< orphan*/  MIIF_FDT_EEE_BROKEN_10GKX4 ; 
 int /*<<< orphan*/  MIIF_FDT_EEE_BROKEN_10GT ; 
 int /*<<< orphan*/  MIIF_FDT_LANE_SWAP ; 
 int /*<<< orphan*/  MIIF_FDT_NO_LANE_SWAP ; 
 int /*<<< orphan*/  M_OFWPROP ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 scalar_t__ OF_getencprop (int,char*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ OF_hasprop (int,char*) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 TYPE_1__* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mii_fdt_get_contype (int) ; 
 int mii_fdt_get_phynode (int) ; 
 int ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 scalar_t__ ofw_bus_node_is_compatible (int,char*) ; 

mii_fdt_phy_config_t *
mii_fdt_get_config(device_t phydev)
{
	mii_fdt_phy_config_t *cfg;
	device_t miibus, macdev;
	pcell_t val;

	miibus = device_get_parent(phydev);
	macdev = device_get_parent(miibus);

	cfg = malloc(sizeof(*cfg), M_OFWPROP, M_ZERO | M_WAITOK);

	/*
	 * If we can't find our parent MAC's node, there's nothing more we can
	 * fill in; cfg is already full of zero/default values, return it.
	 */
	if ((cfg->macnode = ofw_bus_get_node(macdev)) == -1)
		return (cfg);

	cfg->con_type = mii_fdt_get_contype(cfg->macnode);

	/*
	 * If we can't find our own PHY node, there's nothing more we can fill
	 * in, just return what we've got.
	 */
	if ((cfg->phynode = mii_fdt_get_phynode(cfg->macnode)) == -1)
		return (cfg);

	if (OF_getencprop(cfg->phynode, "max-speed", &val, sizeof(val)) > 0)
		cfg->max_speed = val;

	if (ofw_bus_node_is_compatible(cfg->phynode,
	    "ethernet-phy-ieee802.3-c45"))
		cfg->flags |= MIIF_FDT_COMPAT_CLAUSE45;

	if (OF_hasprop(cfg->phynode, "broken-turn-around"))
		cfg->flags |= MIIF_FDT_BROKEN_TURNAROUND;
	if (OF_hasprop(cfg->phynode, "enet-phy-lane-swap"))
		cfg->flags |= MIIF_FDT_LANE_SWAP;
	if (OF_hasprop(cfg->phynode, "enet-phy-lane-no-swap"))
		cfg->flags |= MIIF_FDT_NO_LANE_SWAP;
	if (OF_hasprop(cfg->phynode, "eee-broken-100tx"))
		cfg->flags |= MIIF_FDT_EEE_BROKEN_100TX;
	if (OF_hasprop(cfg->phynode, "eee-broken-1000t"))
		cfg->flags |= MIIF_FDT_EEE_BROKEN_1000T;
	if (OF_hasprop(cfg->phynode, "eee-broken-10gt"))
		cfg->flags |= MIIF_FDT_EEE_BROKEN_10GT;
	if (OF_hasprop(cfg->phynode, "eee-broken-1000kx"))
		cfg->flags |= MIIF_FDT_EEE_BROKEN_1000KX;
	if (OF_hasprop(cfg->phynode, "eee-broken-10gkx4"))
		cfg->flags |= MIIF_FDT_EEE_BROKEN_10GKX4;
	if (OF_hasprop(cfg->phynode, "eee-broken-10gkr"))
		cfg->flags |= MIIF_FDT_EEE_BROKEN_10GKR;

	return (cfg);
}