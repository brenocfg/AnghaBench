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
typedef  size_t u8 ;
struct ti_sci_xfers_info {struct ti_sci_xfer* xfer_block; int /*<<< orphan*/  xfer_alloc_table; } ;
struct ti_sci_xfer {scalar_t__ rx_len; int /*<<< orphan*/  done; int /*<<< orphan*/  xfer_buf; } ;
struct ti_sci_msg_hdr {size_t seq; } ;
struct ti_sci_info {TYPE_1__* desc; struct ti_sci_xfers_info minfo; struct device* dev; } ;
struct ti_msgmgr_message {scalar_t__ len; scalar_t__ buf; } ;
struct mbox_client {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {scalar_t__ max_msg_size; } ;

/* Variables and functions */
 struct ti_sci_info* cl_to_ti_sci_info (struct mbox_client*) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  test_bit (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_sci_dump_header_dbg (struct device*,struct ti_sci_msg_hdr*) ; 

__attribute__((used)) static void ti_sci_rx_callback(struct mbox_client *cl, void *m)
{
	struct ti_sci_info *info = cl_to_ti_sci_info(cl);
	struct device *dev = info->dev;
	struct ti_sci_xfers_info *minfo = &info->minfo;
	struct ti_msgmgr_message *mbox_msg = m;
	struct ti_sci_msg_hdr *hdr = (struct ti_sci_msg_hdr *)mbox_msg->buf;
	struct ti_sci_xfer *xfer;
	u8 xfer_id;

	xfer_id = hdr->seq;

	/*
	 * Are we even expecting this?
	 * NOTE: barriers were implicit in locks used for modifying the bitmap
	 */
	if (!test_bit(xfer_id, minfo->xfer_alloc_table)) {
		dev_err(dev, "Message for %d is not expected!\n", xfer_id);
		return;
	}

	xfer = &minfo->xfer_block[xfer_id];

	/* Is the message of valid length? */
	if (mbox_msg->len > info->desc->max_msg_size) {
		dev_err(dev, "Unable to handle %zu xfer(max %d)\n",
			mbox_msg->len, info->desc->max_msg_size);
		ti_sci_dump_header_dbg(dev, hdr);
		return;
	}
	if (mbox_msg->len < xfer->rx_len) {
		dev_err(dev, "Recv xfer %zu < expected %d length\n",
			mbox_msg->len, xfer->rx_len);
		ti_sci_dump_header_dbg(dev, hdr);
		return;
	}

	ti_sci_dump_header_dbg(dev, hdr);
	/* Take a copy to the rx buffer.. */
	memcpy(xfer->xfer_buf, mbox_msg->buf, xfer->rx_len);
	complete(&xfer->done);
}