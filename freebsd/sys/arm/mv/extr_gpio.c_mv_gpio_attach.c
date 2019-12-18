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
struct mv_gpio_softc {int pin_num; int /*<<< orphan*/ * irq_res; int /*<<< orphan*/ * irq_rid; int /*<<< orphan*/  mutex; int /*<<< orphan*/ * sc_busdev; int /*<<< orphan*/  mem_res; int /*<<< orphan*/  bsh; int /*<<< orphan*/  bst; scalar_t__ mem_rid; TYPE_1__* gpio_setup; scalar_t__ offset; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  scalar_t__ pcell_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  gp_caps; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  GPIO_GENERIC_CAP ; 
 int MIN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTX_SPIN ; 
 int /*<<< orphan*/  MV_GPIO_MAX_NPINS ; 
 int OF_getencprop (int /*<<< orphan*/ ,char*,scalar_t__*,int) ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * gpiobus_attach_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int mv_gpio_setup_interrupts (struct mv_gpio_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mv_gpio_attach(device_t dev)
{
	int i, rv;
	struct mv_gpio_softc *sc;
	phandle_t node;
	pcell_t pincnt = 0;

	sc = (struct mv_gpio_softc *)device_get_softc(dev);
	if (sc == NULL)
		return (ENXIO);

	node = ofw_bus_get_node(dev);
	sc->dev = dev;

	if (OF_getencprop(node, "pin-count", &pincnt, sizeof(pcell_t)) >= 0 ||
	    OF_getencprop(node, "ngpios", &pincnt, sizeof(pcell_t)) >= 0) {
		sc->pin_num = MIN(pincnt, MV_GPIO_MAX_NPINS);
		if (bootverbose)
			device_printf(dev, "%d pins available\n", sc->pin_num);
	} else {
		device_printf(dev, "ERROR: no pin-count or ngpios entry found!\n");
		return (ENXIO);
	}

	if (OF_getencprop(node, "offset", &sc->offset, sizeof(sc->offset)) == -1)
		sc->offset = 0;

	/* Assign generic capabilities to every gpio pin */
	for(i = 0; i < sc->pin_num; i++)
		sc->gpio_setup[i].gp_caps = GPIO_GENERIC_CAP;

	mtx_init(&sc->mutex, device_get_nameunit(dev), NULL, MTX_SPIN);

	sc->mem_rid = 0;
	sc->mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &sc->mem_rid,
		 RF_ACTIVE | RF_SHAREABLE );

	if (!sc->mem_res) {
		mtx_destroy(&sc->mutex);
		device_printf(dev, "could not allocate memory window\n");
		return (ENXIO);
	}

	sc->bst = rman_get_bustag(sc->mem_res);
	sc->bsh = rman_get_bushandle(sc->mem_res);

	rv = mv_gpio_setup_interrupts(sc, node);
	if (rv != 0)
		return (rv);

	sc->sc_busdev = gpiobus_attach_bus(dev);
	if (sc->sc_busdev == NULL) {
		mtx_destroy(&sc->mutex);
		bus_release_resource(dev, SYS_RES_IRQ,
			sc->irq_rid[i], sc->irq_res[i]);
		return (ENXIO);
	}

	return (0);
}