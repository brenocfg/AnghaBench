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
typedef  int /*<<< orphan*/  usb_error_t ;
typedef  int uint16_t ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_ERR_INVAL ; 
#define  USB_TEMP_AUDIO 139 
#define  USB_TEMP_CDCE 138 
#define  USB_TEMP_CDCEEM 137 
#define  USB_TEMP_KBD 136 
#define  USB_TEMP_MIDI 135 
#define  USB_TEMP_MODEM 134 
#define  USB_TEMP_MOUSE 133 
#define  USB_TEMP_MSC 132 
#define  USB_TEMP_MTP 131 
#define  USB_TEMP_MULTI 130 
#define  USB_TEMP_PHONE 129 
#define  USB_TEMP_SERIALNET 128 
 int /*<<< orphan*/  usb_temp_setup (struct usb_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_template_audio ; 
 int /*<<< orphan*/  usb_template_cdce ; 
 int /*<<< orphan*/  usb_template_cdceem ; 
 int /*<<< orphan*/  usb_template_kbd ; 
 int /*<<< orphan*/  usb_template_midi ; 
 int /*<<< orphan*/  usb_template_modem ; 
 int /*<<< orphan*/  usb_template_mouse ; 
 int /*<<< orphan*/  usb_template_msc ; 
 int /*<<< orphan*/  usb_template_mtp ; 
 int /*<<< orphan*/  usb_template_multi ; 
 int /*<<< orphan*/  usb_template_phone ; 
 int /*<<< orphan*/  usb_template_serialnet ; 

__attribute__((used)) static usb_error_t
usb_temp_setup_by_index(struct usb_device *udev, uint16_t index)
{
	usb_error_t err;

	switch (index) {
	case USB_TEMP_MSC:
		err = usb_temp_setup(udev, &usb_template_msc);
		break;
	case USB_TEMP_CDCE:
		err = usb_temp_setup(udev, &usb_template_cdce);
		break;
	case USB_TEMP_MTP:
		err = usb_temp_setup(udev, &usb_template_mtp);
		break;
	case USB_TEMP_MODEM:
		err = usb_temp_setup(udev, &usb_template_modem);
		break;
	case USB_TEMP_AUDIO:
		err = usb_temp_setup(udev, &usb_template_audio);
		break;
	case USB_TEMP_KBD:
		err = usb_temp_setup(udev, &usb_template_kbd);
		break;
	case USB_TEMP_MOUSE:
		err = usb_temp_setup(udev, &usb_template_mouse);
		break;
	case USB_TEMP_PHONE:
		err = usb_temp_setup(udev, &usb_template_phone);
		break;
	case USB_TEMP_SERIALNET:
		err = usb_temp_setup(udev, &usb_template_serialnet);
		break;
	case USB_TEMP_MIDI:
		err = usb_temp_setup(udev, &usb_template_midi);
		break;
	case USB_TEMP_MULTI:
		err = usb_temp_setup(udev, &usb_template_multi);
		break;
	case USB_TEMP_CDCEEM:
		err = usb_temp_setup(udev, &usb_template_cdceem);
		break;
	default:
		return (USB_ERR_INVAL);
	}

	return (err);
}