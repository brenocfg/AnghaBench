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
typedef  void* u8 ;
typedef  void* u32 ;
typedef  void* u16 ;
struct ti_sci_xfer {scalar_t__ xfer_buf; } ;
struct ti_sci_msg_rm_ring_cfg_req {void* order_id; void* size; void* mode; void* count; void* addr_hi; void* addr_lo; void* index; void* nav_id; void* valid_params; } ;
struct ti_sci_msg_hdr {int dummy; } ;
struct ti_sci_info {int /*<<< orphan*/  minfo; struct device* dev; } ;
struct ti_sci_handle {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ IS_ERR (struct ti_sci_xfer*) ; 
 scalar_t__ IS_ERR_OR_NULL (struct ti_sci_handle const*) ; 
 int PTR_ERR (struct ti_sci_xfer*) ; 
 int /*<<< orphan*/  TI_SCI_FLAG_REQ_ACK_ON_PROCESSED ; 
 int /*<<< orphan*/  TI_SCI_MSG_RM_RING_CFG ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,void*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct ti_sci_info* handle_to_ti_sci_info (struct ti_sci_handle const*) ; 
 int ti_sci_do_xfer (struct ti_sci_info*,struct ti_sci_xfer*) ; 
 struct ti_sci_xfer* ti_sci_get_one_xfer (struct ti_sci_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ ti_sci_is_response_ack (struct ti_sci_msg_hdr*) ; 
 int /*<<< orphan*/  ti_sci_put_one_xfer (int /*<<< orphan*/ *,struct ti_sci_xfer*) ; 

__attribute__((used)) static int ti_sci_cmd_ring_config(const struct ti_sci_handle *handle,
				  u32 valid_params, u16 nav_id, u16 index,
				  u32 addr_lo, u32 addr_hi, u32 count,
				  u8 mode, u8 size, u8 order_id)
{
	struct ti_sci_msg_rm_ring_cfg_req *req;
	struct ti_sci_msg_hdr *resp;
	struct ti_sci_xfer *xfer;
	struct ti_sci_info *info;
	struct device *dev;
	int ret = 0;

	if (IS_ERR_OR_NULL(handle))
		return -EINVAL;

	info = handle_to_ti_sci_info(handle);
	dev = info->dev;

	xfer = ti_sci_get_one_xfer(info, TI_SCI_MSG_RM_RING_CFG,
				   TI_SCI_FLAG_REQ_ACK_ON_PROCESSED,
				   sizeof(*req), sizeof(*resp));
	if (IS_ERR(xfer)) {
		ret = PTR_ERR(xfer);
		dev_err(dev, "RM_RA:Message config failed(%d)\n", ret);
		return ret;
	}
	req = (struct ti_sci_msg_rm_ring_cfg_req *)xfer->xfer_buf;
	req->valid_params = valid_params;
	req->nav_id = nav_id;
	req->index = index;
	req->addr_lo = addr_lo;
	req->addr_hi = addr_hi;
	req->count = count;
	req->mode = mode;
	req->size = size;
	req->order_id = order_id;

	ret = ti_sci_do_xfer(info, xfer);
	if (ret) {
		dev_err(dev, "RM_RA:Mbox config send fail %d\n", ret);
		goto fail;
	}

	resp = (struct ti_sci_msg_hdr *)xfer->xfer_buf;
	ret = ti_sci_is_response_ack(resp) ? 0 : -ENODEV;

fail:
	ti_sci_put_one_xfer(&info->minfo, xfer);
	dev_dbg(dev, "RM_RA:config ring %u ret:%d\n", index, ret);
	return ret;
}