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
struct usb_interface {TYPE_1__* idesc; } ;
struct uhso_softc {struct usb_device* sc_udev; scalar_t__ sc_ttys; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_super_ucom; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_ucom; int /*<<< orphan*/ * sc_xfer; int /*<<< orphan*/  sc_type; } ;
struct TYPE_2__ {int bNumEndpoints; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  UHSO_DPRINTF (int,char*,...) ; 
 int UHSO_IFACE_PORT (int) ; 
 scalar_t__ UHSO_IFACE_PORT_TYPE (int) ; 
 int /*<<< orphan*/  UHSO_IFACE_SPEC (int,int,scalar_t__) ; 
 int UHSO_IFACE_USB_TYPE (int) ; 
 int UHSO_IF_BULK ; 
 int UHSO_IF_MUX ; 
 size_t UHSO_MUX_ENDPT_INTR ; 
 int UHSO_PORT_SERIAL ; 
 scalar_t__ UHSO_PORT_TYPE_NETWORK ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int ucom_attach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,struct uhso_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucom_set_pnpinfo_usb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int uhso_attach_bulkserial (struct uhso_softc*,struct usb_interface*,int) ; 
 int uhso_attach_ifnet (struct uhso_softc*,struct usb_interface*,int) ; 
 int uhso_attach_muxserial (struct uhso_softc*,struct usb_interface*,int) ; 
 int /*<<< orphan*/  uhso_ucom_callback ; 
 struct usb_interface* usbd_get_iface (struct usb_device*,int) ; 
 int /*<<< orphan*/  usbd_transfer_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
uhso_probe_iface(struct uhso_softc *sc, int index,
    int (*probe)(struct usb_device *, int))
{
	struct usb_interface *iface;
	int type, error;

	UHSO_DPRINTF(1, "Probing for interface %d, probe_func=%p\n", index, probe);

	type = probe(sc->sc_udev, index);
	UHSO_DPRINTF(1, "Probe result %x\n", type);
	if (type <= 0)
		return (ENXIO);

	sc->sc_type = type;
	iface = usbd_get_iface(sc->sc_udev, index);

	if (UHSO_IFACE_PORT_TYPE(type) == UHSO_PORT_TYPE_NETWORK) {
		error = uhso_attach_ifnet(sc, iface, type);
		if (error) {
			UHSO_DPRINTF(1, "uhso_attach_ifnet failed");
			return (ENXIO);
		}

		/*
		 * If there is an additional interrupt endpoint on this
		 * interface then we most likely have a multiplexed serial port
		 * available.
		 */
		if (iface->idesc->bNumEndpoints < 3) {
			sc->sc_type = UHSO_IFACE_SPEC( 
			    UHSO_IFACE_USB_TYPE(type) & ~UHSO_IF_MUX,
			    UHSO_IFACE_PORT(type) & ~UHSO_PORT_SERIAL,
			    UHSO_IFACE_PORT_TYPE(type));
			return (0);
		}

		UHSO_DPRINTF(1, "Trying to attach mux. serial\n");
		error = uhso_attach_muxserial(sc, iface, type);
		if (error == 0 && sc->sc_ttys > 0) {
			error = ucom_attach(&sc->sc_super_ucom, sc->sc_ucom,
			    sc->sc_ttys, sc, &uhso_ucom_callback, &sc->sc_mtx);
			if (error) {
				device_printf(sc->sc_dev, "ucom_attach failed\n");
				return (ENXIO);
			}
			ucom_set_pnpinfo_usb(&sc->sc_super_ucom, sc->sc_dev);

			mtx_lock(&sc->sc_mtx);
			usbd_transfer_start(sc->sc_xfer[UHSO_MUX_ENDPT_INTR]);
			mtx_unlock(&sc->sc_mtx);
		}
	} else if ((UHSO_IFACE_USB_TYPE(type) & UHSO_IF_BULK) &&
	    UHSO_IFACE_PORT(type) & UHSO_PORT_SERIAL) {

		error = uhso_attach_bulkserial(sc, iface, type);
		if (error)
			return (ENXIO);

		error = ucom_attach(&sc->sc_super_ucom, sc->sc_ucom,
		    sc->sc_ttys, sc, &uhso_ucom_callback, &sc->sc_mtx);
		if (error) {
			device_printf(sc->sc_dev, "ucom_attach failed\n");
			return (ENXIO);
		}
		ucom_set_pnpinfo_usb(&sc->sc_super_ucom, sc->sc_dev);
	}
	else {
		UHSO_DPRINTF(0, "Unknown type %x\n", type);
		return (ENXIO);
	}

	return (0);
}