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
typedef  int /*<<< orphan*/  usb_error_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct usb_interface {int /*<<< orphan*/ * pnpinfo; } ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_USBDEV ; 
 int /*<<< orphan*/  USB_ERR_INVAL ; 
 int /*<<< orphan*/  USB_ERR_NOMEM ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strdup (char const*,int /*<<< orphan*/ ) ; 
 struct usb_interface* usbd_get_iface (struct usb_device*,int /*<<< orphan*/ ) ; 

usb_error_t 
usbd_set_pnpinfo(struct usb_device *udev, uint8_t iface_index, const char *pnpinfo)
{
	struct usb_interface *iface;

	iface = usbd_get_iface(udev, iface_index);
	if (iface == NULL)
		return (USB_ERR_INVAL);

	if (iface->pnpinfo != NULL) {
		free(iface->pnpinfo, M_USBDEV);
		iface->pnpinfo = NULL;
	}

	if (pnpinfo == NULL || pnpinfo[0] == 0)
		return (0);		/* success */

	iface->pnpinfo = strdup(pnpinfo, M_USBDEV);
	if (iface->pnpinfo == NULL)
		return (USB_ERR_NOMEM);

	return (0);			/* success */
}