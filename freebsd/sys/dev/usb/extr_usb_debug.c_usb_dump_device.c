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
struct TYPE_2__ {int self_powered; } ;
struct usb_device {int address; int curr_config_no; int depth; int speed; int power; int langid; TYPE_1__ flags; int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,struct usb_device*,...) ; 

void
usb_dump_device(struct usb_device *udev)
{
	printf("usb_dump_device: dev=%p\n", udev);
	if (udev == NULL) {
		return;
	}
	printf(" bus=%p \n"
	    " address=%d config=%d depth=%d speed=%d self_powered=%d\n"
	    " power=%d langid=%d\n",
	    udev->bus,
	    udev->address, udev->curr_config_no, udev->depth, udev->speed,
	    udev->flags.self_powered, udev->power, udev->langid);
}