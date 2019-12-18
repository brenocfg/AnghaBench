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
typedef  int /*<<< orphan*/  usb_error_t ;
typedef  size_t uint8_t ;
struct octusb_softc {size_t sc_noport; int /*<<< orphan*/  sc_bus; TYPE_1__* sc_port; } ;
struct TYPE_2__ {scalar_t__ disabled; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_BUS_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cvmx_usb_shutdown (int /*<<< orphan*/ *) ; 

usb_error_t
octusb_uninit(struct octusb_softc *sc)
{
	uint8_t x;

	USB_BUS_LOCK(&sc->sc_bus);

	for (x = 0; x != sc->sc_noport; x++) {
		if (sc->sc_port[x].disabled == 0)
			cvmx_usb_shutdown(&sc->sc_port[x].state);
	}
	USB_BUS_UNLOCK(&sc->sc_bus);

	return (0);

}