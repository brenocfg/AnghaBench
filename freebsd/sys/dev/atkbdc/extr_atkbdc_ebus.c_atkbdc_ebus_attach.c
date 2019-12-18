#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct atkbdc_device {int dummy; } ;
typedef  scalar_t__ rman_res_t ;
typedef  scalar_t__ phandle_t ;
typedef  int /*<<< orphan*/ * device_t ;
struct TYPE_9__ {int retry; int /*<<< orphan*/ * port0; int /*<<< orphan*/ * port1; } ;
typedef  TYPE_1__ atkbdc_softc_t ;
struct TYPE_10__ {int /*<<< orphan*/  resources; int /*<<< orphan*/  rid; } ;
typedef  TYPE_2__ atkbdc_device_t ;

/* Variables and functions */
 char* ATKBD_DRIVER_NAME ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  KBDC_RID_AUX ; 
 int /*<<< orphan*/  KBDC_RID_KBD ; 
 scalar_t__ KBD_STATUS_PORT ; 
 int /*<<< orphan*/  M_ATKBDDEV ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 scalar_t__ OF_child (int /*<<< orphan*/ ) ; 
 int OF_getprop_alloc (scalar_t__,char*,void**) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 int /*<<< orphan*/  OF_prop_free (char*) ; 
 char* PSM_DRIVER_NAME ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int atkbdc_attach_unit (int,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* atkbdc_get_softc (int) ; 
 void* bus_alloc_resource (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int bus_generic_attach (int /*<<< orphan*/ *) ; 
 scalar_t__ bus_get_resource (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,scalar_t__*,scalar_t__*) ; 
 scalar_t__ bus_get_resource_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ *) ; 
 int device_get_unit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  device_set_softc (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  free (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resource_list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  resource_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resource_list_init (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int
atkbdc_ebus_attach(device_t dev)
{
	atkbdc_softc_t *sc;
	atkbdc_device_t *adi;
	device_t cdev;
	phandle_t child;
	rman_res_t count, intr, start;
	int children, error, rid, unit;
	char *cname, *dname;

	unit = device_get_unit(dev);
	sc = *(atkbdc_softc_t **)device_get_softc(dev);
	if (sc == NULL) {
		/*
		 * We have to maintain two copies of the kbdc_softc struct,
		 * as the low-level console needs to have access to the
		 * keyboard controller before kbdc is probed and attached.
		 * kbdc_soft[] contains the default entry for that purpose.
		 * See atkbdc.c. XXX
		 */
		sc = atkbdc_get_softc(unit);
		if (sc == NULL)
			return (ENOMEM);
		device_set_softc(dev, sc);
	}

	rid = 0;
	if (bus_get_resource(dev, SYS_RES_MEMORY, rid, &start, &count) != 0) {
		device_printf(dev,
		    "cannot determine command/data port resource\n");
		return (ENXIO);
	}
	sc->retry = 5000;
	sc->port0 = bus_alloc_resource(dev, SYS_RES_MEMORY, &rid, start, start,
	    1, RF_ACTIVE);
	if (sc->port0 == NULL) {
		device_printf(dev,
		    "cannot allocate command/data port resource\n");
		return (ENXIO);
	}

	rid = 1;
	if (bus_get_resource(dev, SYS_RES_MEMORY, rid, &start, &count) != 0) {
		device_printf(dev, "cannot determine status port resource\n");
		error = ENXIO;
		goto fail_port0;
	}
	start += KBD_STATUS_PORT;
	sc->port1 = bus_alloc_resource(dev, SYS_RES_MEMORY, &rid, start, start,
	    1, RF_ACTIVE);
	if (sc->port1 == NULL) {
		device_printf(dev, "cannot allocate status port resource\n");
		error = ENXIO;
		goto fail_port0;
	}

	error = atkbdc_attach_unit(unit, sc, sc->port0, sc->port1);
	if (error != 0) {
		device_printf(dev, "atkbdc_attach_unit failed\n");
		goto fail_port1;
	}

	/* Attach children. */
	children = 0;
	for (child = OF_child(ofw_bus_get_node(dev)); child != 0;
	    child = OF_peer(child)) {
		if ((OF_getprop_alloc(child, "name", (void **)&cname)) == -1)
			continue;
		if (children >= 2) {
			device_printf(dev,
			    "<%s>: only two children per 8042 supported\n",
			    cname);
			OF_prop_free(cname);
			continue;
		}
		adi = malloc(sizeof(struct atkbdc_device), M_ATKBDDEV,
		    M_NOWAIT | M_ZERO);
		if (adi == NULL) {
			device_printf(dev, "<%s>: malloc failed\n", cname);
			OF_prop_free(cname);
			continue;
		}
		if (strcmp(cname, "kb_ps2") == 0) {
			adi->rid = KBDC_RID_KBD;
			dname = ATKBD_DRIVER_NAME;
		} else if (strcmp(cname, "kdmouse") == 0) {
			adi->rid = KBDC_RID_AUX;
			dname = PSM_DRIVER_NAME;
		} else {
			device_printf(dev, "<%s>: unknown device\n", cname);
			free(adi, M_ATKBDDEV);
			OF_prop_free(cname);
			continue;
		}
		intr = bus_get_resource_start(dev, SYS_RES_IRQ, adi->rid);
		if (intr == 0) {
			device_printf(dev,
			    "<%s>: cannot determine interrupt resource\n",
			    cname);
			free(adi, M_ATKBDDEV);
			OF_prop_free(cname);
			continue;
		}
		resource_list_init(&adi->resources);
		resource_list_add(&adi->resources, SYS_RES_IRQ, adi->rid,
		    intr, intr, 1);
		if ((cdev = device_add_child(dev, dname, -1)) == NULL) {
			device_printf(dev, "<%s>: device_add_child failed\n",
			    cname);
			resource_list_free(&adi->resources);
			free(adi, M_ATKBDDEV);
			OF_prop_free(cname);
			continue;
		}
		device_set_ivars(cdev, adi);
		children++;
	}

	error = bus_generic_attach(dev);
	if (error != 0) {
		device_printf(dev, "bus_generic_attach failed\n");
		goto fail_port1;
	}

	return (0);

 fail_port1:
	bus_release_resource(dev, SYS_RES_MEMORY, 1, sc->port1);
 fail_port0:
	bus_release_resource(dev, SYS_RES_MEMORY, 0, sc->port0);

	return (error);
}