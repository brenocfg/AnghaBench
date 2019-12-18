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
struct libusb_device_descriptor {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  libusb_device ;
typedef  int /*<<< orphan*/  libusb_context ;

/* Variables and functions */
 int /*<<< orphan*/  iwmbt_err (char*,long long) ; 
 scalar_t__ iwmbt_is_8260 (struct libusb_device_descriptor*) ; 
 int /*<<< orphan*/  libusb_free_device_list (int /*<<< orphan*/ **,int) ; 
 int libusb_get_bus_number (int /*<<< orphan*/ *) ; 
 int libusb_get_device_address (int /*<<< orphan*/ *) ; 
 int libusb_get_device_descriptor (int /*<<< orphan*/ *,struct libusb_device_descriptor*) ; 
 scalar_t__ libusb_get_device_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ***) ; 
 int /*<<< orphan*/ * libusb_ref_device (int /*<<< orphan*/ *) ; 
 long long libusb_strerror (int) ; 

__attribute__((used)) static libusb_device *
iwmbt_find_device(libusb_context *ctx, int bus_id, int dev_id)
{
	libusb_device **list, *dev = NULL, *found = NULL;
	struct libusb_device_descriptor d;
	ssize_t cnt, i;
	int r;

	cnt = libusb_get_device_list(ctx, &list);
	if (cnt < 0) {
		iwmbt_err("libusb_get_device_list() failed: code %lld",
		    (long long int) cnt);
		return (NULL);
	}

	/*
	 * Scan through USB device list.
	 */
	for (i = 0; i < cnt; i++) {
		dev = list[i];
		if (bus_id == libusb_get_bus_number(dev) &&
		    dev_id == libusb_get_device_address(dev)) {
			/* Get the device descriptor for this device entry */
			r = libusb_get_device_descriptor(dev, &d);
			if (r != 0) {
				iwmbt_err("libusb_get_device_descriptor: %s",
				    libusb_strerror(r));
				break;
			}

			/* Match on the vendor/product id */
			if (iwmbt_is_8260(&d)) {
				/*
				 * Take a reference so it's not freed later on.
				 */
				found = libusb_ref_device(dev);
				break;
			}
		}
	}

	libusb_free_device_list(list, 1);
	return (found);
}