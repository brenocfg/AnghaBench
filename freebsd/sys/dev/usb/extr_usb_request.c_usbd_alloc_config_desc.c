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
typedef  scalar_t__ uint32_t ;
struct usb_device {void* config_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  M_USBDEV ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 scalar_t__ USB_CONFIG_MAX ; 
 void* malloc (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 

void *
usbd_alloc_config_desc(struct usb_device *udev, uint32_t size)
{
	if (size > USB_CONFIG_MAX) {
		DPRINTF("Configuration descriptor too big\n");
		return (NULL);
	}
#if (USB_HAVE_FIXED_CONFIG == 0)
	return (malloc(size, M_USBDEV, M_ZERO | M_WAITOK));
#else
	memset(udev->config_data, 0, sizeof(udev->config_data));
	return (udev->config_data);
#endif
}