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
typedef  scalar_t__ usb_error_t ;
struct usb_interface {TYPE_2__* idesc; } ;
struct usb_descriptor {int bDescriptorSubtype; } ;
struct uhso_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_xfer; int /*<<< orphan*/  sc_udev; int /*<<< orphan*/  sc_dev; TYPE_1__* sc_tty; int /*<<< orphan*/  sc_iface_index; } ;
struct TYPE_4__ {int /*<<< orphan*/  bInterfaceNumber; } ;
struct TYPE_3__ {int ht_muxport; int /*<<< orphan*/  ht_xfer; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  UDESC_CS_INTERFACE ; 
 int UHSO_CTRL_MAX ; 
 int /*<<< orphan*/  UHSO_DPRINTF (int,char*,...) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int uhso_alloc_tty (struct uhso_softc*) ; 
 int /*<<< orphan*/  uhso_ctrl_config ; 
 int /*<<< orphan*/  uhso_mux_config ; 
 int /*<<< orphan*/  usbd_errstr (scalar_t__) ; 
 struct usb_descriptor* usbd_find_descriptor (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ usbd_transfer_setup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct uhso_softc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
uhso_attach_muxserial(struct uhso_softc *sc, struct usb_interface *iface,
    int type)
{
	struct usb_descriptor *desc;
	int i, port, tty;
	usb_error_t uerr;

	/*
	 * The class specific interface (type 0x24) descriptor subtype field
	 * contains a bitmask that specifies which (and how many) ports that
	 * are available through this multiplexed serial port.
 	 */
	desc = usbd_find_descriptor(sc->sc_udev, NULL,
	    iface->idesc->bInterfaceNumber, UDESC_CS_INTERFACE, 0xff, 0, 0);
	if (desc == NULL) {
		UHSO_DPRINTF(0, "Failed to find UDESC_CS_INTERFACE\n");
		return (ENXIO);
	}

	UHSO_DPRINTF(1, "Mux port mask %x\n", desc->bDescriptorSubtype);
	if (desc->bDescriptorSubtype == 0)
		return (ENXIO);

	/*
	 * The bitmask is one octet, loop through the number of
	 * bits that are set and create a TTY for each.
	 */
	for (i = 0; i < 8; i++) {
		port = (1 << i);
		if ((port & desc->bDescriptorSubtype) == port) {
			UHSO_DPRINTF(2, "Found mux port %x (%d)\n", port, i);
			tty = uhso_alloc_tty(sc);
			if (tty < 0)
				return (ENOMEM);
			sc->sc_tty[tty].ht_muxport = i;
			uerr = usbd_transfer_setup(sc->sc_udev,	
			    &sc->sc_iface_index, sc->sc_tty[tty].ht_xfer,
			    uhso_ctrl_config, UHSO_CTRL_MAX, sc, &sc->sc_mtx);
			if (uerr) {
				device_printf(sc->sc_dev,
				    "Failed to setup control pipe: %s\n",
				    usbd_errstr(uerr));
				return (ENXIO);
			}
		}
	}

	/* Setup the intr. endpoint */
	uerr = usbd_transfer_setup(sc->sc_udev,
	    &iface->idesc->bInterfaceNumber, sc->sc_xfer,
	    uhso_mux_config, 1, sc, &sc->sc_mtx);
	if (uerr)
		return (ENXIO);

	return (0);
}