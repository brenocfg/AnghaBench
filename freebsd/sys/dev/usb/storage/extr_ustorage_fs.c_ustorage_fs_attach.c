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
struct ustorage_fs_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/ * sc_xfer; void* sc_dma_ptr; void* sc_csw; void* sc_cbw; int /*<<< orphan*/  sc_iface_no; TYPE_1__* sc_lun; int /*<<< orphan*/  sc_udev; int /*<<< orphan*/  sc_dev; } ;
struct usb_interface_descriptor {int /*<<< orphan*/  bInterfaceNumber; } ;
struct TYPE_4__ {int /*<<< orphan*/  bIfaceIndex; } ;
struct usb_attach_arg {TYPE_2__ info; int /*<<< orphan*/  device; int /*<<< orphan*/  iface; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_3__ {int num_sectors; int removable; int /*<<< orphan*/ * memory_image; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int MTX_DEF ; 
 int MTX_RECURSE ; 
 int /*<<< orphan*/  M_USB ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  USB_POWER_MODE_SAVE ; 
 int USTORAGE_FS_RAM_SECT ; 
 size_t USTORAGE_FS_T_BBB_COMMAND ; 
 size_t USTORAGE_FS_T_BBB_DATA_READ ; 
 int /*<<< orphan*/  USTORAGE_FS_T_BBB_MAX ; 
 size_t USTORAGE_FS_T_BBB_STATUS ; 
 struct usb_attach_arg* device_get_ivars (int /*<<< orphan*/ ) ; 
 struct ustorage_fs_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  device_set_usb_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_errstr (int) ; 
 struct usb_interface_descriptor* usbd_get_interface_descriptor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_set_power_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usbd_transfer_setup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ustorage_fs_softc*,int /*<<< orphan*/ *) ; 
 void* usbd_xfer_get_frame_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ustorage_fs_bbb_config ; 
 int /*<<< orphan*/  ustorage_fs_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ustorage_fs_ramdisk ; 
 int /*<<< orphan*/  ustorage_fs_transfer_start (struct ustorage_fs_softc*,size_t) ; 

__attribute__((used)) static int
ustorage_fs_attach(device_t dev)
{
	struct ustorage_fs_softc *sc = device_get_softc(dev);
	struct usb_attach_arg *uaa = device_get_ivars(dev);
	struct usb_interface_descriptor *id;
	int err;
	int unit;

	/*
	 * NOTE: the softc struct is cleared in device_set_driver.
	 * We can safely call ustorage_fs_detach without specifically
	 * initializing the struct.
	 */

	sc->sc_dev = dev;
	sc->sc_udev = uaa->device;
	unit = device_get_unit(dev);

	/* enable power saving mode */
	usbd_set_power_mode(uaa->device, USB_POWER_MODE_SAVE);

	if (unit == 0) {
		if (ustorage_fs_ramdisk == NULL) {
			/*
			 * allocate a memory image for our ramdisk until
			 * further
			 */
			ustorage_fs_ramdisk =
			    malloc(USTORAGE_FS_RAM_SECT << 9, M_USB,
			    M_ZERO | M_WAITOK);

			if (ustorage_fs_ramdisk == NULL) {
				return (ENOMEM);
			}
		}
		sc->sc_lun[0].memory_image = ustorage_fs_ramdisk;
		sc->sc_lun[0].num_sectors = USTORAGE_FS_RAM_SECT;
		sc->sc_lun[0].removable = 1;
	}

	device_set_usb_desc(dev);

	mtx_init(&sc->sc_mtx, "USTORAGE_FS lock",
	    NULL, (MTX_DEF | MTX_RECURSE));

	/* get interface index */

	id = usbd_get_interface_descriptor(uaa->iface);
	if (id == NULL) {
		device_printf(dev, "failed to get "
		    "interface number\n");
		goto detach;
	}
	sc->sc_iface_no = id->bInterfaceNumber;

	err = usbd_transfer_setup(uaa->device,
	    &uaa->info.bIfaceIndex, sc->sc_xfer, ustorage_fs_bbb_config,
	    USTORAGE_FS_T_BBB_MAX, sc, &sc->sc_mtx);
	if (err) {
		device_printf(dev, "could not setup required "
		    "transfers, %s\n", usbd_errstr(err));
		goto detach;
	}

	sc->sc_cbw = usbd_xfer_get_frame_buffer(sc->sc_xfer[
	    USTORAGE_FS_T_BBB_COMMAND], 0);
	sc->sc_csw = usbd_xfer_get_frame_buffer(sc->sc_xfer[
	    USTORAGE_FS_T_BBB_STATUS], 0);
 	sc->sc_dma_ptr = usbd_xfer_get_frame_buffer(sc->sc_xfer[
	    USTORAGE_FS_T_BBB_DATA_READ], 0);

	/* start Mass Storage State Machine */

	mtx_lock(&sc->sc_mtx);
	ustorage_fs_transfer_start(sc, USTORAGE_FS_T_BBB_COMMAND);
	mtx_unlock(&sc->sc_mtx);

	return (0);			/* success */

detach:
	ustorage_fs_detach(dev);
	return (ENXIO);			/* failure */
}