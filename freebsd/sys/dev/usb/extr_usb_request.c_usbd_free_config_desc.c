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
struct usb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_USBDEV ; 
 int /*<<< orphan*/  free (void*,int /*<<< orphan*/ ) ; 

void
usbd_free_config_desc(struct usb_device *udev, void *ptr)
{
#if (USB_HAVE_FIXED_CONFIG == 0)
	free(ptr, M_USBDEV);
#endif
}