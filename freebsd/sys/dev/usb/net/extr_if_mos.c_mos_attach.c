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
typedef  int /*<<< orphan*/  uint8_t ;
struct usb_ether {int /*<<< orphan*/ * ue_methods; int /*<<< orphan*/ * ue_mtx; int /*<<< orphan*/  ue_udev; int /*<<< orphan*/  ue_dev; struct mos_softc* ue_sc; } ;
struct usb_attach_arg {int /*<<< orphan*/  device; } ;
struct mos_softc {int mos_flags; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_xfer; struct usb_ether sc_ue; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int MCS7730 ; 
 int MCS7830 ; 
 int MCS7832 ; 
 int /*<<< orphan*/  MOS_DPRINTFN (char*) ; 
 int /*<<< orphan*/  MOS_ENDPT_MAX ; 
 int /*<<< orphan*/  MOS_IFACE_IDX ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int USB_GET_DRIVER_INFO (struct usb_attach_arg*) ; 
 struct usb_attach_arg* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct mos_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_set_usb_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mos_config ; 
 int /*<<< orphan*/  mos_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mos_ue_methods ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int uether_ifattach (struct usb_ether*) ; 
 int usbd_transfer_setup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mos_softc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mos_attach(device_t dev)
{
	struct usb_attach_arg *uaa = device_get_ivars(dev);
	struct mos_softc *sc = device_get_softc(dev);
	struct usb_ether *ue = &sc->sc_ue;
	uint8_t iface_index;
	int error;

	sc->mos_flags = USB_GET_DRIVER_INFO(uaa);

	device_set_usb_desc(dev);
	mtx_init(&sc->sc_mtx, device_get_nameunit(dev), NULL, MTX_DEF);

	iface_index = MOS_IFACE_IDX;
	error = usbd_transfer_setup(uaa->device, &iface_index,
	    sc->sc_xfer, mos_config, MOS_ENDPT_MAX,
	    sc, &sc->sc_mtx);

	if (error) {
		device_printf(dev, "allocating USB transfers failed\n");
		goto detach;
	}
	ue->ue_sc = sc;
	ue->ue_dev = dev;
	ue->ue_udev = uaa->device;
	ue->ue_mtx = &sc->sc_mtx;
	ue->ue_methods = &mos_ue_methods;


	if (sc->mos_flags & MCS7730) {
		MOS_DPRINTFN("model: MCS7730");
	} else if (sc->mos_flags & MCS7830) {
		MOS_DPRINTFN("model: MCS7830");
	} else if (sc->mos_flags & MCS7832) {
		MOS_DPRINTFN("model: MCS7832");
	}
	error = uether_ifattach(ue);
	if (error) {
		device_printf(dev, "could not attach interface\n");
		goto detach;
	}
	return (0);


detach:
	mos_detach(dev);
	return (ENXIO);
}