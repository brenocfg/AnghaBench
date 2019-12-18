#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usb_error_t ;
typedef  size_t uint8_t ;
struct TYPE_7__ {int /*<<< orphan*/  usbrev; int /*<<< orphan*/ * methods; } ;
struct octusb_softc {scalar_t__ sc_noport; TYPE_2__ sc_bus; TYPE_1__* sc_port; } ;
typedef  int /*<<< orphan*/  cvmx_usb_initialize_flags_t ;
struct TYPE_6__ {int disabled; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_USB_INITIALIZE_FLAGS_CLOCK_AUTO ; 
 int /*<<< orphan*/  CVMX_USB_INITIALIZE_FLAGS_DEBUG_ALL ; 
 scalar_t__ OCTUSB_MAX_PORTS ; 
 int /*<<< orphan*/  USB_BUS_LOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  USB_REV_2_0 ; 
 scalar_t__ cvmx_usb_get_num_ports () ; 
 int cvmx_usb_initialize (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  octusb_bus_methods ; 
 int /*<<< orphan*/  octusb_do_poll (TYPE_2__*) ; 
 int /*<<< orphan*/  octusb_iterate_hw_softc ; 
 int octusbdebug ; 
 int /*<<< orphan*/  usb_bus_mem_flush_all (TYPE_2__*,int /*<<< orphan*/ *) ; 

usb_error_t
octusb_init(struct octusb_softc *sc)
{
	cvmx_usb_initialize_flags_t flags;
	int status;
	uint8_t x;

	/* flush all cache into memory */

	usb_bus_mem_flush_all(&sc->sc_bus, &octusb_iterate_hw_softc);

	/* set up the bus struct */
	sc->sc_bus.methods = &octusb_bus_methods;

	/* get number of ports */
	sc->sc_noport = cvmx_usb_get_num_ports();

	/* check number of ports */
	if (sc->sc_noport > OCTUSB_MAX_PORTS)
		sc->sc_noport = OCTUSB_MAX_PORTS;

	/* set USB revision */
	sc->sc_bus.usbrev = USB_REV_2_0;

	/* flags for port initialization */
	flags = CVMX_USB_INITIALIZE_FLAGS_CLOCK_AUTO;
#ifdef USB_DEBUG
	if (octusbdebug > 100)
		flags |= CVMX_USB_INITIALIZE_FLAGS_DEBUG_ALL;
#endif

	USB_BUS_LOCK(&sc->sc_bus);

	/* setup all ports */
	for (x = 0; x != sc->sc_noport; x++) {
		status = cvmx_usb_initialize(&sc->sc_port[x].state, x, flags);
		if (status < 0)
			sc->sc_port[x].disabled = 1;
	}

	USB_BUS_UNLOCK(&sc->sc_bus);

	/* catch lost interrupts */
	octusb_do_poll(&sc->sc_bus);

	return (0);
}