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
struct phynode_init_def {void* ofw_node; } ;
struct phynode {int dummy; } ;
struct awusb3phy_softc {int /*<<< orphan*/  reg; int /*<<< orphan*/  res; } ;
typedef  void* phandle_t ;
typedef  int /*<<< orphan*/  hwreset_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  clk_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  aw_usb3phy_spec ; 
 int /*<<< orphan*/  awusb3phy_phynode_class ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 scalar_t__ clk_get_by_ofw_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_get_name (int /*<<< orphan*/ ) ; 
 struct awusb3phy_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int hwreset_deassert (int /*<<< orphan*/ ) ; 
 scalar_t__ hwreset_get_by_ofw_idx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 void* ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 struct phynode* phynode_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct phynode_init_def*) ; 
 int /*<<< orphan*/ * phynode_register (struct phynode*) ; 
 int /*<<< orphan*/  regulator_get_by_ofw_property (int /*<<< orphan*/ ,void*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
awusb3phy_attach(device_t dev)
{
	struct phynode *phynode;
	struct phynode_init_def phy_init;
	struct awusb3phy_softc *sc;
	clk_t clk;
	hwreset_t rst;
	phandle_t node;
	int error, i;

	sc = device_get_softc(dev);
	node = ofw_bus_get_node(dev);

	if (bus_alloc_resources(dev, aw_usb3phy_spec, &sc->res) != 0) {
		device_printf(dev, "cannot allocate resources for device\n");
		return (ENXIO);
	}

	/* Enable clocks */
	for (i = 0; clk_get_by_ofw_index(dev, 0, i, &clk) == 0; i++) {
		error = clk_enable(clk);
		if (error != 0) {
			device_printf(dev, "couldn't enable clock %s\n",
			    clk_get_name(clk));
			return (error);
		}
	}

	/* De-assert resets */
	for (i = 0; hwreset_get_by_ofw_idx(dev, 0, i, &rst) == 0; i++) {
		error = hwreset_deassert(rst);
		if (error != 0) {
			device_printf(dev, "couldn't de-assert reset %d\n",
			    i);
			return (error);
		}
	}

	/* Get regulators */
	regulator_get_by_ofw_property(dev, node, "phy-supply", &sc->reg);

	/* Create the phy */
	phy_init.ofw_node = ofw_bus_get_node(dev);
	phynode = phynode_create(dev, &awusb3phy_phynode_class,
	    &phy_init);
	if (phynode == NULL) {
		device_printf(dev, "failed to create USB PHY\n");
		return (ENXIO);
	}
	if (phynode_register(phynode) == NULL) {
		device_printf(dev, "failed to create USB PHY\n");
		return (ENXIO);
	}

	return (error);
}