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
typedef  enum usb_dev_speed { ____Placeholder_usb_dev_speed } usb_dev_speed ;
typedef  int /*<<< orphan*/  cvmx_usb_speed_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_USB_SPEED_FULL ; 
 int /*<<< orphan*/  CVMX_USB_SPEED_HIGH ; 
 int /*<<< orphan*/  CVMX_USB_SPEED_LOW ; 
#define  USB_SPEED_FULL 129 
#define  USB_SPEED_HIGH 128 

__attribute__((used)) static cvmx_usb_speed_t
octusb_convert_speed(enum usb_dev_speed speed)
{
	;				/* indent fix */
	switch (speed) {
	case USB_SPEED_HIGH:
		return (CVMX_USB_SPEED_HIGH);
	case USB_SPEED_FULL:
		return (CVMX_USB_SPEED_FULL);
	default:
		return (CVMX_USB_SPEED_LOW);
	}
}