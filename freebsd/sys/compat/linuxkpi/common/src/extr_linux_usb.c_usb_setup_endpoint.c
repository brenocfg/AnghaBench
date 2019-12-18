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
typedef  int usb_size_t ;
typedef  scalar_t__ uint8_t ;
struct TYPE_3__ {scalar_t__ bmAttributes; scalar_t__ bEndpointAddress; } ;
struct usb_host_endpoint {int fbsd_buf_size; int /*<<< orphan*/  bsd_xfer; int /*<<< orphan*/  bsd_iface_index; TYPE_1__ desc; } ;
struct usb_device {int dummy; } ;
struct TYPE_4__ {int proxy_buffer; int ext_buffer; int short_xfer_ok; } ;
struct usb_config {int bufsize; TYPE_2__ flags; int /*<<< orphan*/ * callback; scalar_t__ direction; scalar_t__ endpoint; scalar_t__ type; int /*<<< orphan*/  frames; } ;
typedef  int /*<<< orphan*/  cfg ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  Giant ; 
 scalar_t__ UE_ADDR ; 
 scalar_t__ UE_DIR_IN ; 
 scalar_t__ UE_DIR_OUT ; 
 scalar_t__ UE_ISOCHRONOUS ; 
 scalar_t__ UE_XFERTYPE ; 
 int /*<<< orphan*/  bcopy (struct usb_config*,struct usb_config*,int) ; 
 int /*<<< orphan*/  memset (struct usb_config*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_linux_isoc_callback ; 
 int /*<<< orphan*/  usb_linux_non_isoc_callback ; 
 int /*<<< orphan*/  usb_max_isoc_frames (struct usb_device*) ; 
 scalar_t__ usbd_transfer_setup (struct usb_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct usb_config*,int,struct usb_host_endpoint*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_transfer_unsetup (int /*<<< orphan*/ ,int) ; 

int
usb_setup_endpoint(struct usb_device *dev,
    struct usb_host_endpoint *uhe, usb_size_t bufsize)
{
	struct usb_config cfg[2];
	uint8_t type = uhe->desc.bmAttributes & UE_XFERTYPE;
	uint8_t addr = uhe->desc.bEndpointAddress;

	if (uhe->fbsd_buf_size == bufsize) {
		/* optimize */
		return (0);
	}
	usbd_transfer_unsetup(uhe->bsd_xfer, 2);

	uhe->fbsd_buf_size = bufsize;

	if (bufsize == 0) {
		return (0);
	}
	memset(cfg, 0, sizeof(cfg));

	if (type == UE_ISOCHRONOUS) {

		/*
		 * Isochronous transfers are special in that they don't fit
		 * into the BULK/INTR/CONTROL transfer model.
		 */

		cfg[0].type = type;
		cfg[0].endpoint = addr & UE_ADDR;
		cfg[0].direction = addr & (UE_DIR_OUT | UE_DIR_IN);
		cfg[0].callback = &usb_linux_isoc_callback;
		cfg[0].bufsize = 0;	/* use wMaxPacketSize */
		cfg[0].frames = usb_max_isoc_frames(dev);
		cfg[0].flags.proxy_buffer = 1;
#if 0
		/*
		 * The Linux USB API allows non back-to-back
		 * isochronous frames which we do not support. If the
		 * isochronous frames are not back-to-back we need to
		 * do a copy, and then we need a buffer for
		 * that. Enable this at your own risk.
		 */
		cfg[0].flags.ext_buffer = 1;
#endif
		cfg[0].flags.short_xfer_ok = 1;

		bcopy(cfg, cfg + 1, sizeof(*cfg));

		/* Allocate and setup two generic FreeBSD USB transfers */

		if (usbd_transfer_setup(dev, &uhe->bsd_iface_index,
		    uhe->bsd_xfer, cfg, 2, uhe, &Giant)) {
			return (-EINVAL);
		}
	} else {
		if (bufsize > (1 << 22)) {
			/* limit buffer size */
			bufsize = (1 << 22);
		}
		/* Allocate and setup one generic FreeBSD USB transfer */

		cfg[0].type = type;
		cfg[0].endpoint = addr & UE_ADDR;
		cfg[0].direction = addr & (UE_DIR_OUT | UE_DIR_IN);
		cfg[0].callback = &usb_linux_non_isoc_callback;
		cfg[0].bufsize = bufsize;
		cfg[0].flags.ext_buffer = 1;	/* enable zero-copy */
		cfg[0].flags.proxy_buffer = 1;
		cfg[0].flags.short_xfer_ok = 1;

		if (usbd_transfer_setup(dev, &uhe->bsd_iface_index,
		    uhe->bsd_xfer, cfg, 1, uhe, &Giant)) {
			return (-EINVAL);
		}
	}
	return (0);
}