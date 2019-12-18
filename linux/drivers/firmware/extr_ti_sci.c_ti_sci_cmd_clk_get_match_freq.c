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
typedef  void* u64 ;
typedef  int u32 ;
typedef  struct ti_sci_xfer {scalar_t__ xfer_buf; } const ti_sci_xfer ;
struct ti_sci_msg_resp_query_clock_freq {void* freq_hz; } ;
struct ti_sci_msg_req_query_clock_freq {int dev_id; int clk_id; int clk_id_32; void* max_freq_hz; void* target_freq_hz; void* min_freq_hz; } ;
struct ti_sci_info {int /*<<< orphan*/  minfo; struct device* dev; } ;
struct ti_sci_handle {scalar_t__ xfer_buf; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ IS_ERR (struct ti_sci_xfer const*) ; 
 int PTR_ERR (struct ti_sci_xfer const*) ; 
 int /*<<< orphan*/  TI_SCI_FLAG_REQ_ACK_ON_PROCESSED ; 
 int /*<<< orphan*/  TI_SCI_MSG_QUERY_CLOCK_FREQ ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct ti_sci_info* handle_to_ti_sci_info (struct ti_sci_xfer const*) ; 
 int ti_sci_do_xfer (struct ti_sci_info*,struct ti_sci_xfer const*) ; 
 struct ti_sci_xfer* ti_sci_get_one_xfer (struct ti_sci_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ti_sci_is_response_ack (struct ti_sci_msg_resp_query_clock_freq*) ; 
 int /*<<< orphan*/  ti_sci_put_one_xfer (int /*<<< orphan*/ *,struct ti_sci_xfer const*) ; 

__attribute__((used)) static int ti_sci_cmd_clk_get_match_freq(const struct ti_sci_handle *handle,
					 u32 dev_id, u32 clk_id, u64 min_freq,
					 u64 target_freq, u64 max_freq,
					 u64 *match_freq)
{
	struct ti_sci_info *info;
	struct ti_sci_msg_req_query_clock_freq *req;
	struct ti_sci_msg_resp_query_clock_freq *resp;
	struct ti_sci_xfer *xfer;
	struct device *dev;
	int ret = 0;

	if (IS_ERR(handle))
		return PTR_ERR(handle);
	if (!handle || !match_freq)
		return -EINVAL;

	info = handle_to_ti_sci_info(handle);
	dev = info->dev;

	xfer = ti_sci_get_one_xfer(info, TI_SCI_MSG_QUERY_CLOCK_FREQ,
				   TI_SCI_FLAG_REQ_ACK_ON_PROCESSED,
				   sizeof(*req), sizeof(*resp));
	if (IS_ERR(xfer)) {
		ret = PTR_ERR(xfer);
		dev_err(dev, "Message alloc failed(%d)\n", ret);
		return ret;
	}
	req = (struct ti_sci_msg_req_query_clock_freq *)xfer->xfer_buf;
	req->dev_id = dev_id;
	if (clk_id < 255) {
		req->clk_id = clk_id;
	} else {
		req->clk_id = 255;
		req->clk_id_32 = clk_id;
	}
	req->min_freq_hz = min_freq;
	req->target_freq_hz = target_freq;
	req->max_freq_hz = max_freq;

	ret = ti_sci_do_xfer(info, xfer);
	if (ret) {
		dev_err(dev, "Mbox send fail %d\n", ret);
		goto fail;
	}

	resp = (struct ti_sci_msg_resp_query_clock_freq *)xfer->xfer_buf;

	if (!ti_sci_is_response_ack(resp))
		ret = -ENODEV;
	else
		*match_freq = resp->freq_hz;

fail:
	ti_sci_put_one_xfer(&info->minfo, xfer);

	return ret;
}