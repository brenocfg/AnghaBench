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
 int /*<<< orphan*/  ATH3K_GETSTATE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  USB_CTRL_SET_TIMEOUT ; 
 int USB_DIR_IN ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int usb_control_msg (struct usb_device*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath3k_get_state(struct usb_device *udev, unsigned char *state)
{
	int ret, pipe = 0;
	char *buf;

	buf = kmalloc(sizeof(*buf), GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	pipe = usb_rcvctrlpipe(udev, 0);
	ret = usb_control_msg(udev, pipe, ATH3K_GETSTATE,
			      USB_TYPE_VENDOR | USB_DIR_IN, 0, 0,
			      buf, sizeof(*buf), USB_CTRL_SET_TIMEOUT);

	*state = *buf;
	kfree(buf);

	return ret;
}