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
typedef  scalar_t__ uint32_t ;
struct bcm2835_mbox_tag_hdr {scalar_t__ tag; int val_len; int val_buf_size; } ;
struct bcm2835_mbox_hdr {scalar_t__ code; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  scalar_t__ bus_addr_t ;

/* Variables and functions */
 scalar_t__ BCM2835_MBOX_CODE_RESP_SUCCESS ; 
 int BCM2835_MBOX_TAG_VAL_LEN_RESPONSE ; 
 int EIO ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int
bcm2835_mbox_err(device_t dev, bus_addr_t msg_phys, uint32_t resp_phys,
	struct bcm2835_mbox_hdr *msg, size_t len)
{
	int idx;
	struct bcm2835_mbox_tag_hdr *tag;
	uint8_t *last;

	if ((uint32_t)msg_phys != resp_phys) {
		device_printf(dev, "response channel mismatch\n");
		return (EIO);
	}
	if (msg->code != BCM2835_MBOX_CODE_RESP_SUCCESS) {
		device_printf(dev, "mbox response error\n");
		return (EIO);
	}

	/* Loop until the end tag. */
	tag = (struct bcm2835_mbox_tag_hdr *)(msg + 1);
	last = (uint8_t *)msg + len;
	for (idx = 0; tag->tag != 0; idx++) {
		if ((tag->val_len & BCM2835_MBOX_TAG_VAL_LEN_RESPONSE) == 0) {
			device_printf(dev, "tag %d response error\n", idx);
			return (EIO);
		}
		/* Clear the response bit. */
		tag->val_len &= ~BCM2835_MBOX_TAG_VAL_LEN_RESPONSE;

		/* Next tag. */
		tag = (struct bcm2835_mbox_tag_hdr *)((uint8_t *)tag +
		    sizeof(*tag) + tag->val_buf_size);

		if ((uint8_t *)tag > last) {
			device_printf(dev, "mbox buffer size error\n");
			return (EIO);
		}
	}

	return (0);
}