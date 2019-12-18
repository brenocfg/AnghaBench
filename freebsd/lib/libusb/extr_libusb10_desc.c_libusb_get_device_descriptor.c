#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct libusb_device_descriptor {int /*<<< orphan*/  bNumConfigurations; int /*<<< orphan*/  iSerialNumber; int /*<<< orphan*/  iProduct; int /*<<< orphan*/  iManufacturer; int /*<<< orphan*/  bcdDevice; int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; int /*<<< orphan*/  bMaxPacketSize0; int /*<<< orphan*/  bDeviceProtocol; int /*<<< orphan*/  bDeviceSubClass; int /*<<< orphan*/  bDeviceClass; int /*<<< orphan*/  bcdUSB; int /*<<< orphan*/  bDescriptorType; int /*<<< orphan*/  bLength; } ;
struct libusb20_device {int dummy; } ;
struct LIBUSB20_DEVICE_DESC_DECODED {int /*<<< orphan*/  bNumConfigurations; int /*<<< orphan*/  iSerialNumber; int /*<<< orphan*/  iProduct; int /*<<< orphan*/  iManufacturer; int /*<<< orphan*/  bcdDevice; int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; int /*<<< orphan*/  bMaxPacketSize0; int /*<<< orphan*/  bDeviceProtocol; int /*<<< orphan*/  bDeviceSubClass; int /*<<< orphan*/  bDeviceClass; int /*<<< orphan*/  bcdUSB; int /*<<< orphan*/  bDescriptorType; int /*<<< orphan*/  bLength; } ;
struct TYPE_3__ {struct libusb20_device* os_priv; } ;
typedef  TYPE_1__ libusb_device ;

/* Variables and functions */
 int LIBUSB_ERROR_INVALID_PARAM ; 
 struct LIBUSB20_DEVICE_DESC_DECODED* libusb20_dev_get_device_desc (struct libusb20_device*) ; 

int
libusb_get_device_descriptor(libusb_device *dev,
    struct libusb_device_descriptor *desc)
{
	struct LIBUSB20_DEVICE_DESC_DECODED *pdesc;
	struct libusb20_device *pdev;

	if ((dev == NULL) || (desc == NULL))
		return (LIBUSB_ERROR_INVALID_PARAM);

	pdev = dev->os_priv;
	pdesc = libusb20_dev_get_device_desc(pdev);

	desc->bLength = pdesc->bLength;
	desc->bDescriptorType = pdesc->bDescriptorType;
	desc->bcdUSB = pdesc->bcdUSB;
	desc->bDeviceClass = pdesc->bDeviceClass;
	desc->bDeviceSubClass = pdesc->bDeviceSubClass;
	desc->bDeviceProtocol = pdesc->bDeviceProtocol;
	desc->bMaxPacketSize0 = pdesc->bMaxPacketSize0;
	desc->idVendor = pdesc->idVendor;
	desc->idProduct = pdesc->idProduct;
	desc->bcdDevice = pdesc->bcdDevice;
	desc->iManufacturer = pdesc->iManufacturer;
	desc->iProduct = pdesc->iProduct;
	desc->iSerialNumber = pdesc->iSerialNumber;
	desc->bNumConfigurations = pdesc->bNumConfigurations;

	return (0);
}