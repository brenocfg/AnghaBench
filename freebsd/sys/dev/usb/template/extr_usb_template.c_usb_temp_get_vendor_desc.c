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
typedef  int /*<<< orphan*/  uint16_t ;
struct usb_temp_device_desc {void const* (* getVendorDesc ) (struct usb_device_request const*,int /*<<< orphan*/ *) ;} ;
struct usb_device_request {int dummy; } ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 void const* stub1 (struct usb_device_request const*,int /*<<< orphan*/ *) ; 
 struct usb_temp_device_desc* usb_temp_get_tdd (struct usb_device*) ; 

__attribute__((used)) static const void *
usb_temp_get_vendor_desc(struct usb_device *udev,
    const struct usb_device_request *req, uint16_t *plen)
{
	const struct usb_temp_device_desc *tdd;

	tdd = usb_temp_get_tdd(udev);
	if (tdd == NULL) {
		return (NULL);
	}
	if (tdd->getVendorDesc == NULL) {
		return (NULL);
	}
	return ((tdd->getVendorDesc) (req, plen));
}