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
struct simplebus_devinfo {int /*<<< orphan*/  rl; } ;
struct resource_list_entry {int end; int /*<<< orphan*/  start; } ;
struct resource_list {int dummy; } ;
struct jz4780_pinctrl_softc {int /*<<< orphan*/ * dev; } ;
typedef  scalar_t__ phandle_t ;
typedef  int /*<<< orphan*/ * device_t ;
typedef  int bus_size_t ;
typedef  int bus_addr_t ;

/* Variables and functions */
 struct resource_list* BUS_GET_RESOURCE_LIST (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int CHIP_REG_OFFSET (int /*<<< orphan*/ ,int) ; 
 int CHIP_REG_STRIDE ; 
 int ENXIO ; 
 scalar_t__ OF_child (scalar_t__) ; 
 int /*<<< orphan*/  OF_hasprop (scalar_t__,char*) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int bus_generic_attach (int /*<<< orphan*/ *) ; 
 struct simplebus_devinfo* device_get_ivars (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ *) ; 
 struct jz4780_pinctrl_softc* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fdt_pinctrl_configure_tree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fdt_pinctrl_register (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ ofw_bus_get_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resource_list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 struct resource_list_entry* resource_list_find (struct resource_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * simplebus_add_device (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simplebus_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
jz4780_pinctrl_attach(device_t dev)
{
	struct jz4780_pinctrl_softc *sc;
	struct resource_list *rs;
	struct resource_list_entry *re;
	phandle_t dt_parent, dt_child;
	int i, ret;

	sc = device_get_softc(dev);
	sc->dev = dev;

	/*
	 * Fetch our own resource list to dole memory between children
	 */
	rs = BUS_GET_RESOURCE_LIST(device_get_parent(dev), dev);
	if (rs == NULL)
		return (ENXIO);
	re = resource_list_find(rs, SYS_RES_MEMORY, 0);
	if (re == NULL)
		return (ENXIO);

	simplebus_init(dev, 0);

	/* Iterate over this node children, looking for pin controllers */
	dt_parent = ofw_bus_get_node(dev);
	i = 0;
	for (dt_child = OF_child(dt_parent); dt_child != 0;
	    dt_child = OF_peer(dt_child)) {
		struct simplebus_devinfo *ndi;
		device_t child;
		bus_addr_t phys;
		bus_size_t size;

		/* Add gpio controller child */
		if (!OF_hasprop(dt_child, "gpio-controller"))
			continue;
		child = simplebus_add_device(dev, dt_child, 0,  NULL, -1, NULL);
		if (child == NULL)
			break;
		/* Setup child resources */
		phys = CHIP_REG_OFFSET(re->start, i);
		size = CHIP_REG_STRIDE;
		if (phys + size - 1 <= re->end) {
			ndi = device_get_ivars(child);
			resource_list_add(&ndi->rl, SYS_RES_MEMORY, 0,
			    phys, phys + size - 1, size);
		}
		i++;
	}

	ret = bus_generic_attach(dev);
	if (ret == 0) {
	    fdt_pinctrl_register(dev, "ingenic,pins");
	    fdt_pinctrl_configure_tree(dev);
	}
	return (ret);
}