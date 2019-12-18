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
struct mv_gpio_softc {int irq_num; int* irq_rid; int offset; int pin_num; int* debounce_counters; struct callout** debounce_callouts; int /*<<< orphan*/  bsh; int /*<<< orphan*/  bst; int /*<<< orphan*/  dev; int /*<<< orphan*/ * irq_res; int /*<<< orphan*/  mutex; int /*<<< orphan*/ * ih_cookie; } ;
struct callout {int dummy; } ;
typedef  scalar_t__ phandle_t ;
typedef  int pcell_t ;
typedef  int /*<<< orphan*/  irq_cells ;
typedef  int /*<<< orphan*/  driver_filter_t ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 scalar_t__ GPIO_INT_CAUSE ; 
 scalar_t__ GPIO_INT_EDGE_MASK ; 
 scalar_t__ GPIO_INT_LEV_MASK ; 
 int /*<<< orphan*/  INTR_TYPE_MISC ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int OF_getproplen (scalar_t__,char*) ; 
 int /*<<< orphan*/  OF_node_from_xref (scalar_t__) ; 
 int OF_searchencprop (int /*<<< orphan*/ ,char*,int*,int) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct mv_gpio_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_space_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ mv_gpio_intr ; 
 scalar_t__ ofw_bus_find_iparent (scalar_t__) ; 

__attribute__((used)) static int
mv_gpio_setup_interrupts(struct mv_gpio_softc *sc, phandle_t node)
{
	phandle_t iparent;
	pcell_t irq_cells;
	int i, size;

	/* Find root interrupt controller */
	iparent = ofw_bus_find_iparent(node);
	if (iparent == 0) {
		device_printf(sc->dev, "No interrupt-parrent found. "
				"Error in DTB\n");
		return (ENXIO);
	} else {
		/* While at parent - store interrupt cells prop */
		if (OF_searchencprop(OF_node_from_xref(iparent),
		    "#interrupt-cells", &irq_cells, sizeof(irq_cells)) == -1) {
			device_printf(sc->dev, "DTB: Missing #interrupt-cells "
			    "property in interrupt parent node\n");
			return (ENXIO);
		}
	}

	size = OF_getproplen(node, "interrupts");
	if (size != -1) {
		size = size / sizeof(pcell_t);
		size = size / irq_cells;
		sc->irq_num = size;
		device_printf(sc->dev, "%d IRQs available\n", sc->irq_num);
	} else {
		device_printf(sc->dev, "ERROR: no interrupts entry found!\n");
		return (ENXIO);
	}

	for (i = 0; i < sc->irq_num; i++) {
		sc->irq_rid[i] = i;
		sc->irq_res[i] = bus_alloc_resource_any(sc->dev, SYS_RES_IRQ,
			&sc->irq_rid[i], RF_ACTIVE);
		if (!sc->irq_res[i]) {
			mtx_destroy(&sc->mutex);
			device_printf(sc->dev,
			    "could not allocate gpio%d interrupt\n", i+1);
			return (ENXIO);
		}
	}

	device_printf(sc->dev, "Disable interrupts (offset = %x + EDGE(0x18)\n", sc->offset);
	/* Disable all interrupts */
	bus_space_write_4(sc->bst, sc->bsh, sc->offset + GPIO_INT_EDGE_MASK, 0);
	device_printf(sc->dev, "Disable interrupts (offset = %x + LEV(0x1C))\n", sc->offset);
	bus_space_write_4(sc->bst, sc->bsh, sc->offset + GPIO_INT_LEV_MASK, 0);

	for (i = 0; i < sc->irq_num; i++) {
		device_printf(sc->dev, "Setup intr %d\n", i);
		if (bus_setup_intr(sc->dev, sc->irq_res[i],
		    INTR_TYPE_MISC,
		    (driver_filter_t *)mv_gpio_intr, NULL,
		    sc, &sc->ih_cookie[i]) != 0) {
			mtx_destroy(&sc->mutex);
			bus_release_resource(sc->dev, SYS_RES_IRQ,
				sc->irq_rid[i], sc->irq_res[i]);
			device_printf(sc->dev, "could not set up intr %d\n", i);
			return (ENXIO);
		}
	}

	/* Clear interrupt status. */
	device_printf(sc->dev, "Clear int status (offset = %x)\n", sc->offset);
	bus_space_write_4(sc->bst, sc->bsh, sc->offset + GPIO_INT_CAUSE, 0);

	sc->debounce_callouts = (struct callout **)malloc(sc->pin_num *
	    sizeof(struct callout *), M_DEVBUF, M_WAITOK | M_ZERO);
	if (sc->debounce_callouts == NULL)
		return (ENOMEM);

	sc->debounce_counters = (int *)malloc(sc->pin_num * sizeof(int),
	    M_DEVBUF, M_WAITOK);
	if (sc->debounce_counters == NULL)
		return (ENOMEM);

	return (0);
}