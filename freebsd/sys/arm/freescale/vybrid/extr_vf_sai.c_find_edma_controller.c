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
struct sc_info {int /*<<< orphan*/  edma_chnum; struct edma_softc* edma_sc; int /*<<< orphan*/  dev; } ;
struct edma_softc {int device_id; int /*<<< orphan*/  (* channel_configure ) (struct edma_softc*,int,int) ;} ;
typedef  int phandle_t ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 int EDMA_NUM_DEVICES ; 
 int ENXIO ; 
 int /*<<< orphan*/  OF_getencprop (int,char*,int*,int) ; 
 int OF_getproplen (int,char*) ; 
 int OF_node_from_xref (int) ; 
 int /*<<< orphan*/  devclass_find (char*) ; 
 scalar_t__ devclass_get_device (int /*<<< orphan*/ ,int) ; 
 struct edma_softc* device_get_softc (scalar_t__) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct edma_softc*,int,int) ; 

__attribute__((used)) static int
find_edma_controller(struct sc_info *sc)
{
	struct edma_softc *edma_sc;
	phandle_t node, edma_node;
	int edma_src_transmit;
	int edma_mux_group;
	int edma_device_id;
	device_t edma_dev;
	int dts_value;
	int len;
	int i;

	if ((node = ofw_bus_get_node(sc->dev)) == -1)
		return (ENXIO);

	if ((len = OF_getproplen(node, "edma-controller")) <= 0)
		return (ENXIO);
	if ((len = OF_getproplen(node, "edma-src-transmit")) <= 0)
		return (ENXIO);
	if ((len = OF_getproplen(node, "edma-mux-group")) <= 0)
		return (ENXIO);

	OF_getencprop(node, "edma-src-transmit", &dts_value, len);
	edma_src_transmit = dts_value;
	OF_getencprop(node, "edma-mux-group", &dts_value, len);
	edma_mux_group = dts_value;
	OF_getencprop(node, "edma-controller", &dts_value, len);
	edma_node = OF_node_from_xref(dts_value);

	if ((len = OF_getproplen(edma_node, "device-id")) <= 0) {
		return (ENXIO);
	}

	OF_getencprop(edma_node, "device-id", &dts_value, len);
	edma_device_id = dts_value;

	edma_sc = NULL;

	for (i = 0; i < EDMA_NUM_DEVICES; i++) {
		edma_dev = devclass_get_device(devclass_find("edma"), i);
		if (edma_dev) {
			edma_sc = device_get_softc(edma_dev);
			if (edma_sc->device_id == edma_device_id) {
				/* found */
				break;
			}

			edma_sc = NULL;
		}
	}

	if (edma_sc == NULL) {
		device_printf(sc->dev, "no eDMA. can't operate\n");
		return (ENXIO);
	}

	sc->edma_sc = edma_sc;

	sc->edma_chnum = edma_sc->channel_configure(edma_sc, edma_mux_group,
	    edma_src_transmit);
	if (sc->edma_chnum < 0) {
		/* cant setup eDMA */
		return (ENXIO);
	}

	return (0);
}