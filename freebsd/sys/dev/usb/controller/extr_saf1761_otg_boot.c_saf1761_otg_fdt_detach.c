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
struct saf1761_otg_softc {int /*<<< orphan*/  sc_bus; scalar_t__ sc_irq_res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  device_delete_children (int /*<<< orphan*/ ) ; 
 struct saf1761_otg_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saf1761_otg_uninit (struct saf1761_otg_softc*) ; 
 int /*<<< orphan*/  usb_bus_mem_free_all (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
saf1761_otg_fdt_detach(device_t dev)
{
	struct saf1761_otg_softc *sc = device_get_softc(dev);

	/* during module unload there are lots of children leftover */
	device_delete_children(dev);

	if (sc->sc_irq_res) {
		/*
		 * Only call uninit() after init()
		 */
		saf1761_otg_uninit(sc);
	}
	usb_bus_mem_free_all(&sc->sc_bus, NULL);

	return (0);
}