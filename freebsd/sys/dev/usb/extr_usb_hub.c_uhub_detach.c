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
typedef  scalar_t__ uint8_t ;
struct usb_hub {scalar_t__ nports; scalar_t__ ports; int /*<<< orphan*/ * tt_msg; } ;
struct usb_device {int dummy; } ;
struct usb_bus {int dummy; } ;
struct uhub_softc {int /*<<< orphan*/  sc_mtx; TYPE_1__* sc_udev; int /*<<< orphan*/  sc_xfer; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {struct usb_hub* hub; struct usb_bus* bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_USBDEV ; 
 int /*<<< orphan*/  UHUB_N_TRANSFER ; 
 int /*<<< orphan*/  USB_BUS_LOCK (struct usb_bus*) ; 
 int /*<<< orphan*/  USB_BUS_TT_PROC (struct usb_bus*) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (struct usb_bus*) ; 
 struct uhub_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct usb_hub*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 struct usb_device* usb_bus_port_get_device (struct usb_bus*,scalar_t__) ; 
 int /*<<< orphan*/  usb_free_device (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_proc_mwait (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_transfer_unsetup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
uhub_detach(device_t dev)
{
	struct uhub_softc *sc = device_get_softc(dev);
	struct usb_hub *hub = sc->sc_udev->hub;
	struct usb_bus *bus = sc->sc_udev->bus;
	struct usb_device *child;
	uint8_t x;

	if (hub == NULL)		/* must be partially working */
		return (0);

	/* Make sure interrupt transfer is gone. */
	usbd_transfer_unsetup(sc->sc_xfer, UHUB_N_TRANSFER);

	/* Detach all ports */
	for (x = 0; x != hub->nports; x++) {

		child = usb_bus_port_get_device(bus, hub->ports + x);

		if (child == NULL) {
			continue;
		}

		/*
		 * Free USB device and all subdevices, if any.
		 */
		usb_free_device(child, 0);
	}

#if USB_HAVE_TT_SUPPORT
	/* Make sure our TT messages are not queued anywhere */
	USB_BUS_LOCK(bus);
	usb_proc_mwait(USB_BUS_TT_PROC(bus),
	    &hub->tt_msg[0], &hub->tt_msg[1]);
	USB_BUS_UNLOCK(bus);
#endif

#if (USB_HAVE_FIXED_PORT == 0)
	free(hub, M_USBDEV);
#endif
	sc->sc_udev->hub = NULL;

	mtx_destroy(&sc->sc_mtx);

	return (0);
}