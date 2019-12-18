#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
struct scmi_xfers_info {int dummy; } ;
struct TYPE_8__ {int poll_completion; void* protocol_id; void* id; } ;
struct TYPE_6__ {size_t len; } ;
struct TYPE_5__ {size_t len; } ;
struct scmi_xfer {TYPE_4__ hdr; TYPE_2__ rx; TYPE_1__ tx; } ;
struct scmi_info {TYPE_3__* desc; struct device* dev; struct scmi_xfers_info tx_minfo; } ;
struct scmi_handle {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_7__ {size_t max_msg_size; } ;

/* Variables and functions */
 int ERANGE ; 
 scalar_t__ IS_ERR (struct scmi_xfer*) ; 
 int PTR_ERR (struct scmi_xfer*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct scmi_info* handle_to_scmi_info (struct scmi_handle const*) ; 
 struct scmi_xfer* scmi_xfer_get (struct scmi_handle const*,struct scmi_xfers_info*) ; 

int scmi_xfer_get_init(const struct scmi_handle *handle, u8 msg_id, u8 prot_id,
		       size_t tx_size, size_t rx_size, struct scmi_xfer **p)
{
	int ret;
	struct scmi_xfer *xfer;
	struct scmi_info *info = handle_to_scmi_info(handle);
	struct scmi_xfers_info *minfo = &info->tx_minfo;
	struct device *dev = info->dev;

	/* Ensure we have sane transfer sizes */
	if (rx_size > info->desc->max_msg_size ||
	    tx_size > info->desc->max_msg_size)
		return -ERANGE;

	xfer = scmi_xfer_get(handle, minfo);
	if (IS_ERR(xfer)) {
		ret = PTR_ERR(xfer);
		dev_err(dev, "failed to get free message slot(%d)\n", ret);
		return ret;
	}

	xfer->tx.len = tx_size;
	xfer->rx.len = rx_size ? : info->desc->max_msg_size;
	xfer->hdr.id = msg_id;
	xfer->hdr.protocol_id = prot_id;
	xfer->hdr.poll_completion = false;

	*p = xfer;

	return 0;
}