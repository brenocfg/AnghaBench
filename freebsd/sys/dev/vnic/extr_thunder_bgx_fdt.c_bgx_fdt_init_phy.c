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
typedef  size_t uint8_t ;
struct bgx {int /*<<< orphan*/  dev; TYPE_1__* lmac; int /*<<< orphan*/  bgx_id; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  qlm_mode ;
typedef  int /*<<< orphan*/  phy ;
typedef  scalar_t__ phandle_t ;
struct TYPE_2__ {scalar_t__ phyaddr; size_t lmacid; int /*<<< orphan*/  mac; int /*<<< orphan*/ * phy_if_dev; } ;

/* Variables and functions */
 int CONN_TYPE_MAXLEN ; 
 int ENXIO ; 
 size_t MAX_LMAC_PER_BGX ; 
 scalar_t__ MII_PHY_ANY ; 
 int /*<<< orphan*/  M_OFWPROP ; 
 scalar_t__ OF_child (scalar_t__) ; 
 int /*<<< orphan*/ * OF_device_from_xref (int /*<<< orphan*/ ) ; 
 scalar_t__ OF_getencprop (scalar_t__,char*,scalar_t__*,int) ; 
 scalar_t__ OF_getprop (scalar_t__,char*,char*,int) ; 
 scalar_t__ OF_getprop_alloc (scalar_t__,char*,void**) ; 
 scalar_t__ OF_instance_to_package (scalar_t__) ; 
 scalar_t__ OF_parent (scalar_t__) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 int /*<<< orphan*/  OF_xref_from_node (scalar_t__) ; 
 scalar_t__ bgx_fdt_find_node (struct bgx*) ; 
 int /*<<< orphan*/  bgx_fdt_get_macaddr (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bgx_fdt_phy_mode_match (struct bgx*,char*,scalar_t__) ; 
 int /*<<< orphan*/  bgx_fdt_phy_name_match (struct bgx*,char*,scalar_t__) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 

int
bgx_fdt_init_phy(struct bgx *bgx)
{
	char *node_name;
	phandle_t node, child;
	phandle_t phy, mdio;
	ssize_t len;
	uint8_t lmac;
	char qlm_mode[CONN_TYPE_MAXLEN];

	node = bgx_fdt_find_node(bgx);
	if (node == 0) {
		device_printf(bgx->dev,
		    "Could not find bgx%d node in FDT\n", bgx->bgx_id);
		return (ENXIO);
	}

	lmac = 0;
	for (child = OF_child(node); child > 0; child = OF_peer(child)) {
		len = OF_getprop(child, "qlm-mode", qlm_mode, sizeof(qlm_mode));
		if (len > 0) {
			if (!bgx_fdt_phy_mode_match(bgx, qlm_mode, len)) {
				/*
				 * Connection type not match with BGX mode.
				 */
				continue;
			}
		} else {
			len = OF_getprop_alloc(child, "name",
			    (void **)&node_name);
			if (len <= 0) {
				continue;
			}

			if (!bgx_fdt_phy_name_match(bgx, node_name, len)) {
				free(node_name, M_OFWPROP);
				continue;
			}
			free(node_name, M_OFWPROP);
		}

		/* Acquire PHY address */
		if (OF_getencprop(child, "reg", &bgx->lmac[lmac].phyaddr,
		    sizeof(bgx->lmac[lmac].phyaddr)) <= 0) {
			if (bootverbose) {
				device_printf(bgx->dev,
				    "Could not retrieve PHY address\n");
			}
			bgx->lmac[lmac].phyaddr = MII_PHY_ANY;
		}

		if (OF_getencprop(child, "phy-handle", &phy,
		    sizeof(phy)) <= 0) {
			if (bootverbose) {
				device_printf(bgx->dev,
				    "No phy-handle in PHY node. Skipping...\n");
			}
			continue;
		}
		phy = OF_instance_to_package(phy);
		/*
		 * Get PHY interface (MDIO bus) device.
		 * Driver must be already attached.
		 */
		mdio = OF_parent(phy);
		bgx->lmac[lmac].phy_if_dev =
		    OF_device_from_xref(OF_xref_from_node(mdio));
		if (bgx->lmac[lmac].phy_if_dev == NULL) {
			if (bootverbose) {
				device_printf(bgx->dev,
				    "Could not find interface to PHY\n");
			}
			continue;
		}

		/* Get mac address from FDT */
		bgx_fdt_get_macaddr(child, bgx->lmac[lmac].mac);

		bgx->lmac[lmac].lmacid = lmac;
		lmac++;
		if (lmac == MAX_LMAC_PER_BGX)
			break;
	}
	if (lmac == 0) {
		device_printf(bgx->dev, "Could not find matching PHY\n");
		return (ENXIO);
	}

	return (0);
}