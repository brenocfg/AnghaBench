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
struct ti_sci_xfer {scalar_t__ xfer_buf; } ;
struct ti_sci_msg_rm_udmap_tx_ch_cfg_req {int /*<<< orphan*/  tx_burst_size; int /*<<< orphan*/  tx_sched_priority; int /*<<< orphan*/  fdepth; int /*<<< orphan*/  tx_orderid; int /*<<< orphan*/  tx_qos; int /*<<< orphan*/  tx_priority; int /*<<< orphan*/  txcq_qnum; int /*<<< orphan*/  tx_credit_count; int /*<<< orphan*/  tx_fetch_size; int /*<<< orphan*/  tx_supr_tdpkt; int /*<<< orphan*/  tx_chan_type; int /*<<< orphan*/  tx_atype; int /*<<< orphan*/  tx_filt_pswords; int /*<<< orphan*/  tx_filt_einfo; int /*<<< orphan*/  tx_pause_on_err; int /*<<< orphan*/  index; int /*<<< orphan*/  nav_id; int /*<<< orphan*/  valid_params; } ;
struct ti_sci_msg_rm_udmap_tx_ch_cfg {int /*<<< orphan*/  index; int /*<<< orphan*/  tx_burst_size; int /*<<< orphan*/  tx_sched_priority; int /*<<< orphan*/  fdepth; int /*<<< orphan*/  tx_orderid; int /*<<< orphan*/  tx_qos; int /*<<< orphan*/  tx_priority; int /*<<< orphan*/  txcq_qnum; int /*<<< orphan*/  tx_credit_count; int /*<<< orphan*/  tx_fetch_size; int /*<<< orphan*/  tx_supr_tdpkt; int /*<<< orphan*/  tx_chan_type; int /*<<< orphan*/  tx_atype; int /*<<< orphan*/  tx_filt_pswords; int /*<<< orphan*/  tx_filt_einfo; int /*<<< orphan*/  tx_pause_on_err; int /*<<< orphan*/  nav_id; int /*<<< orphan*/  valid_params; } ;
struct ti_sci_msg_hdr {int dummy; } ;
struct ti_sci_info {int /*<<< orphan*/  minfo; struct device* dev; } ;
struct ti_sci_handle {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct ti_sci_xfer*) ; 
 scalar_t__ IS_ERR_OR_NULL (struct ti_sci_handle const*) ; 
 int PTR_ERR (struct ti_sci_xfer*) ; 
 int /*<<< orphan*/  TISCI_MSG_RM_UDMAP_TX_CH_CFG ; 
 int /*<<< orphan*/  TI_SCI_FLAG_REQ_ACK_ON_PROCESSED ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct ti_sci_info* handle_to_ti_sci_info (struct ti_sci_handle const*) ; 
 int ti_sci_do_xfer (struct ti_sci_info*,struct ti_sci_xfer*) ; 
 struct ti_sci_xfer* ti_sci_get_one_xfer (struct ti_sci_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ ti_sci_is_response_ack (struct ti_sci_msg_hdr*) ; 
 int /*<<< orphan*/  ti_sci_put_one_xfer (int /*<<< orphan*/ *,struct ti_sci_xfer*) ; 

__attribute__((used)) static int ti_sci_cmd_rm_udmap_tx_ch_cfg(const struct ti_sci_handle *handle,
			const struct ti_sci_msg_rm_udmap_tx_ch_cfg *params)
{
	struct ti_sci_msg_rm_udmap_tx_ch_cfg_req *req;
	struct ti_sci_msg_hdr *resp;
	struct ti_sci_xfer *xfer;
	struct ti_sci_info *info;
	struct device *dev;
	int ret = 0;

	if (IS_ERR_OR_NULL(handle))
		return -EINVAL;

	info = handle_to_ti_sci_info(handle);
	dev = info->dev;

	xfer = ti_sci_get_one_xfer(info, TISCI_MSG_RM_UDMAP_TX_CH_CFG,
				   TI_SCI_FLAG_REQ_ACK_ON_PROCESSED,
				   sizeof(*req), sizeof(*resp));
	if (IS_ERR(xfer)) {
		ret = PTR_ERR(xfer);
		dev_err(dev, "Message TX_CH_CFG alloc failed(%d)\n", ret);
		return ret;
	}
	req = (struct ti_sci_msg_rm_udmap_tx_ch_cfg_req *)xfer->xfer_buf;
	req->valid_params = params->valid_params;
	req->nav_id = params->nav_id;
	req->index = params->index;
	req->tx_pause_on_err = params->tx_pause_on_err;
	req->tx_filt_einfo = params->tx_filt_einfo;
	req->tx_filt_pswords = params->tx_filt_pswords;
	req->tx_atype = params->tx_atype;
	req->tx_chan_type = params->tx_chan_type;
	req->tx_supr_tdpkt = params->tx_supr_tdpkt;
	req->tx_fetch_size = params->tx_fetch_size;
	req->tx_credit_count = params->tx_credit_count;
	req->txcq_qnum = params->txcq_qnum;
	req->tx_priority = params->tx_priority;
	req->tx_qos = params->tx_qos;
	req->tx_orderid = params->tx_orderid;
	req->fdepth = params->fdepth;
	req->tx_sched_priority = params->tx_sched_priority;
	req->tx_burst_size = params->tx_burst_size;

	ret = ti_sci_do_xfer(info, xfer);
	if (ret) {
		dev_err(dev, "Mbox send TX_CH_CFG fail %d\n", ret);
		goto fail;
	}

	resp = (struct ti_sci_msg_hdr *)xfer->xfer_buf;
	ret = ti_sci_is_response_ack(resp) ? 0 : -EINVAL;

fail:
	ti_sci_put_one_xfer(&info->minfo, xfer);
	dev_dbg(dev, "TX_CH_CFG: chn %u ret:%u\n", params->index, ret);
	return ret;
}