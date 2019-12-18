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
typedef  scalar_t__ uint8_t ;
struct usb_interface {scalar_t__ num_altsetting; scalar_t__ altsetting; scalar_t__ cur_altsetting; int /*<<< orphan*/  bsd_iface_index; } ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct usb_interface* usb_ifnum_to_if (struct usb_device*,scalar_t__) ; 
 int /*<<< orphan*/  usb_linux_cleanup_interface (struct usb_device*,struct usb_interface*) ; 
 int usbd_set_alt_interface_index (struct usb_device*,int /*<<< orphan*/ ,scalar_t__) ; 

int
usb_set_interface(struct usb_device *dev, uint8_t iface_no, uint8_t alt_index)
{
	struct usb_interface *p_ui = usb_ifnum_to_if(dev, iface_no);
	int err;

	if (p_ui == NULL)
		return (-EINVAL);
	if (alt_index >= p_ui->num_altsetting)
		return (-EINVAL);
	usb_linux_cleanup_interface(dev, p_ui);
	err = -usbd_set_alt_interface_index(dev,
	    p_ui->bsd_iface_index, alt_index);
	if (err == 0) {
		p_ui->cur_altsetting = p_ui->altsetting + alt_index;
	}
	return (err);
}