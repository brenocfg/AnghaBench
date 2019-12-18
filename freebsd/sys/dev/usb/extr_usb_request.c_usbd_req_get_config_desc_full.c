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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct usb_device {int dummy; } ;
struct usb_config_descriptor {int /*<<< orphan*/  wTotalLength; } ;
struct mtx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  DPRINTFN (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UDESC_CONFIG ; 
 scalar_t__ UGETW (int /*<<< orphan*/ ) ; 
 scalar_t__ USB_CONFIG_MAX ; 
 scalar_t__ USB_ERR_INVAL ; 
 scalar_t__ USB_ERR_NOMEM ; 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,scalar_t__) ; 
 struct usb_config_descriptor* usbd_alloc_config_desc (struct usb_device*,scalar_t__) ; 
 int /*<<< orphan*/  usbd_free_config_desc (struct usb_device*,struct usb_config_descriptor*) ; 
 scalar_t__ usbd_req_get_config_desc (struct usb_device*,struct mtx*,struct usb_config_descriptor*,int /*<<< orphan*/ ) ; 
 scalar_t__ usbd_req_get_desc (struct usb_device*,struct mtx*,int /*<<< orphan*/ *,struct usb_config_descriptor*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

usb_error_t
usbd_req_get_config_desc_full(struct usb_device *udev, struct mtx *mtx,
    struct usb_config_descriptor **ppcd, uint8_t index)
{
	struct usb_config_descriptor cd;
	struct usb_config_descriptor *cdesc;
	uint32_t len;
	usb_error_t err;

	DPRINTFN(4, "index=%d\n", index);

	*ppcd = NULL;

	err = usbd_req_get_config_desc(udev, mtx, &cd, index);
	if (err)
		return (err);

	/* get full descriptor */
	len = UGETW(cd.wTotalLength);
	if (len < (uint32_t)sizeof(*cdesc)) {
		/* corrupt descriptor */
		return (USB_ERR_INVAL);
	} else if (len > USB_CONFIG_MAX) {
		DPRINTF("Configuration descriptor was truncated\n");
		len = USB_CONFIG_MAX;
	}
	cdesc = usbd_alloc_config_desc(udev, len);
	if (cdesc == NULL)
		return (USB_ERR_NOMEM);
	err = usbd_req_get_desc(udev, mtx, NULL, cdesc, len, len, 0,
	    UDESC_CONFIG, index, 3);
	if (err) {
		usbd_free_config_desc(udev, cdesc);
		return (err);
	}
	/* make sure that the device is not fooling us: */
	USETW(cdesc->wTotalLength, len);

	*ppcd = cdesc;

	return (0);			/* success */
}