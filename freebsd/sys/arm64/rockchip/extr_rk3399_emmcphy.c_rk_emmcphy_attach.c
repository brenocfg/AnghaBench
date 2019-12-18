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
struct rk_emmcphy_softc {int /*<<< orphan*/ * syscon; } ;
struct phynode_init_def {void* ofw_node; scalar_t__ id; } ;
struct phynode {int dummy; } ;
typedef  int /*<<< orphan*/  phy_init ;
typedef  void* phandle_t ;
typedef  int /*<<< orphan*/  pcell_t ;
typedef  int /*<<< orphan*/  handle ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ OF_getencprop (void*,char*,void*,int) ; 
 scalar_t__ OF_hasprop (void*,char*) ; 
 void* OF_node_from_xref (int /*<<< orphan*/ ) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  bzero (struct phynode_init_def*,int) ; 
 struct rk_emmcphy_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 void* ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 struct phynode* phynode_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct phynode_init_def*) ; 
 intptr_t phynode_get_id (struct phynode*) ; 
 int /*<<< orphan*/ * phynode_register (struct phynode*) ; 
 int /*<<< orphan*/  rk_emmcphy_phynode_class ; 
 scalar_t__ syscon_get_by_ofw_property (int /*<<< orphan*/ ,void*,char*,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int
rk_emmcphy_attach(device_t dev)
{
	struct phynode_init_def phy_init;
	struct phynode *phynode;
	struct rk_emmcphy_softc *sc;
	phandle_t node;
	phandle_t xnode;
	pcell_t handle;
	intptr_t phy;

	sc = device_get_softc(dev);
	node = ofw_bus_get_node(dev);

	if (OF_getencprop(node, "clocks", (void *)&handle,
	    sizeof(handle)) <= 0) {
		device_printf(dev, "cannot get clocks handle\n");
		return (ENXIO);
	}
	xnode = OF_node_from_xref(handle);
	if (OF_hasprop(xnode, "arasan,soc-ctl-syscon") &&
	    syscon_get_by_ofw_property(dev, xnode,
	    "arasan,soc-ctl-syscon", &sc->syscon) != 0) {
		device_printf(dev, "cannot get grf driver handle\n");
		return (ENXIO);
	}

	if (sc->syscon == NULL) {
		device_printf(dev, "failed to get syscon\n");
		return (ENXIO);
	}

	/* Create and register phy */
	bzero(&phy_init, sizeof(phy_init));
	phy_init.id = 0;
	phy_init.ofw_node = ofw_bus_get_node(dev);
	phynode = phynode_create(dev, &rk_emmcphy_phynode_class, &phy_init);
	if (phynode == NULL) {
		device_printf(dev, "failed to create eMMC PHY\n");
		return (ENXIO);
	}
	if (phynode_register(phynode) == NULL) {
		device_printf(dev, "failed to register eMMC PHY\n");
		return (ENXIO);
	}
	if (bootverbose) {
		phy = phynode_get_id(phynode);
		device_printf(dev, "Attached phy id: %ld\n", phy);
	}
	return (0);
}