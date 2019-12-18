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
struct TYPE_2__ {int /*<<< orphan*/  sc_bus; int /*<<< orphan*/ ** sc_irq_res; int /*<<< orphan*/ ** sc_intr_hdl; } ;
struct octusb_octeon_softc {TYPE_1__ sc_dci; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int OCTUSB_MAX_PORTS ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int cvmx_usb_get_num_ports () ; 
 int /*<<< orphan*/  device_delete_children (int /*<<< orphan*/ ) ; 
 struct octusb_octeon_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  octusb_uninit (TYPE_1__*) ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int /*<<< orphan*/  usb_bus_mem_free_all (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
octusb_octeon_detach(device_t dev)
{
	struct octusb_octeon_softc *sc = device_get_softc(dev);
	int err;
	int nports;
	int i;

	/* during module unload there are lots of children leftover */
	device_delete_children(dev);

	if (sc->sc_dci.sc_irq_res[0] && sc->sc_dci.sc_intr_hdl[0])
		/*
	 	 * only call octusb_octeon_uninit() after octusb_octeon_init()
	 	 */
		octusb_uninit(&sc->sc_dci);

	nports = cvmx_usb_get_num_ports();
	if (nports > OCTUSB_MAX_PORTS)
		panic("octusb: too many USB ports %d", nports);
	for (i = 0; i < nports; i++) {
		if (sc->sc_dci.sc_irq_res[i] && sc->sc_dci.sc_intr_hdl[i]) {
			err = bus_teardown_intr(dev, sc->sc_dci.sc_irq_res[i],
			    sc->sc_dci.sc_intr_hdl[i]);
			sc->sc_dci.sc_intr_hdl[i] = NULL;
		}
		if (sc->sc_dci.sc_irq_res[i]) {
			bus_release_resource(dev, SYS_RES_IRQ, 0,
			    sc->sc_dci.sc_irq_res[i]);
			sc->sc_dci.sc_irq_res[i] = NULL;
		}
	}
	usb_bus_mem_free_all(&sc->sc_dci.sc_bus, NULL);

	return (0);
}