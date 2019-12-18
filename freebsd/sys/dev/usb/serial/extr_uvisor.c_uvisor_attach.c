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
typedef  int /*<<< orphan*/  uvisor_config_copy ;
struct uvisor_softc {int /*<<< orphan*/  sc_super_ucom; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_ucom; int /*<<< orphan*/  sc_xfer; int /*<<< orphan*/  sc_iface_index; int /*<<< orphan*/  sc_iface_no; int /*<<< orphan*/  sc_flag; int /*<<< orphan*/  sc_udev; } ;
struct usb_config {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bIfaceNum; } ;
struct usb_attach_arg {int /*<<< orphan*/  device; TYPE_1__ info; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,...) ; 
 int ENXIO ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  USB_GET_DRIVER_INFO (struct usb_attach_arg*) ; 
 int /*<<< orphan*/  UVISOR_IFACE_INDEX ; 
 int UVISOR_N_TRANSFER ; 
 struct usb_attach_arg* device_get_ivars (int /*<<< orphan*/ ) ; 
 struct uvisor_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_usb_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct usb_config*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ucom_attach (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,struct uvisor_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucom_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucom_set_pnpinfo_usb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_errstr (int) ; 
 int usbd_transfer_setup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct usb_config*,int,struct uvisor_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uvisor_callback ; 
 int /*<<< orphan*/  uvisor_config ; 
 int /*<<< orphan*/  uvisor_detach (int /*<<< orphan*/ ) ; 
 int uvisor_init (struct uvisor_softc*,int /*<<< orphan*/ ,struct usb_config*) ; 

__attribute__((used)) static int
uvisor_attach(device_t dev)
{
	struct usb_attach_arg *uaa = device_get_ivars(dev);
	struct uvisor_softc *sc = device_get_softc(dev);
	struct usb_config uvisor_config_copy[UVISOR_N_TRANSFER];
	int error;

	DPRINTF("sc=%p\n", sc);
	memcpy(uvisor_config_copy, uvisor_config,
	    sizeof(uvisor_config_copy));

	device_set_usb_desc(dev);

	mtx_init(&sc->sc_mtx, "uvisor", NULL, MTX_DEF);
	ucom_ref(&sc->sc_super_ucom);

	sc->sc_udev = uaa->device;

	/* configure the device */

	sc->sc_flag = USB_GET_DRIVER_INFO(uaa);
	sc->sc_iface_no = uaa->info.bIfaceNum;
	sc->sc_iface_index = UVISOR_IFACE_INDEX;

	error = uvisor_init(sc, uaa->device, uvisor_config_copy);

	if (error) {
		DPRINTF("init failed, error=%s\n",
		    usbd_errstr(error));
		goto detach;
	}
	error = usbd_transfer_setup(uaa->device, &sc->sc_iface_index,
	    sc->sc_xfer, uvisor_config_copy, UVISOR_N_TRANSFER,
	    sc, &sc->sc_mtx);
	if (error) {
		DPRINTF("could not allocate all pipes\n");
		goto detach;
	}

	error = ucom_attach(&sc->sc_super_ucom, &sc->sc_ucom, 1, sc,
	    &uvisor_callback, &sc->sc_mtx);
	if (error) {
		DPRINTF("ucom_attach failed\n");
		goto detach;
	}
	ucom_set_pnpinfo_usb(&sc->sc_super_ucom, dev);

	return (0);

detach:
	uvisor_detach(dev);
	return (ENXIO);
}