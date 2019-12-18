#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ irq; int /*<<< orphan*/  isrc; int /*<<< orphan*/  tri; int /*<<< orphan*/  pol; } ;
struct aw_nmi_softc {int /*<<< orphan*/ * res; int /*<<< orphan*/  intrcookie; TYPE_1__ intr; int /*<<< orphan*/  dev; struct aw_nmi_reg_cfg* cfg; } ;
struct aw_nmi_reg_cfg {int /*<<< orphan*/  pending_reg; int /*<<< orphan*/  enable_reg; } ;
typedef  scalar_t__ phandle_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {scalar_t__ ocd_data; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  INTR_POLARITY_CONFORM ; 
 int /*<<< orphan*/  INTR_TRIGGER_CONFORM ; 
 int /*<<< orphan*/  INTR_TYPE_MISC ; 
 int NMI_IRQ_ACK ; 
 int /*<<< orphan*/  NMI_IRQ_ENABLE ; 
 scalar_t__ OF_xref_from_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SC_NMI_WRITE (struct aw_nmi_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  aw_nmi_intr ; 
 int /*<<< orphan*/  aw_nmi_res_spec ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct aw_nmi_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compat_data ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct aw_nmi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ intr_isrc_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * intr_pic_register (int /*<<< orphan*/ ,intptr_t) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 TYPE_2__* ofw_bus_search_compatible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aw_nmi_attach(device_t dev)
{
	struct aw_nmi_softc *sc;
	phandle_t xref;

	sc = device_get_softc(dev);
	sc->dev = dev;
	sc->cfg = (struct aw_nmi_reg_cfg *)
	    ofw_bus_search_compatible(dev, compat_data)->ocd_data;

	if (bus_alloc_resources(dev, aw_nmi_res_spec, sc->res) != 0) {
		device_printf(dev, "can't allocate device resources\n");
		return (ENXIO);
	}
	if ((bus_setup_intr(dev, sc->res[1], INTR_TYPE_MISC,
	    aw_nmi_intr, NULL, sc, &sc->intrcookie))) {
		device_printf(dev, "unable to register interrupt handler\n");
		bus_release_resources(dev, aw_nmi_res_spec, sc->res);
		return (ENXIO);
	}

	/* Disable and clear interrupts */
	SC_NMI_WRITE(sc, sc->cfg->enable_reg, !NMI_IRQ_ENABLE);
	SC_NMI_WRITE(sc, sc->cfg->pending_reg, NMI_IRQ_ACK);

	xref = OF_xref_from_node(ofw_bus_get_node(dev));
	/* Register our isrc */
	sc->intr.irq = 0;
	sc->intr.pol = INTR_POLARITY_CONFORM;
	sc->intr.tri = INTR_TRIGGER_CONFORM;
	if (intr_isrc_register(&sc->intr.isrc, sc->dev, 0, "%s,%u",
	      device_get_nameunit(sc->dev), sc->intr.irq) != 0)
		goto error;

	if (intr_pic_register(dev, (intptr_t)xref) == NULL) {
		device_printf(dev, "could not register pic\n");
		goto error;
	}
	return (0);

error:
	bus_teardown_intr(dev, sc->res[1], sc->intrcookie);
	bus_release_resources(dev, aw_nmi_res_spec, sc->res);
	return (ENXIO);
}