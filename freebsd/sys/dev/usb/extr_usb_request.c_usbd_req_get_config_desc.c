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
typedef  scalar_t__ uint16_t ;
struct usb_device {int dummy; } ;
struct usb_config_descriptor {int /*<<< orphan*/  wTotalLength; } ;
struct mtx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UDESC_CONFIG ; 
 scalar_t__ UGETW (int /*<<< orphan*/ ) ; 
 scalar_t__ USB_ERR_INVAL ; 
 scalar_t__ usbd_req_get_desc (struct usb_device*,struct mtx*,int /*<<< orphan*/ *,struct usb_config_descriptor*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

usb_error_t
usbd_req_get_config_desc(struct usb_device *udev, struct mtx *mtx,
    struct usb_config_descriptor *d, uint8_t conf_index)
{
	usb_error_t err;

	DPRINTFN(4, "confidx=%d\n", conf_index);

	err = usbd_req_get_desc(udev, mtx, NULL, d, sizeof(*d),
	    sizeof(*d), 0, UDESC_CONFIG, conf_index, 0);
	if (err) {
		goto done;
	}
	/* Extra sanity checking */
	if (UGETW(d->wTotalLength) < (uint16_t)sizeof(*d)) {
		err = USB_ERR_INVAL;
	}
done:
	return (err);
}