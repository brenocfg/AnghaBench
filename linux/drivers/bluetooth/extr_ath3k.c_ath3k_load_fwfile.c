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
typedef  int /*<<< orphan*/  u8 ;
struct usb_device {int dummy; } ;
struct firmware {int size; scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH3K_DNLOAD ; 
 int /*<<< orphan*/  BT_ERR (char*) ; 
 int /*<<< orphan*/  BULK_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FW_HDR_SIZE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  TIMEGAP_USEC_MAX ; 
 int /*<<< orphan*/  TIMEGAP_USEC_MIN ; 
 int /*<<< orphan*/  USB_CTRL_SET_TIMEOUT ; 
 int /*<<< orphan*/  USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  ath3k_log_failed_loading (int,int,int,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int min_t (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uint ; 
 int usb_bulk_msg (struct usb_device*,int,int /*<<< orphan*/ *,int,int*,int) ; 
 int usb_control_msg (struct usb_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int usb_sndbulkpipe (struct usb_device*,int) ; 
 int usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath3k_load_fwfile(struct usb_device *udev,
		const struct firmware *firmware)
{
	u8 *send_buf;
	int len = 0;
	int err, pipe, size, count, sent = 0;
	int ret;

	count = firmware->size;

	send_buf = kmalloc(BULK_SIZE, GFP_KERNEL);
	if (!send_buf) {
		BT_ERR("Can't allocate memory chunk for firmware");
		return -ENOMEM;
	}

	size = min_t(uint, count, FW_HDR_SIZE);
	memcpy(send_buf, firmware->data, size);

	pipe = usb_sndctrlpipe(udev, 0);
	ret = usb_control_msg(udev, pipe, ATH3K_DNLOAD,
			USB_TYPE_VENDOR, 0, 0, send_buf,
			size, USB_CTRL_SET_TIMEOUT);
	if (ret < 0) {
		BT_ERR("Can't change to loading configuration err");
		kfree(send_buf);
		return ret;
	}

	sent += size;
	count -= size;

	pipe = usb_sndbulkpipe(udev, 0x02);

	while (count) {
		/* workaround the compatibility issue with xHCI controller*/
		usleep_range(TIMEGAP_USEC_MIN, TIMEGAP_USEC_MAX);

		size = min_t(uint, count, BULK_SIZE);
		memcpy(send_buf, firmware->data + sent, size);

		err = usb_bulk_msg(udev, pipe, send_buf, size,
					&len, 3000);
		if (err || (len != size)) {
			ath3k_log_failed_loading(err, len, size, count);
			kfree(send_buf);
			return err;
		}
		sent  += size;
		count -= size;
	}

	kfree(send_buf);
	return 0;
}