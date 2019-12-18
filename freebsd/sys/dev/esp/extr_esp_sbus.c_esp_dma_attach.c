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
struct ncr53c9x_softc {int /*<<< orphan*/  sc_freq; } ;
struct lsi64854_softc {struct ncr53c9x_softc* sc_client; } ;
struct esp_softc {int /*<<< orphan*/ * sc_res; struct lsi64854_softc* sc_dma; int /*<<< orphan*/  sc_dev; struct ncr53c9x_softc sc_ncr53c9x; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int OF_getprop (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct esp_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  esp_sbus_glue ; 
 int espattach (struct esp_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  rman_get_rid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
esp_dma_attach(device_t dev)
{
	struct esp_softc *esc;
	struct ncr53c9x_softc *sc;
	int error, i;

	esc = device_get_softc(dev);
	sc = &esc->sc_ncr53c9x;

	esc->sc_dev = dev;
	if (OF_getprop(ofw_bus_get_node(dev), "clock-frequency",
	    &sc->sc_freq, sizeof(sc->sc_freq)) == -1) {
		printf("failed to query OFW for clock-frequency\n");
		return (ENXIO);
	}

	/* XXX hackery */
	esc->sc_dma = (struct lsi64854_softc *)
	    device_get_softc(device_get_parent(dev));
	esc->sc_dma->sc_client = sc;

	/*
	 * Allocate SCSI core registers.
	 */
	i = 0;
	if ((esc->sc_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
	    &i, RF_ACTIVE)) == NULL) {
		device_printf(dev, "cannot allocate SCSI core registers\n");
		return (ENXIO);
	}

	error = espattach(esc, &esp_sbus_glue);
	if (error != 0) {
		device_printf(dev, "espattach failed\n");
		goto fail_dma_eres;
	}

	return (0);

 fail_dma_eres:
	bus_release_resource(dev, SYS_RES_MEMORY, rman_get_rid(esc->sc_res),
	    esc->sc_res);
	return (error);
}