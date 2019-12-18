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
struct usb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_CTRL_SET_TIMEOUT ; 
 int /*<<< orphan*/  USB_REG_SWITCH_VID_PID ; 
 int /*<<< orphan*/  USB_TYPE_VENDOR ; 
 int usb_control_msg (struct usb_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath3k_switch_pid(struct usb_device *udev)
{
	int pipe = 0;

	pipe = usb_sndctrlpipe(udev, 0);
	return usb_control_msg(udev, pipe, USB_REG_SWITCH_VID_PID,
			USB_TYPE_VENDOR, 0, 0,
			NULL, 0, USB_CTRL_SET_TIMEOUT);
}