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
struct awusbphy_softc {int id_det_valid; int vbus_det_valid; int /*<<< orphan*/ ** pmu; int /*<<< orphan*/ * reg; struct aw_usbphy_conf* phy_conf; int /*<<< orphan*/  vbus_det_pin; int /*<<< orphan*/  id_det_pin; int /*<<< orphan*/ * phy_ctrl; } ;
struct aw_usbphy_conf {int num_phys; } ;
typedef  int /*<<< orphan*/  regulator_t ;
typedef  int /*<<< orphan*/  pname ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  hwreset_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  clk_t ;
struct TYPE_2__ {scalar_t__ ocd_data; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 scalar_t__ clk_get_by_ofw_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compat_data ; 
 struct awusbphy_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int gpio_pin_get_by_ofw_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int hwreset_deassert (int /*<<< orphan*/ ) ; 
 scalar_t__ hwreset_get_by_ofw_idx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ofw_bus_find_string_index (int /*<<< orphan*/ ,char*,char*,int*) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 TYPE_1__* ofw_bus_search_compatible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ regulator_get_by_ofw_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int
awusbphy_init(device_t dev)
{
	struct awusbphy_softc *sc;
	phandle_t node;
	char pname[20];
	int error, off, rid;
	regulator_t reg;
	hwreset_t rst;
	clk_t clk;

	sc = device_get_softc(dev);
	node = ofw_bus_get_node(dev);

	sc->phy_conf = (struct aw_usbphy_conf *)ofw_bus_search_compatible(dev, compat_data)->ocd_data;

	/* Get phy_ctrl region */
	if (ofw_bus_find_string_index(node, "reg-names", "phy_ctrl", &rid) != 0) {
		device_printf(dev, "Cannot locate phy control resource\n");
		return (ENXIO);
	}
	sc->phy_ctrl = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE);
	if (sc->phy_ctrl == NULL) {
		device_printf(dev, "Cannot allocate resource\n");
		return (ENXIO);
	}

	/* Enable clocks */
	for (off = 0; clk_get_by_ofw_index(dev, 0, off, &clk) == 0; off++) {
		error = clk_enable(clk);
		if (error != 0) {
			device_printf(dev, "couldn't enable clock %s\n",
			    clk_get_name(clk));
			return (error);
		}
	}

	/* De-assert resets */
	for (off = 0; hwreset_get_by_ofw_idx(dev, 0, off, &rst) == 0; off++) {
		error = hwreset_deassert(rst);
		if (error != 0) {
			device_printf(dev, "couldn't de-assert reset %d\n",
			    off);
			return (error);
		}
	}

	/* Get GPIOs */
	error = gpio_pin_get_by_ofw_property(dev, node, "usb0_id_det-gpios",
	    &sc->id_det_pin);
	if (error == 0)
		sc->id_det_valid = 1;
	error = gpio_pin_get_by_ofw_property(dev, node, "usb0_vbus_det-gpios",
	    &sc->vbus_det_pin);
	if (error == 0)
		sc->vbus_det_valid = 1;

	sc->reg = malloc(sizeof(*(sc->reg)) * sc->phy_conf->num_phys, M_DEVBUF,
	    M_WAITOK | M_ZERO);
	sc->pmu = malloc(sizeof(*(sc->pmu)) * sc->phy_conf->num_phys, M_DEVBUF,
	    M_WAITOK | M_ZERO);
	/* Get regulators */
	for (off = 0; off < sc->phy_conf->num_phys; off++) {
		snprintf(pname, sizeof(pname), "usb%d_vbus-supply", off);
		if (regulator_get_by_ofw_property(dev, 0, pname, &reg) == 0)
			sc->reg[off] = reg;

		snprintf(pname, sizeof(pname), "pmu%d", off);
		if (ofw_bus_find_string_index(node, "reg-names",
		    pname, &rid) != 0)
			continue;

		sc->pmu[off] = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
		    RF_ACTIVE);
		if (sc->pmu[off] == NULL) {
			device_printf(dev, "Cannot allocate resource\n");
			return (ENXIO);
		}
	}

	return (0);
}