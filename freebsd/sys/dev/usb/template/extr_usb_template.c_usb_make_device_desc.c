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
typedef  int uint16_t ;
struct usb_temp_setup {int size; int bConfigurationValue; int usb_speed; int /*<<< orphan*/  err; scalar_t__ buf; } ;
struct usb_temp_device_desc {int idVendor; int idProduct; int bcdDevice; int /*<<< orphan*/  bDeviceProtocol; int /*<<< orphan*/  bDeviceSubClass; int /*<<< orphan*/  bDeviceClass; int /*<<< orphan*/  iSerialNumber; int /*<<< orphan*/  iProduct; int /*<<< orphan*/  iManufacturer; struct usb_temp_config_desc** ppConfigDesc; } ;
struct TYPE_4__ {int bLength; int bNumConfigurations; int bMaxPacketSize; int /*<<< orphan*/  bcdUSB; int /*<<< orphan*/  iSerialNumber; int /*<<< orphan*/  iProduct; int /*<<< orphan*/  iManufacturer; int /*<<< orphan*/  bcdDevice; int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; int /*<<< orphan*/  bDeviceProtocol; int /*<<< orphan*/  bDeviceSubClass; int /*<<< orphan*/  bDeviceClass; int /*<<< orphan*/  bDescriptorType; } ;
struct TYPE_3__ {int bLength; scalar_t__ bMaxPacketSize0; int /*<<< orphan*/  bcdUSB; scalar_t__ bNumConfigurations; int /*<<< orphan*/  bDeviceProtocol; int /*<<< orphan*/  bDeviceSubClass; int /*<<< orphan*/  bDeviceClass; int /*<<< orphan*/  bDescriptorType; } ;
struct usb_temp_data {TYPE_2__ udd; TYPE_1__ udq; struct usb_temp_device_desc const* tdd; } ;
struct usb_temp_config_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UDESC_DEVICE ; 
 int /*<<< orphan*/  UDESC_DEVICE_QUALIFIER ; 
 struct usb_temp_data* USB_ADD_BYTES (scalar_t__,int) ; 
 int /*<<< orphan*/  USB_ERR_INVAL ; 
#define  USB_SPEED_FULL 132 
#define  USB_SPEED_HIGH 131 
#define  USB_SPEED_LOW 130 
#define  USB_SPEED_SUPER 129 
#define  USB_SPEED_VARIABLE 128 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_make_config_desc (struct usb_temp_setup*,struct usb_temp_config_desc const*) ; 

__attribute__((used)) static void
usb_make_device_desc(struct usb_temp_setup *temp,
    const struct usb_temp_device_desc *tdd)
{
	struct usb_temp_data *utd;
	const struct usb_temp_config_desc **tcd;
	uint16_t old_size;

	/* Reserve memory */

	old_size = temp->size;
	temp->size += sizeof(*utd);

	/* Scan all the USB configs */

	temp->bConfigurationValue = 1;
	tcd = tdd->ppConfigDesc;
	if (tcd) {
		while (*tcd) {
			usb_make_config_desc(temp, *tcd);
			temp->bConfigurationValue++;
			tcd++;
		}
	}
	/*
	 * Fill out the real USB device descriptor
	 * in case there is a buffer present:
	 */

	if (temp->buf) {
		utd = USB_ADD_BYTES(temp->buf, old_size);

		/* Store a pointer to our template device descriptor */
		utd->tdd = tdd;

		/* Fill out USB device descriptor */
		utd->udd.bLength = sizeof(utd->udd);
		utd->udd.bDescriptorType = UDESC_DEVICE;
		utd->udd.bDeviceClass = tdd->bDeviceClass;
		utd->udd.bDeviceSubClass = tdd->bDeviceSubClass;
		utd->udd.bDeviceProtocol = tdd->bDeviceProtocol;
		USETW(utd->udd.idVendor, tdd->idVendor);
		USETW(utd->udd.idProduct, tdd->idProduct);
		USETW(utd->udd.bcdDevice, tdd->bcdDevice);
		utd->udd.iManufacturer = tdd->iManufacturer;
		utd->udd.iProduct = tdd->iProduct;
		utd->udd.iSerialNumber = tdd->iSerialNumber;
		utd->udd.bNumConfigurations = temp->bConfigurationValue - 1;

		/*
		 * Fill out the USB device qualifier. Pretend that we
		 * don't support any other speeds by setting
		 * "bNumConfigurations" equal to zero. That saves us
		 * generating an extra set of configuration
		 * descriptors.
		 */
		utd->udq.bLength = sizeof(utd->udq);
		utd->udq.bDescriptorType = UDESC_DEVICE_QUALIFIER;
		utd->udq.bDeviceClass = tdd->bDeviceClass;
		utd->udq.bDeviceSubClass = tdd->bDeviceSubClass;
		utd->udq.bDeviceProtocol = tdd->bDeviceProtocol;
		utd->udq.bNumConfigurations = 0;
		USETW(utd->udq.bcdUSB, 0x0200);
		utd->udq.bMaxPacketSize0 = 0;

		switch (temp->usb_speed) {
		case USB_SPEED_LOW:
			USETW(utd->udd.bcdUSB, 0x0110);
			utd->udd.bMaxPacketSize = 8;
			break;
		case USB_SPEED_FULL:
			USETW(utd->udd.bcdUSB, 0x0110);
			utd->udd.bMaxPacketSize = 32;
			break;
		case USB_SPEED_HIGH:
			USETW(utd->udd.bcdUSB, 0x0200);
			utd->udd.bMaxPacketSize = 64;
			break;
		case USB_SPEED_VARIABLE:
			USETW(utd->udd.bcdUSB, 0x0250);
			utd->udd.bMaxPacketSize = 255;	/* 512 bytes */
			break;
		case USB_SPEED_SUPER:
			USETW(utd->udd.bcdUSB, 0x0300);
			utd->udd.bMaxPacketSize = 9;	/* 2**9 = 512 bytes */
			break;
		default:
			temp->err = USB_ERR_INVAL;
			break;
		}
	}
}