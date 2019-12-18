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
typedef  int /*<<< orphan*/  uint8_t ;
struct usb_device {int /*<<< orphan*/  enum_sx; } ;

/* Variables and functions */
 int /*<<< orphan*/  sx_xlocked (int /*<<< orphan*/ *) ; 

uint8_t
usbd_enum_is_locked(struct usb_device *udev)
{
	return (sx_xlocked(&udev->enum_sx));
}