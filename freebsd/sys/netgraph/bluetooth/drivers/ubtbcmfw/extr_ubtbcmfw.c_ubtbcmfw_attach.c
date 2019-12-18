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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  bIfaceIndex; } ;
struct usb_attach_arg {TYPE_1__ info; int /*<<< orphan*/  device; } ;
struct ubtbcmfw_softc {int /*<<< orphan*/  sc_fifo; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_xfer; int /*<<< orphan*/  sc_udev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  GID_OPERATOR ; 
 int MTX_DEF ; 
 int MTX_RECURSE ; 
 int /*<<< orphan*/  UBTBCMFW_IFACE_IDX ; 
 int /*<<< orphan*/  UBTBCMFW_N_TRANSFER ; 
 int /*<<< orphan*/  UID_ROOT ; 
 struct usb_attach_arg* device_get_ivars (int /*<<< orphan*/ ) ; 
 struct ubtbcmfw_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_usb_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ubtbcmfw_config ; 
 int /*<<< orphan*/  ubtbcmfw_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubtbcmfw_fifo_methods ; 
 int usb_fifo_attach (int /*<<< orphan*/ ,struct ubtbcmfw_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usbd_errstr (int) ; 
 int usbd_transfer_setup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ubtbcmfw_softc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ubtbcmfw_attach(device_t dev)
{
	struct usb_attach_arg	*uaa = device_get_ivars(dev);
	struct ubtbcmfw_softc	*sc = device_get_softc(dev);
	uint8_t			iface_index;
	int			error;

	sc->sc_udev = uaa->device;

	device_set_usb_desc(dev);

	mtx_init(&sc->sc_mtx, "ubtbcmfw lock", NULL, MTX_DEF | MTX_RECURSE);

	iface_index = UBTBCMFW_IFACE_IDX;
	error = usbd_transfer_setup(uaa->device, &iface_index, sc->sc_xfer,
				ubtbcmfw_config, UBTBCMFW_N_TRANSFER,
				sc, &sc->sc_mtx);
	if (error != 0) {
		device_printf(dev, "allocating USB transfers failed. %s\n",
			usbd_errstr(error));
		goto detach;
	}

	error = usb_fifo_attach(uaa->device, sc, &sc->sc_mtx,
			&ubtbcmfw_fifo_methods, &sc->sc_fifo,
			device_get_unit(dev), 0 - 1, uaa->info.bIfaceIndex,
			UID_ROOT, GID_OPERATOR, 0644);
	if (error != 0) {
		device_printf(dev, "could not attach fifo. %s\n",
			usbd_errstr(error));
		goto detach;
	}

	return (0);	/* success */

detach:
	ubtbcmfw_detach(dev);

	return (ENXIO);	/* failure */
}