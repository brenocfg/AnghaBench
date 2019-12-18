#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct usb_hub {int* uframe_usage; } ;
struct usb_device {TYPE_1__* parent_hs_hub; struct usb_bus* bus; } ;
struct usb_bus {int* uframe_usage; } ;
typedef  int int16_t ;
typedef  enum usb_dev_speed { ____Placeholder_usb_dev_speed } usb_dev_speed ;
struct TYPE_2__ {struct usb_hub* hub; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  USB_BUS_LOCK_ASSERT (struct usb_bus*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_FS_ISOC_UFRAME_MAX ; 
 int USB_HS_MICRO_FRAMES_MAX ; 
#define  USB_SPEED_FULL 129 
#define  USB_SPEED_LOW 128 
 int usb_intr_find_best_slot (int*,int /*<<< orphan*/ ,int,int) ; 
 int usbd_get_speed (struct usb_device*) ; 

__attribute__((used)) static uint8_t
usb_hs_bandwidth_adjust(struct usb_device *udev, int16_t len,
    uint8_t slot, uint8_t mask)
{
	struct usb_bus *bus = udev->bus;
	struct usb_hub *hub;
	enum usb_dev_speed speed;
	uint8_t x;

	USB_BUS_LOCK_ASSERT(bus, MA_OWNED);

	speed = usbd_get_speed(udev);

	switch (speed) {
	case USB_SPEED_LOW:
	case USB_SPEED_FULL:
		if (speed == USB_SPEED_LOW) {
			len *= 8;
		}
		/*
	         * The Host Controller Driver should have
	         * performed checks so that the lookup
	         * below does not result in a NULL pointer
	         * access.
	         */

		hub = udev->parent_hs_hub->hub;
		if (slot >= USB_HS_MICRO_FRAMES_MAX) {
			slot = usb_intr_find_best_slot(hub->uframe_usage,
			    USB_FS_ISOC_UFRAME_MAX, 6, mask);
		}
		for (x = slot; x < 8; x++) {
			if (mask & (1U << (x - slot))) {
				hub->uframe_usage[x] += len;
				bus->uframe_usage[x] += len;
			}
		}
		break;
	default:
		if (slot >= USB_HS_MICRO_FRAMES_MAX) {
			slot = usb_intr_find_best_slot(bus->uframe_usage, 0,
			    USB_HS_MICRO_FRAMES_MAX, mask);
		}
		for (x = slot; x < 8; x++) {
			if (mask & (1U << (x - slot))) {
				bus->uframe_usage[x] += len;
			}
		}
		break;
	}
	return (slot);
}