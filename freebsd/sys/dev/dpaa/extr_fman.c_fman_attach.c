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
struct TYPE_2__ {void* dev; } ;
struct fman_softc {int mem_rid; int irq_rid; int err_irq_rid; int /*<<< orphan*/ * fm_handle; void* err_irq_res; void* irq_res; void* mem_res; void* qman_chan_count; void* qman_chan_base; TYPE_1__ sc_base; } ;
struct fman_config {uintptr_t irq_num; uintptr_t err_irq_num; int /*<<< orphan*/  bus_error_callback; int /*<<< orphan*/  exception_callback; int /*<<< orphan*/  mem_base_addr; int /*<<< orphan*/  fm_id; void* fman_device; } ;
typedef  int /*<<< orphan*/  qchan_range ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  void* pcell_t ;
typedef  void* device_t ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ E_OK ; 
 scalar_t__ OF_getencprop (int /*<<< orphan*/ ,char*,void**,int) ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  XX_FmanFixIntr (int /*<<< orphan*/ ) ; 
 scalar_t__ XX_MallocSmartInit () ; 
 void* bus_alloc_resource_any (void*,int /*<<< orphan*/ ,int*,int) ; 
 int bus_generic_attach (void*) ; 
 struct fman_softc* device_get_softc (void*) ; 
 int /*<<< orphan*/  device_get_unit (void*) ; 
 int /*<<< orphan*/  device_printf (void*,char*) ; 
 int /*<<< orphan*/  fman_detach (void*) ; 
 int /*<<< orphan*/  fman_error_callback ; 
 int /*<<< orphan*/  fman_exception_callback ; 
 int /*<<< orphan*/ * fman_init (struct fman_softc*,struct fman_config*) ; 
 int /*<<< orphan*/  ofw_bus_get_node (void*) ; 
 int /*<<< orphan*/  rman_get_bushandle (void*) ; 
 int /*<<< orphan*/  rman_get_start (void*) ; 

int
fman_attach(device_t dev)
{
	struct fman_softc *sc;
	struct fman_config cfg;
	pcell_t qchan_range[2];
	phandle_t node;

	sc = device_get_softc(dev);
	sc->sc_base.dev = dev;

	/* Check if MallocSmart allocator is ready */
	if (XX_MallocSmartInit() != E_OK) {
		device_printf(dev, "could not initialize smart allocator.\n");
		return (ENXIO);
	}

	node = ofw_bus_get_node(dev);
	if (OF_getencprop(node, "fsl,qman-channel-range", qchan_range,
	    sizeof(qchan_range)) <= 0) {
		device_printf(dev, "Missing QMan channel range property!\n");
		return (ENXIO);
	}
	sc->qman_chan_base = qchan_range[0];
	sc->qman_chan_count = qchan_range[1];
	sc->mem_rid = 0;
	sc->mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &sc->mem_rid,
	    RF_ACTIVE | RF_SHAREABLE);
	if (!sc->mem_res) {
		device_printf(dev, "could not allocate memory.\n");
		return (ENXIO);
	}

	sc->irq_rid = 0;
	sc->irq_res = bus_alloc_resource_any(dev, SYS_RES_IRQ, &sc->irq_rid,
	    RF_ACTIVE);
	if (!sc->irq_res) {
		device_printf(dev, "could not allocate interrupt.\n");
		goto err;
	}

	/*
	 * XXX: Fix FMan interrupt. This is workaround for the issue with
	 * interrupts directed to multiple CPUs by the interrupts subsystem.
	 * Workaround is to bind the interrupt to only one CPU0.
	 */
	XX_FmanFixIntr(rman_get_start(sc->irq_res));

	sc->err_irq_rid = 1;
	sc->err_irq_res = bus_alloc_resource_any(dev, SYS_RES_IRQ,
	    &sc->err_irq_rid, RF_ACTIVE | RF_SHAREABLE);
	if (!sc->err_irq_res) {
		device_printf(dev, "could not allocate error interrupt.\n");
		goto err;
	}

	/* Set FMan configuration */
	cfg.fman_device = dev;
	cfg.fm_id = device_get_unit(dev);
	cfg.mem_base_addr = rman_get_bushandle(sc->mem_res);
	cfg.irq_num = (uintptr_t)sc->irq_res;
	cfg.err_irq_num = (uintptr_t)sc->err_irq_res;
	cfg.exception_callback = fman_exception_callback;
	cfg.bus_error_callback = fman_error_callback;

	sc->fm_handle = fman_init(sc, &cfg);
	if (sc->fm_handle == NULL) {
		device_printf(dev, "could not be configured\n");
		return (ENXIO);
	}

	return (bus_generic_attach(dev));

err:
	fman_detach(dev);
	return (ENXIO);
}