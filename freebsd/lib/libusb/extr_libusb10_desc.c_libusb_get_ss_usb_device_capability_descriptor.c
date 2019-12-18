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
struct libusb_ss_usb_device_capability_descriptor {scalar_t__ bDevCapabilityType; int bmAttributes; int wSpeedSupported; int bFunctionalitySupport; int bU1DevExitLat; int wU2DevExitLat; int /*<<< orphan*/  bDescriptorType; scalar_t__ bLength; } ;
struct libusb_context {int dummy; } ;
struct libusb_bos_dev_capability_descriptor {scalar_t__ bDevCapabilityType; scalar_t__ bLength; int* dev_capability_data; int /*<<< orphan*/  bDescriptorType; } ;

/* Variables and functions */
 scalar_t__ LIBUSB_BT_SS_USB_DEVICE_CAPABILITY ; 
 scalar_t__ LIBUSB_BT_SS_USB_DEVICE_CAPABILITY_SIZE ; 
 int LIBUSB_ERROR_INVALID_PARAM ; 
 int LIBUSB_ERROR_IO ; 
 int LIBUSB_ERROR_NO_MEM ; 
 struct libusb_ss_usb_device_capability_descriptor* malloc (int) ; 

int
libusb_get_ss_usb_device_capability_descriptor(struct libusb_context *ctx,
    struct libusb_bos_dev_capability_descriptor *dev_cap,
    struct libusb_ss_usb_device_capability_descriptor **ss_usb_device_capability)
{
	struct libusb_ss_usb_device_capability_descriptor *desc;

	if (dev_cap == NULL || ss_usb_device_capability == NULL ||
	    dev_cap->bDevCapabilityType != LIBUSB_BT_SS_USB_DEVICE_CAPABILITY)
		return (LIBUSB_ERROR_INVALID_PARAM);
	if (dev_cap->bLength < LIBUSB_BT_SS_USB_DEVICE_CAPABILITY_SIZE)
		return (LIBUSB_ERROR_IO);

	desc = malloc(sizeof(*desc));
	if (desc == NULL)
		return (LIBUSB_ERROR_NO_MEM);

	desc->bLength = LIBUSB_BT_SS_USB_DEVICE_CAPABILITY_SIZE;
	desc->bDescriptorType = dev_cap->bDescriptorType;
	desc->bDevCapabilityType = dev_cap->bDevCapabilityType;
	desc->bmAttributes = dev_cap->dev_capability_data[0];
	desc->wSpeedSupported = dev_cap->dev_capability_data[1] |
	    (dev_cap->dev_capability_data[2] << 8);
	desc->bFunctionalitySupport = dev_cap->dev_capability_data[3];
	desc->bU1DevExitLat = dev_cap->dev_capability_data[4];
	desc->wU2DevExitLat = dev_cap->dev_capability_data[5] |
	    (dev_cap->dev_capability_data[6] << 8);

	*ss_usb_device_capability = desc;
	return (0);
}