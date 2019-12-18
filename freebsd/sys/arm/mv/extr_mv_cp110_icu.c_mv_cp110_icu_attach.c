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
struct mv_cp110_icu_softc {int /*<<< orphan*/  res; struct intr_map_data_fdt* parent_map_data; int /*<<< orphan*/ * parent; int /*<<< orphan*/  dev; } ;
struct intr_map_data_fdt {int dummy; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  INTR_MAP_DATA_FDT ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/ * OF_device_from_xref (int /*<<< orphan*/ ) ; 
 scalar_t__ OF_getencprop (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  OF_xref_from_node (int /*<<< orphan*/ ) ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct mv_cp110_icu_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ intr_alloc_map_data (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/ * intr_pic_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mv_cp110_icu_res_spec ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mv_cp110_icu_attach(device_t dev)
{
	struct mv_cp110_icu_softc *sc;
	phandle_t node, msi_parent;

	sc = device_get_softc(dev);
	sc->dev = dev;
	node = ofw_bus_get_node(dev);

	if (OF_getencprop(node, "msi-parent", &msi_parent,
	    sizeof(phandle_t)) <= 0) {
		device_printf(dev, "cannot find msi-parent property\n");
		return (ENXIO);
	}

	if ((sc->parent = OF_device_from_xref(msi_parent)) == NULL) {
		device_printf(dev, "cannot find msi-parent device\n");
		return (ENXIO);
	}
	if (bus_alloc_resources(dev, mv_cp110_icu_res_spec, &sc->res) != 0) {
		device_printf(dev, "cannot allocate resources for device\n");
		return (ENXIO);
	}

	if (intr_pic_register(dev, OF_xref_from_node(node)) == NULL) {
		device_printf(dev, "Cannot register ICU\n");
		goto fail;
	}

	/* Allocate GICP compatible mapping entry (2 cells) */
	sc->parent_map_data = (struct intr_map_data_fdt *)intr_alloc_map_data(
	    INTR_MAP_DATA_FDT, sizeof(struct intr_map_data_fdt) +
	    + 3 * sizeof(phandle_t), M_WAITOK | M_ZERO);
	return (0);

fail:
	bus_release_resources(dev, mv_cp110_icu_res_spec, &sc->res);
	return (ENXIO);
}