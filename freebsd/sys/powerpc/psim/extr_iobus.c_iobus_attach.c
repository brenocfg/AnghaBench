#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* u_int ;
struct TYPE_3__ {char* rm_descr; int /*<<< orphan*/  rm_type; } ;
struct iobus_softc {scalar_t__ sc_node; void* sc_addr; void* sc_size; TYPE_1__ sc_mem_rman; } ;
struct iobus_devinfo {char* id_name; scalar_t__ id_node; int /*<<< orphan*/  id_resources; } ;
typedef  int /*<<< orphan*/  reg ;
typedef  scalar_t__ phandle_t ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  M_IOBUS ; 
 int /*<<< orphan*/  M_WAITOK ; 
 scalar_t__ OF_child (scalar_t__) ; 
 int OF_getprop (scalar_t__,char*,void**,int) ; 
 int /*<<< orphan*/  OF_getprop_alloc (scalar_t__,char*,void**) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 int /*<<< orphan*/  OF_prop_free (char*) ; 
 int /*<<< orphan*/  RMAN_ARRAY ; 
 int bus_generic_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct iobus_softc* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,struct iobus_devinfo*) ; 
 int /*<<< orphan*/  iobus_add_intr (scalar_t__,struct iobus_devinfo*) ; 
 int /*<<< orphan*/  iobus_add_reg (scalar_t__,struct iobus_devinfo*,void*) ; 
 struct iobus_devinfo* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct iobus_devinfo*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ofw_bus_get_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resource_list_init (int /*<<< orphan*/ *) ; 
 scalar_t__ rman_init (TYPE_1__*) ; 
 int /*<<< orphan*/  rman_manage_region (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int
iobus_attach(device_t dev)
{
	struct iobus_softc *sc;
        struct iobus_devinfo *dinfo;
        phandle_t  root;
        phandle_t  child;
        device_t   cdev;
        char *name;
	u_int reg[2];
	int size;

	sc = device_get_softc(dev);
	sc->sc_node = ofw_bus_get_node(dev);

	/*
	 * Find the base addr/size of the iobus, and initialize the
	 * resource manager
	 */
	size = OF_getprop(sc->sc_node, "reg", reg, sizeof(reg));
	if (size == sizeof(reg)) {
		sc->sc_addr = reg[0];
		sc->sc_size = reg[1];
	} else {
		return (ENXIO);
	}

	sc->sc_mem_rman.rm_type = RMAN_ARRAY;
        sc->sc_mem_rman.rm_descr = "IOBus Device Memory";
        if (rman_init(&sc->sc_mem_rman) != 0) {
		device_printf(dev,
                    "failed to init mem range resources\n");
                return (ENXIO);
	}
	rman_manage_region(&sc->sc_mem_rman, 0, sc->sc_size);

        /*
         * Iterate through the sub-devices
         */
        root = sc->sc_node;

        for (child = OF_child(root); child != 0; child = OF_peer(child)) {
                OF_getprop_alloc(child, "name", (void **)&name);

                cdev = device_add_child(dev, NULL, -1);
                if (cdev != NULL) {
                        dinfo = malloc(sizeof(*dinfo), M_IOBUS, M_WAITOK);
			memset(dinfo, 0, sizeof(*dinfo));
			resource_list_init(&dinfo->id_resources);
                        dinfo->id_node = child;
                        dinfo->id_name = name;
			iobus_add_intr(child, dinfo);
			iobus_add_reg(child, dinfo, sc->sc_addr);
                        device_set_ivars(cdev, dinfo);
                } else {
                        OF_prop_free(name);
                }
        }

        return (bus_generic_attach(dev));
}