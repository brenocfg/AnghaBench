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
struct TYPE_3__ {int /*<<< orphan*/  os_priv; } ;
typedef  TYPE_1__ libusb_device ;
typedef  enum libusb_speed { ____Placeholder_libusb_speed } libusb_speed ;

/* Variables and functions */
#define  LIBUSB20_SPEED_FULL 131 
#define  LIBUSB20_SPEED_HIGH 130 
#define  LIBUSB20_SPEED_LOW 129 
#define  LIBUSB20_SPEED_SUPER 128 
 int LIBUSB_SPEED_FULL ; 
 int LIBUSB_SPEED_HIGH ; 
 int LIBUSB_SPEED_LOW ; 
 int LIBUSB_SPEED_SUPER ; 
 int LIBUSB_SPEED_UNKNOWN ; 
 int libusb20_dev_get_speed (int /*<<< orphan*/ ) ; 

enum libusb_speed
libusb_get_device_speed(libusb_device *dev)
{
	if (dev == NULL)
		return (LIBUSB_SPEED_UNKNOWN);	/* should not happen */

	switch (libusb20_dev_get_speed(dev->os_priv)) {
	case LIBUSB20_SPEED_LOW:
		return (LIBUSB_SPEED_LOW);
	case LIBUSB20_SPEED_FULL:
		return (LIBUSB_SPEED_FULL);
	case LIBUSB20_SPEED_HIGH:
		return (LIBUSB_SPEED_HIGH);
	case LIBUSB20_SPEED_SUPER:
		return (LIBUSB_SPEED_SUPER);
	default:
		break;
	}
	return (LIBUSB_SPEED_UNKNOWN);
}