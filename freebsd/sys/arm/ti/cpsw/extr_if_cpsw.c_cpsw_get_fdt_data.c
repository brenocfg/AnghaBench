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
struct cpsw_softc {TYPE_1__* port; int /*<<< orphan*/  node; } ;
typedef  scalar_t__ phandle_t ;
typedef  int pcell_t ;
struct TYPE_2__ {int phy; int vlan; } ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ OF_child (int /*<<< orphan*/ ) ; 
 scalar_t__ OF_getencprop (scalar_t__,char*,int*,int) ; 
 scalar_t__ OF_getprop_alloc (scalar_t__,char*,void**) ; 
 int OF_getproplen (scalar_t__,char*) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 int /*<<< orphan*/  OF_prop_free (char*) ; 
 scalar_t__ fdt_get_phyaddr (scalar_t__,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 unsigned long* slave_mdio_addr ; 
 int sscanf (char*,char*,unsigned long*) ; 

__attribute__((used)) static int
cpsw_get_fdt_data(struct cpsw_softc *sc, int port)
{
	char *name;
	int len, phy, vlan;
	pcell_t phy_id[3], vlan_id;
	phandle_t child;
	unsigned long mdio_child_addr;

	/* Find any slave with phy-handle/phy_id */
	phy = -1;
	vlan = -1;
	for (child = OF_child(sc->node); child != 0; child = OF_peer(child)) {
		if (OF_getprop_alloc(child, "name", (void **)&name) < 0)
			continue;
		if (sscanf(name, "slave@%lx", &mdio_child_addr) != 1) {
			OF_prop_free(name);
			continue;
		}
		OF_prop_free(name);

		if (mdio_child_addr != slave_mdio_addr[port] &&
		    mdio_child_addr != (slave_mdio_addr[port] & 0xFFF))
			continue;

		if (fdt_get_phyaddr(child, NULL, &phy, NULL) != 0){
			/* Users with old DTB will have phy_id instead */
			phy = -1;
			len = OF_getproplen(child, "phy_id");
			if (len / sizeof(pcell_t) == 2) {
				/* Get phy address from fdt */
				if (OF_getencprop(child, "phy_id", phy_id, len) > 0)
					phy = phy_id[1];
			}
		}

		len = OF_getproplen(child, "dual_emac_res_vlan");
		if (len / sizeof(pcell_t) == 1) {
			/* Get phy address from fdt */
			if (OF_getencprop(child, "dual_emac_res_vlan",
			    &vlan_id, len) > 0) {
				vlan = vlan_id;
			}
		}

		break;
	}
	if (phy == -1)
		return (ENXIO);
	sc->port[port].phy = phy;
	sc->port[port].vlan = vlan;

	return (0);
}