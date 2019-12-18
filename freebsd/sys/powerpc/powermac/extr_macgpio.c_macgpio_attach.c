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
typedef  int uint32_t ;
struct macgpio_softc {scalar_t__ sc_node; int /*<<< orphan*/  sc_gpios_rid; int /*<<< orphan*/  sc_gpios; } ;
struct TYPE_3__ {int /*<<< orphan*/  obd_name; } ;
struct macgpio_devinfo {int gpio_num; TYPE_1__ mdi_obdinfo; int /*<<< orphan*/  mdi_resources; } ;
typedef  scalar_t__ phandle_t ;
typedef  int /*<<< orphan*/  irq ;
typedef  int /*<<< orphan*/  iparent ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAP_IRQ (scalar_t__,int) ; 
 int /*<<< orphan*/  M_MACGPIO ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 scalar_t__ OF_child (scalar_t__) ; 
 int OF_getencprop (scalar_t__,char*,int*,int) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 int /*<<< orphan*/  OF_searchencprop (scalar_t__,char*,scalar_t__*,int) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_alloc_resource_any (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int bus_generic_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct macgpio_softc* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,struct macgpio_devinfo*) ; 
 int /*<<< orphan*/  free (struct macgpio_devinfo*,int /*<<< orphan*/ ) ; 
 struct macgpio_devinfo* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ofw_bus_gen_destroy_devinfo (TYPE_1__*) ; 
 scalar_t__ ofw_bus_gen_setup_devinfo (TYPE_1__*,scalar_t__) ; 
 scalar_t__ ofw_bus_get_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resource_list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  resource_list_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int 
macgpio_attach(device_t dev)
{
	struct macgpio_softc *sc;
        struct macgpio_devinfo *dinfo;
        phandle_t root, child, iparent;
        device_t cdev;
	uint32_t irq[2];

	sc = device_get_softc(dev);
	root = sc->sc_node = ofw_bus_get_node(dev);
	
	sc->sc_gpios = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
	    &sc->sc_gpios_rid, RF_ACTIVE);

	/*
	 * Iterate through the sub-devices
	 */
	for (child = OF_child(root); child != 0; child = OF_peer(child)) {
		dinfo = malloc(sizeof(*dinfo), M_MACGPIO, M_WAITOK | M_ZERO);
		if (ofw_bus_gen_setup_devinfo(&dinfo->mdi_obdinfo, child) !=
		    0) {
			free(dinfo, M_MACGPIO);
			continue;
		}

		if (OF_getencprop(child, "reg", &dinfo->gpio_num,
		    sizeof(dinfo->gpio_num)) != sizeof(dinfo->gpio_num)) {
			/*
			 * Some early GPIO controllers don't provide GPIO
			 * numbers for GPIOs designed only to provide
			 * interrupt resources.  We should still allow these
			 * to attach, but with caution.
			 */

			dinfo->gpio_num = -1;
		}

		resource_list_init(&dinfo->mdi_resources);

		if (OF_getencprop(child, "interrupts", irq, sizeof(irq)) == 
		    sizeof(irq)) {
			OF_searchencprop(child, "interrupt-parent", &iparent,
			    sizeof(iparent));
			resource_list_add(&dinfo->mdi_resources, SYS_RES_IRQ,
			    0, MAP_IRQ(iparent, irq[0]),
			    MAP_IRQ(iparent, irq[0]), 1);
		}

		/* Fix messed-up offsets */
		if (dinfo->gpio_num > 0x50)
			dinfo->gpio_num -= 0x50;

		cdev = device_add_child(dev, NULL, -1);
		if (cdev == NULL) {
			device_printf(dev, "<%s>: device_add_child failed\n",
			    dinfo->mdi_obdinfo.obd_name);
			ofw_bus_gen_destroy_devinfo(&dinfo->mdi_obdinfo);
			free(dinfo, M_MACGPIO);
			continue;
		}
		device_set_ivars(cdev, dinfo);
	}

	return (bus_generic_attach(dev));
}