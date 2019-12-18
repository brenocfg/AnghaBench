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
typedef  void* uint8_t ;
struct usb_alt_interface {void* uai_alt_index; void* uai_interface_index; } ;
struct libusb20_device {int /*<<< orphan*/  file_ctrl; } ;
typedef  int /*<<< orphan*/  alt_iface ;

/* Variables and functions */
 int /*<<< orphan*/  IOUSB (int /*<<< orphan*/ ) ; 
 int LIBUSB20_ERROR_OTHER ; 
 int /*<<< orphan*/  USB_SET_ALTINTERFACE ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct usb_alt_interface*) ; 
 int /*<<< orphan*/  memset (struct usb_alt_interface*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ugen20_tr_release (struct libusb20_device*) ; 
 int ugen20_tr_renew (struct libusb20_device*) ; 

__attribute__((used)) static int
ugen20_set_alt_index(struct libusb20_device *pdev,
    uint8_t iface_index, uint8_t alt_index)
{
	struct usb_alt_interface alt_iface;

	memset(&alt_iface, 0, sizeof(alt_iface));

	alt_iface.uai_interface_index = iface_index;
	alt_iface.uai_alt_index = alt_index;

	/* release all active USB transfers */
	ugen20_tr_release(pdev);

	if (ioctl(pdev->file_ctrl, IOUSB(USB_SET_ALTINTERFACE), &alt_iface)) {
		return (LIBUSB20_ERROR_OTHER);
	}
	return (ugen20_tr_renew(pdev));
}