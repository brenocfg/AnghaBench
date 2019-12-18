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
typedef  int uint8_t ;
struct usb_device {int dummy; } ;
struct bbb_transfer {int dummy; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  UICLASS_HID ; 
 int /*<<< orphan*/  USB_ERR_INVAL ; 
 int /*<<< orphan*/  USB_MS_HZ ; 
 struct bbb_transfer* bbb_attach (struct usb_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bbb_detach (struct bbb_transfer*) ; 
 int /*<<< orphan*/  bbb_raw_write (struct bbb_transfer*,int const*,int,int /*<<< orphan*/ ) ; 

usb_error_t
usb_dymo_eject(struct usb_device *udev, uint8_t iface_index)
{
	static const uint8_t data[3] = { 0x1b, 0x5a, 0x01 };
	struct bbb_transfer *sc;
	usb_error_t err;

	sc = bbb_attach(udev, iface_index, UICLASS_HID);
	if (sc == NULL)
		return (USB_ERR_INVAL);
	err = bbb_raw_write(sc, data, sizeof(data), USB_MS_HZ);
	bbb_detach(sc);
	return (err);
}