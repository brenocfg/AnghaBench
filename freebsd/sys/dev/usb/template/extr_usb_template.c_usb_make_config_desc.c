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
struct usb_temp_setup {int bInterfaceNumber; int /*<<< orphan*/  bConfigurationValue; scalar_t__ size; scalar_t__ buf; scalar_t__ bAlternateSetting; } ;
struct usb_temp_interface_desc {int dummy; } ;
struct usb_temp_config_desc {int /*<<< orphan*/  bmAttributes; int /*<<< orphan*/  iConfiguration; struct usb_temp_interface_desc** ppIfaceDesc; } ;
struct usb_config_descriptor {int bLength; int bNumInterface; int bMaxPower; int /*<<< orphan*/  bmAttributes; int /*<<< orphan*/  iConfiguration; int /*<<< orphan*/  bConfigurationValue; int /*<<< orphan*/  wTotalLength; int /*<<< orphan*/  bDescriptorType; } ;

/* Variables and functions */
 int /*<<< orphan*/  UC_BUS_POWERED ; 
 int /*<<< orphan*/  UC_REMOTE_WAKEUP ; 
 int /*<<< orphan*/  UC_SELF_POWERED ; 
 int /*<<< orphan*/  UDESC_CONFIG ; 
 struct usb_config_descriptor* USB_ADD_BYTES (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  usb_make_interface_desc (struct usb_temp_setup*,struct usb_temp_interface_desc const*) ; 
 int usb_template_power ; 

__attribute__((used)) static void
usb_make_config_desc(struct usb_temp_setup *temp,
    const struct usb_temp_config_desc *tcd)
{
	struct usb_config_descriptor *cd;
	const struct usb_temp_interface_desc **tid;
	uint16_t old_size;
	int power;

	/* Reserve memory */

	old_size = temp->size;
	temp->size += sizeof(*cd);

	/* Reset some counters */

	temp->bInterfaceNumber = 0xFF;
	temp->bAlternateSetting = 0;

	/* Scan all the USB interfaces */

	tid = tcd->ppIfaceDesc;
	if (tid) {
		while (*tid) {
			usb_make_interface_desc(temp, *tid);
			tid++;
		}
	}
	/*
	 * Fill out the real USB config descriptor
	 * in case there is a buffer present:
	 */
	if (temp->buf) {
		cd = USB_ADD_BYTES(temp->buf, old_size);

		/* compute total size */
		old_size = temp->size - old_size;

		cd->bLength = sizeof(*cd);
		cd->bDescriptorType = UDESC_CONFIG;
		USETW(cd->wTotalLength, old_size);
		cd->bNumInterface = temp->bInterfaceNumber + 1;
		cd->bConfigurationValue = temp->bConfigurationValue;
		cd->iConfiguration = tcd->iConfiguration;
		cd->bmAttributes = tcd->bmAttributes;

		power = usb_template_power;
		cd->bMaxPower = power / 2; /* 2 mA units */
		cd->bmAttributes |= UC_REMOTE_WAKEUP;
		if (power > 0) {
			cd->bmAttributes |= UC_BUS_POWERED;
			cd->bmAttributes &= ~UC_SELF_POWERED;
		} else {
			cd->bmAttributes &= ~UC_BUS_POWERED;
			cd->bmAttributes |= UC_SELF_POWERED;
		}
	}
}