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
typedef  scalar_t__ uint16_t ;
struct libusb20_device {int dummy; } ;
struct libusb20_backend {int dummy; } ;
struct LIBUSB20_DEVICE_DESC_DECODED {scalar_t__ idVendor; scalar_t__ idProduct; } ;

/* Variables and functions */
 scalar_t__ LIBUSB20_MODE_HOST ; 
 struct libusb20_backend* libusb20_be_alloc_default () ; 
 int /*<<< orphan*/  libusb20_be_dequeue_device (struct libusb20_backend*,struct libusb20_device*) ; 
 struct libusb20_device* libusb20_be_device_foreach (struct libusb20_backend*,struct libusb20_device*) ; 
 int /*<<< orphan*/  libusb20_be_free (struct libusb20_backend*) ; 
 struct LIBUSB20_DEVICE_DESC_DECODED* libusb20_dev_get_device_desc (struct libusb20_device*) ; 
 scalar_t__ libusb20_dev_get_mode (struct libusb20_device*) ; 

struct libusb20_device *
find_usb_device(uint16_t vid, uint16_t pid)
{
	struct libusb20_backend *pbe = libusb20_be_alloc_default();
	struct libusb20_device *pdev = NULL;
	struct LIBUSB20_DEVICE_DESC_DECODED *ddesc;

	while ((pdev = libusb20_be_device_foreach(pbe, pdev))) {

		if (libusb20_dev_get_mode(pdev) != LIBUSB20_MODE_HOST)
			continue;

		ddesc = libusb20_dev_get_device_desc(pdev);

		if ((vid == ddesc->idVendor) &&
		    (pid == ddesc->idProduct)) {
			libusb20_be_dequeue_device(pbe, pdev);
			break;
		}
	}

	/* release data */
	libusb20_be_free(pbe);

	return (pdev);
}