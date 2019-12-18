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
typedef  scalar_t__ usb_error_t ;
typedef  int uint8_t ;
struct usb_interface_descriptor {int bInterfaceClass; int /*<<< orphan*/  bInterfaceSubClass; int /*<<< orphan*/  bInterfaceProtocol; } ;
struct usb_interface {struct usb_interface_descriptor* idesc; } ;
struct usb_device {int dummy; } ;
struct usb_config {int dummy; } ;
struct bbb_transfer {int /*<<< orphan*/ * xfer; void* csw; void* cbw; int /*<<< orphan*/  buffer_size; void* buffer; int /*<<< orphan*/  mtx; int /*<<< orphan*/  cv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_USB ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 size_t ST_COMMAND ; 
 size_t ST_DATA_RD ; 
 int ST_MAX ; 
 size_t ST_STATUS ; 
#define  UICLASS_HID 135 
#define  UICLASS_MASS 134 
#define  UIPROTO_MASS_BBB 133 
#define  UIPROTO_MASS_BBB_OLD 132 
#define  UISUBCLASS_SCSI 131 
#define  UISUBCLASS_SFF8020I 130 
#define  UISUBCLASS_SFF8070I 129 
#define  UISUBCLASS_UFI 128 
 struct usb_config* bbb_config ; 
 int /*<<< orphan*/  bbb_detach (struct bbb_transfer*) ; 
 struct usb_config* bbb_raw_config ; 
 int /*<<< orphan*/  cv_init (int /*<<< orphan*/ *,char*) ; 
 struct bbb_transfer* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_detach_device (struct usb_device*,int,int /*<<< orphan*/ ) ; 
 int usbd_enum_lock (struct usb_device*) ; 
 int /*<<< orphan*/  usbd_enum_unlock (struct usb_device*) ; 
 struct usb_interface* usbd_get_iface (struct usb_device*,int) ; 
 scalar_t__ usbd_transfer_setup (struct usb_device*,int*,int /*<<< orphan*/ *,struct usb_config const*,int,struct bbb_transfer*,int /*<<< orphan*/ *) ; 
 void* usbd_xfer_get_frame_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_max_len (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct bbb_transfer *
bbb_attach(struct usb_device *udev, uint8_t iface_index,
    uint8_t bInterfaceClass)
{
	struct usb_interface *iface;
	struct usb_interface_descriptor *id;
	const struct usb_config *pconfig;
	struct bbb_transfer *sc;
	usb_error_t err;
	int nconfig;

#if USB_HAVE_MSCTEST_DETACH
	uint8_t do_unlock;

	/* Prevent re-enumeration */
	do_unlock = usbd_enum_lock(udev);

	/*
	 * Make sure any driver which is hooked up to this interface,
	 * like umass is gone:
	 */
	usb_detach_device(udev, iface_index, 0);

	if (do_unlock)
		usbd_enum_unlock(udev);
#endif

	iface = usbd_get_iface(udev, iface_index);
	if (iface == NULL)
		return (NULL);

	id = iface->idesc;
	if (id == NULL || id->bInterfaceClass != bInterfaceClass)
		return (NULL);

	switch (id->bInterfaceClass) {
	case UICLASS_MASS:
		switch (id->bInterfaceSubClass) {
		case UISUBCLASS_SCSI:
		case UISUBCLASS_UFI:
		case UISUBCLASS_SFF8020I:
		case UISUBCLASS_SFF8070I:
			break;
		default:
			return (NULL);
		}
		switch (id->bInterfaceProtocol) {
		case UIPROTO_MASS_BBB_OLD:
		case UIPROTO_MASS_BBB:
			break;
		default:
			return (NULL);
		}
		pconfig = bbb_config;
		nconfig = ST_MAX;
		break;
	case UICLASS_HID:
		switch (id->bInterfaceSubClass) {
		case 0:
			break;
		default:
			return (NULL);
		}
		pconfig = bbb_raw_config;
		nconfig = 1;
		break;
	default:
		return (NULL);
	}

	sc = malloc(sizeof(*sc), M_USB, M_WAITOK | M_ZERO);
	mtx_init(&sc->mtx, "USB autoinstall", NULL, MTX_DEF);
	cv_init(&sc->cv, "WBBB");

	err = usbd_transfer_setup(udev, &iface_index, sc->xfer, pconfig,
	    nconfig, sc, &sc->mtx);
	if (err) {
		bbb_detach(sc);
		return (NULL);
	}
	switch (id->bInterfaceClass) {
	case UICLASS_MASS:
		/* store pointer to DMA buffers */
		sc->buffer = usbd_xfer_get_frame_buffer(
		    sc->xfer[ST_DATA_RD], 0);
		sc->buffer_size =
		    usbd_xfer_max_len(sc->xfer[ST_DATA_RD]);
		sc->cbw = usbd_xfer_get_frame_buffer(
		    sc->xfer[ST_COMMAND], 0);
		sc->csw = usbd_xfer_get_frame_buffer(
		    sc->xfer[ST_STATUS], 0);
		break;
	default:
		break;
	}
	return (sc);
}