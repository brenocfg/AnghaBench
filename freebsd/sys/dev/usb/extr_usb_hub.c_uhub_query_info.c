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
typedef  int /*<<< orphan*/  usb_error_t ;
typedef  int uint8_t ;
struct usb_hub_ss_descriptor {int bNbrPorts; } ;
struct usb_hub_descriptor {int bNbrPorts; int /*<<< orphan*/  wHubCharacteristics; } ;
struct TYPE_2__ {scalar_t__ bDeviceClass; } ;
struct usb_device {int speed; TYPE_1__ ddesc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ UDCLASS_HUB ; 
 int UGETW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_ERR_INVAL ; 
#define  USB_SPEED_FULL 131 
#define  USB_SPEED_HIGH 130 
#define  USB_SPEED_LOW 129 
#define  USB_SPEED_SUPER 128 
 int /*<<< orphan*/  usbd_errstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_req_get_hub_descriptor (struct usb_device*,int /*<<< orphan*/ *,struct usb_hub_descriptor*,int) ; 
 int /*<<< orphan*/  usbd_req_get_ss_hub_descriptor (struct usb_device*,int /*<<< orphan*/ *,struct usb_hub_ss_descriptor*,int) ; 

usb_error_t
uhub_query_info(struct usb_device *udev, uint8_t *pnports, uint8_t *ptt)
{
	struct usb_hub_descriptor hubdesc20;
	struct usb_hub_ss_descriptor hubdesc30;
	usb_error_t err;
	uint8_t nports;
	uint8_t tt;

	if (udev->ddesc.bDeviceClass != UDCLASS_HUB)
		return (USB_ERR_INVAL);

	nports = 0;
	tt = 0;

	switch (udev->speed) {
	case USB_SPEED_LOW:
	case USB_SPEED_FULL:
	case USB_SPEED_HIGH:
		/* assuming that there is one port */
		err = usbd_req_get_hub_descriptor(udev, NULL, &hubdesc20, 1);
		if (err) {
			DPRINTFN(0, "getting USB 2.0 HUB descriptor failed,"
			    "error=%s\n", usbd_errstr(err));
			break;
		}
		nports = hubdesc20.bNbrPorts;
		if (nports > 127)
			nports = 127;

		if (udev->speed == USB_SPEED_HIGH)
			tt = (UGETW(hubdesc20.wHubCharacteristics) >> 5) & 3;
		break;

	case USB_SPEED_SUPER:
		err = usbd_req_get_ss_hub_descriptor(udev, NULL, &hubdesc30, 1);
		if (err) {
			DPRINTFN(0, "Getting USB 3.0 HUB descriptor failed,"
			    "error=%s\n", usbd_errstr(err));
			break;
		}
		nports = hubdesc30.bNbrPorts;
		if (nports > 16)
			nports = 16;
		break;

	default:
		err = USB_ERR_INVAL;
		break;
	}

	if (pnports != NULL)
		*pnports = nports;

	if (ptt != NULL)
		*ptt = tt;

	return (err);
}