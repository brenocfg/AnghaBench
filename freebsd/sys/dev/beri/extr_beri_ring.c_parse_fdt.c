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
struct beri_softc {void* control_write; void* control_read; void* data_write; void* data_read; void* data_size; int /*<<< orphan*/  dev; int /*<<< orphan*/  devname; } ;
typedef  int phandle_t ;
typedef  void* pcell_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  OF_getencprop (int,char*,void**,int) ; 
 scalar_t__ OF_getprop (int,char*,int /*<<< orphan*/ *,int) ; 
 int OF_getproplen (int,char*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int ofw_bus_get_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
parse_fdt(struct beri_softc *sc)
{
	pcell_t dts_value[0];
	phandle_t node;
	int len;

	if ((node = ofw_bus_get_node(sc->dev)) == -1)
		return (ENXIO);

	/* get device name */
	if (OF_getprop(ofw_bus_get_node(sc->dev), "device_name",
		&sc->devname, sizeof(sc->devname)) <= 0) {
		device_printf(sc->dev, "Can't get device_name\n");
		return (ENXIO);
	}

	if ((len = OF_getproplen(node, "data_size")) <= 0)
		return (ENXIO);
	OF_getencprop(node, "data_size", dts_value, len);
	sc->data_size = dts_value[0];

	if ((len = OF_getproplen(node, "data_read")) <= 0)
		return (ENXIO);
	OF_getencprop(node, "data_read", dts_value, len);
	sc->data_read = dts_value[0];

	if ((len = OF_getproplen(node, "data_write")) <= 0)
		return (ENXIO);
	OF_getencprop(node, "data_write", dts_value, len);
	sc->data_write = dts_value[0];

	if ((len = OF_getproplen(node, "control_read")) <= 0)
		return (ENXIO);
	OF_getencprop(node, "control_read", dts_value, len);
	sc->control_read = dts_value[0];

	if ((len = OF_getproplen(node, "control_write")) <= 0)
		return (ENXIO);
	OF_getencprop(node, "control_write", dts_value, len);
	sc->control_write = dts_value[0];

	return (0);
}