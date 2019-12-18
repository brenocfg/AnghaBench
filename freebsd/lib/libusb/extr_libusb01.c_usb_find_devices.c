#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int bLength; scalar_t__ bNumConfigurations; int /*<<< orphan*/  iSerialNumber; int /*<<< orphan*/  iProduct; int /*<<< orphan*/  iManufacturer; int /*<<< orphan*/  bcdDevice; int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; int /*<<< orphan*/  bMaxPacketSize0; int /*<<< orphan*/  bDeviceProtocol; int /*<<< orphan*/  bDeviceSubClass; int /*<<< orphan*/  bDeviceClass; int /*<<< orphan*/  bcdUSB; int /*<<< orphan*/  bDescriptorType; } ;
struct usb_device {struct libusb20_device* dev; int /*<<< orphan*/  devnum; TYPE_1__ descriptor; int /*<<< orphan*/  filename; TYPE_2__* bus; } ;
struct libusb20_device {struct usb_device* privLuData; } ;
struct LIBUSB20_DEVICE_DESC_DECODED {scalar_t__ bNumConfigurations; int /*<<< orphan*/  iSerialNumber; int /*<<< orphan*/  iProduct; int /*<<< orphan*/  iManufacturer; int /*<<< orphan*/  bcdDevice; int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; int /*<<< orphan*/  bMaxPacketSize0; int /*<<< orphan*/  bDeviceProtocol; int /*<<< orphan*/  bDeviceSubClass; int /*<<< orphan*/  bDeviceClass; int /*<<< orphan*/  bcdUSB; int /*<<< orphan*/  bDescriptorType; } ;
struct TYPE_4__ {int /*<<< orphan*/  devices; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_ADD (int /*<<< orphan*/ ,struct usb_device*) ; 
 int /*<<< orphan*/  LIST_DEL (int /*<<< orphan*/ ,struct usb_device*) ; 
 scalar_t__ USB_MAXCONFIG ; 
 int /*<<< orphan*/  free (struct usb_device*) ; 
 int /*<<< orphan*/ * libusb20_be_alloc_default () ; 
 int /*<<< orphan*/  libusb20_be_dequeue_device (int /*<<< orphan*/ *,struct libusb20_device*) ; 
 struct libusb20_device* libusb20_be_device_foreach (int /*<<< orphan*/ *,struct libusb20_device*) ; 
 int /*<<< orphan*/  libusb20_be_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libusb20_dev_close (struct libusb20_device*) ; 
 int /*<<< orphan*/  libusb20_dev_free (struct libusb20_device*) ; 
 int libusb20_dev_get_address (struct libusb20_device*) ; 
 int libusb20_dev_get_bus_number (struct libusb20_device*) ; 
 struct LIBUSB20_DEVICE_DESC_DECODED* libusb20_dev_get_device_desc (struct libusb20_device*) ; 
 int libusb20_dev_open (struct libusb20_device*,int /*<<< orphan*/ ) ; 
 struct usb_device* malloc (int) ; 
 int /*<<< orphan*/  memset (struct usb_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int) ; 
 int /*<<< orphan*/ * usb_backend ; 
 int /*<<< orphan*/  usb_fetch_and_parse_descriptors (void*) ; 
 TYPE_2__ usb_global_bus ; 

int
usb_find_devices(void)
{
	struct libusb20_device *pdev;
	struct usb_device *udev;
	struct LIBUSB20_DEVICE_DESC_DECODED *ddesc;
	int devnum;
	int err;

	/* cleanup after last device search */
	/* close all opened devices, if any */

	while ((pdev = libusb20_be_device_foreach(usb_backend, NULL))) {
		udev = pdev->privLuData;
		libusb20_be_dequeue_device(usb_backend, pdev);
		libusb20_dev_free(pdev);
		if (udev != NULL) {
			LIST_DEL(usb_global_bus.devices, udev);
			free(udev);
		}
	}

	/* free old USB backend, if any */

	libusb20_be_free(usb_backend);

	/* do a new backend device search */
	usb_backend = libusb20_be_alloc_default();
	if (usb_backend == NULL) {
		return (-1);
	}
	/* iterate all devices */

	devnum = 1;
	pdev = NULL;
	while ((pdev = libusb20_be_device_foreach(usb_backend, pdev))) {
		udev = malloc(sizeof(*udev));
		if (udev == NULL)
			break;

		memset(udev, 0, sizeof(*udev));

		udev->bus = &usb_global_bus;

		snprintf(udev->filename, sizeof(udev->filename),
		    "/dev/ugen%u.%u",
		    libusb20_dev_get_bus_number(pdev),
		    libusb20_dev_get_address(pdev));

		ddesc = libusb20_dev_get_device_desc(pdev);

		udev->descriptor.bLength = sizeof(udev->descriptor);
		udev->descriptor.bDescriptorType = ddesc->bDescriptorType;
		udev->descriptor.bcdUSB = ddesc->bcdUSB;
		udev->descriptor.bDeviceClass = ddesc->bDeviceClass;
		udev->descriptor.bDeviceSubClass = ddesc->bDeviceSubClass;
		udev->descriptor.bDeviceProtocol = ddesc->bDeviceProtocol;
		udev->descriptor.bMaxPacketSize0 = ddesc->bMaxPacketSize0;
		udev->descriptor.idVendor = ddesc->idVendor;
		udev->descriptor.idProduct = ddesc->idProduct;
		udev->descriptor.bcdDevice = ddesc->bcdDevice;
		udev->descriptor.iManufacturer = ddesc->iManufacturer;
		udev->descriptor.iProduct = ddesc->iProduct;
		udev->descriptor.iSerialNumber = ddesc->iSerialNumber;
		udev->descriptor.bNumConfigurations =
		    ddesc->bNumConfigurations;
		if (udev->descriptor.bNumConfigurations > USB_MAXCONFIG) {
			/* truncate number of configurations */
			udev->descriptor.bNumConfigurations = USB_MAXCONFIG;
		}
		udev->devnum = devnum++;
		/* link together the two structures */
		udev->dev = pdev;
		pdev->privLuData = udev;

		err = libusb20_dev_open(pdev, 0);
		if (err == 0) {
			/* XXX get all config descriptors by default */
			usb_fetch_and_parse_descriptors((void *)pdev);
			libusb20_dev_close(pdev);
		}
		LIST_ADD(usb_global_bus.devices, udev);
	}

	return (devnum - 1);			/* success */
}