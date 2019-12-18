#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct pfvf_def_resp_tlv {int dummy; } ;
struct TYPE_8__ {scalar_t__ reply_address; } ;
struct TYPE_9__ {TYPE_2__ first_tlv; } ;
struct TYPE_12__ {scalar_t__ response_offset; int /*<<< orphan*/  mbx_state; } ;
struct TYPE_10__ {int type; int /*<<< orphan*/  length; } ;
struct TYPE_11__ {scalar_t__ reply_address; TYPE_4__ tl; int /*<<< orphan*/  padding; } ;
struct ecore_iov_vf_mbx {int b_pending_msg; TYPE_6__ sw_mbx; TYPE_5__ first_tlv; TYPE_1__* req_virt; } ;
struct ecore_vf_info {int /*<<< orphan*/  abs_vf_id; TYPE_3__ acquire; int /*<<< orphan*/  b_malicious; int /*<<< orphan*/  relative_vf_id; struct ecore_iov_vf_mbx vf_mbx; } ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;
struct TYPE_7__ {TYPE_5__ first_tlv; } ;

/* Variables and functions */
#define  CHANNEL_TLV_ACQUIRE 143 
#define  CHANNEL_TLV_CLOSE 142 
#define  CHANNEL_TLV_COALESCE_READ 141 
#define  CHANNEL_TLV_COALESCE_UPDATE 140 
#define  CHANNEL_TLV_INT_CLEANUP 139 
#define  CHANNEL_TLV_RELEASE 138 
#define  CHANNEL_TLV_START_RXQ 137 
#define  CHANNEL_TLV_START_TXQ 136 
#define  CHANNEL_TLV_STOP_RXQS 135 
#define  CHANNEL_TLV_STOP_TXQS 134 
#define  CHANNEL_TLV_UCAST_FILTER 133 
#define  CHANNEL_TLV_UPDATE_RXQ 132 
#define  CHANNEL_TLV_UPDATE_TUNN_PARAM 131 
#define  CHANNEL_TLV_VPORT_START 130 
#define  CHANNEL_TLV_VPORT_TEARDOWN 129 
#define  CHANNEL_TLV_VPORT_UPDATE 128 
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  ECORE_MSG_IOV ; 
 int /*<<< orphan*/  OSAL_IOV_VF_MSG_TYPE (struct ecore_hwfn*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PFVF_STATUS_MALICIOUS ; 
 int /*<<< orphan*/  PFVF_STATUS_NOT_SUPPORTED ; 
 int /*<<< orphan*/  VF_PF_RESPONSE_READY ; 
 struct ecore_vf_info* ecore_iov_get_vf_info (struct ecore_hwfn*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ecore_iov_lock_vf_pf_channel (struct ecore_hwfn*,struct ecore_vf_info*,int) ; 
 int /*<<< orphan*/  ecore_iov_prepare_resp (struct ecore_hwfn*,struct ecore_ptt*,struct ecore_vf_info*,int const,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ecore_iov_tlv_supported (int) ; 
 int /*<<< orphan*/  ecore_iov_unlock_vf_pf_channel (struct ecore_hwfn*,struct ecore_vf_info*,int const) ; 
 int /*<<< orphan*/  ecore_iov_vf_mbx_acquire (struct ecore_hwfn*,struct ecore_ptt*,struct ecore_vf_info*) ; 
 int /*<<< orphan*/  ecore_iov_vf_mbx_close (struct ecore_hwfn*,struct ecore_ptt*,struct ecore_vf_info*) ; 
 int /*<<< orphan*/  ecore_iov_vf_mbx_int_cleanup (struct ecore_hwfn*,struct ecore_ptt*,struct ecore_vf_info*) ; 
 int /*<<< orphan*/  ecore_iov_vf_mbx_release (struct ecore_hwfn*,struct ecore_ptt*,struct ecore_vf_info*) ; 
 int /*<<< orphan*/  ecore_iov_vf_mbx_start_rxq (struct ecore_hwfn*,struct ecore_ptt*,struct ecore_vf_info*) ; 
 int /*<<< orphan*/  ecore_iov_vf_mbx_start_txq (struct ecore_hwfn*,struct ecore_ptt*,struct ecore_vf_info*) ; 
 int /*<<< orphan*/  ecore_iov_vf_mbx_start_vport (struct ecore_hwfn*,struct ecore_ptt*,struct ecore_vf_info*) ; 
 int /*<<< orphan*/  ecore_iov_vf_mbx_stop_rxqs (struct ecore_hwfn*,struct ecore_ptt*,struct ecore_vf_info*) ; 
 int /*<<< orphan*/  ecore_iov_vf_mbx_stop_txqs (struct ecore_hwfn*,struct ecore_ptt*,struct ecore_vf_info*) ; 
 int /*<<< orphan*/  ecore_iov_vf_mbx_stop_vport (struct ecore_hwfn*,struct ecore_ptt*,struct ecore_vf_info*) ; 
 int /*<<< orphan*/  ecore_iov_vf_mbx_ucast_filter (struct ecore_hwfn*,struct ecore_ptt*,struct ecore_vf_info*) ; 
 int /*<<< orphan*/  ecore_iov_vf_mbx_update_rxqs (struct ecore_hwfn*,struct ecore_ptt*,struct ecore_vf_info*) ; 
 int /*<<< orphan*/  ecore_iov_vf_mbx_update_tunn_param (struct ecore_hwfn*,struct ecore_ptt*,struct ecore_vf_info*) ; 
 int /*<<< orphan*/  ecore_iov_vf_mbx_vport_update (struct ecore_hwfn*,struct ecore_ptt*,struct ecore_vf_info*) ; 
 int /*<<< orphan*/  ecore_iov_vf_pf_get_coalesce (struct ecore_hwfn*,struct ecore_ptt*,struct ecore_vf_info*) ; 
 int /*<<< orphan*/  ecore_iov_vf_pf_set_coalesce (struct ecore_hwfn*,struct ecore_ptt*,struct ecore_vf_info*) ; 

void ecore_iov_process_mbx_req(struct ecore_hwfn    *p_hwfn,
			       struct ecore_ptt     *p_ptt,
			       int vfid)
{
	struct ecore_iov_vf_mbx *mbx;
	struct ecore_vf_info *p_vf;

	p_vf = ecore_iov_get_vf_info(p_hwfn, (u16)vfid, true);
	if (!p_vf)
		return;

	mbx = &p_vf->vf_mbx;

	/* ecore_iov_process_mbx_request */
#ifndef CONFIG_ECORE_SW_CHANNEL
	if (!mbx->b_pending_msg) {
		DP_NOTICE(p_hwfn, true,
			  "VF[%02x]: Trying to process mailbox message when none is pending\n",
			  p_vf->abs_vf_id);
		return;
	}
	mbx->b_pending_msg = false;
#endif

	mbx->first_tlv = mbx->req_virt->first_tlv;

	DP_VERBOSE(p_hwfn, ECORE_MSG_IOV,
		   "VF[%02x]: Processing mailbox message [type %04x]\n",
		   p_vf->abs_vf_id, mbx->first_tlv.tl.type);

	OSAL_IOV_VF_MSG_TYPE(p_hwfn,
                             p_vf->relative_vf_id,
                             mbx->first_tlv.tl.type);

	/* Lock the per vf op mutex and note the locker's identity.
	 * The unlock will take place in mbx response.
	 */
	ecore_iov_lock_vf_pf_channel(p_hwfn, p_vf,
				     mbx->first_tlv.tl.type);

	/* check if tlv type is known */
	if (ecore_iov_tlv_supported(mbx->first_tlv.tl.type) &&
	    !p_vf->b_malicious) {
		/* switch on the opcode */
		switch (mbx->first_tlv.tl.type) {
		case CHANNEL_TLV_ACQUIRE:
			ecore_iov_vf_mbx_acquire(p_hwfn, p_ptt, p_vf);
			break;
		case CHANNEL_TLV_VPORT_START:
			ecore_iov_vf_mbx_start_vport(p_hwfn, p_ptt, p_vf);
			break;
		case CHANNEL_TLV_VPORT_TEARDOWN:
			ecore_iov_vf_mbx_stop_vport(p_hwfn, p_ptt, p_vf);
			break;
		case CHANNEL_TLV_START_RXQ:
			ecore_iov_vf_mbx_start_rxq(p_hwfn, p_ptt, p_vf);
			break;
		case CHANNEL_TLV_START_TXQ:
			ecore_iov_vf_mbx_start_txq(p_hwfn, p_ptt, p_vf);
			break;
		case CHANNEL_TLV_STOP_RXQS:
			ecore_iov_vf_mbx_stop_rxqs(p_hwfn, p_ptt, p_vf);
			break;
		case CHANNEL_TLV_STOP_TXQS:
			ecore_iov_vf_mbx_stop_txqs(p_hwfn, p_ptt, p_vf);
			break;
		case CHANNEL_TLV_UPDATE_RXQ:
			ecore_iov_vf_mbx_update_rxqs(p_hwfn, p_ptt, p_vf);
			break;
		case CHANNEL_TLV_VPORT_UPDATE:
			ecore_iov_vf_mbx_vport_update(p_hwfn, p_ptt, p_vf);
			break;
		case CHANNEL_TLV_UCAST_FILTER:
			ecore_iov_vf_mbx_ucast_filter(p_hwfn, p_ptt, p_vf);
			break;
		case CHANNEL_TLV_CLOSE:
			ecore_iov_vf_mbx_close(p_hwfn, p_ptt, p_vf);
			break;
		case CHANNEL_TLV_INT_CLEANUP:
			ecore_iov_vf_mbx_int_cleanup(p_hwfn, p_ptt, p_vf);
			break;
		case CHANNEL_TLV_RELEASE:
			ecore_iov_vf_mbx_release(p_hwfn, p_ptt, p_vf);
			break;
		case CHANNEL_TLV_UPDATE_TUNN_PARAM:
			ecore_iov_vf_mbx_update_tunn_param(p_hwfn, p_ptt, p_vf);
			break;
		case CHANNEL_TLV_COALESCE_UPDATE:
			ecore_iov_vf_pf_set_coalesce(p_hwfn, p_ptt, p_vf);
			break;
		case CHANNEL_TLV_COALESCE_READ:
			ecore_iov_vf_pf_get_coalesce(p_hwfn, p_ptt, p_vf);
			break;
		}
	} else if (ecore_iov_tlv_supported(mbx->first_tlv.tl.type)) {
		/* If we've received a message from a VF we consider malicious
		 * we ignore the messasge unless it's one for RELEASE, in which
		 * case we'll let it have the benefit of doubt, allowing the
		 * next loaded driver to start again.
		 */
		if (mbx->first_tlv.tl.type == CHANNEL_TLV_RELEASE) {
			/* TODO - initiate FLR, remove malicious indication */
			DP_VERBOSE(p_hwfn, ECORE_MSG_IOV,
				   "VF [%02x] - considered malicious, but wanted to RELEASE. TODO\n",
				   p_vf->abs_vf_id);
		} else {
			DP_VERBOSE(p_hwfn, ECORE_MSG_IOV,
				   "VF [%02x] - considered malicious; Ignoring TLV [%04x]\n",
				   p_vf->abs_vf_id, mbx->first_tlv.tl.type);
		}

		ecore_iov_prepare_resp(p_hwfn, p_ptt, p_vf,
				       mbx->first_tlv.tl.type,
				       sizeof(struct pfvf_def_resp_tlv),
				       PFVF_STATUS_MALICIOUS);
	} else {
		/* unknown TLV - this may belong to a VF driver from the future
		 * - a version written after this PF driver was written, which
		 * supports features unknown as of yet. Too bad since we don't
		 * support them. Or this may be because someone wrote a crappy
		 * VF driver and is sending garbage over the channel.
		 */
		DP_NOTICE(p_hwfn, false,
			  "VF[%02x]: unknown TLV. type %04x length %04x padding %08x reply address %llu\n",
			  p_vf->abs_vf_id,
			  mbx->first_tlv.tl.type,
			  mbx->first_tlv.tl.length,
			  mbx->first_tlv.padding,
			  (unsigned long long)mbx->first_tlv.reply_address);

		/* Try replying in case reply address matches the acquisition's
		 * posted address.
		 */
		if (p_vf->acquire.first_tlv.reply_address &&
		    (mbx->first_tlv.reply_address ==
		     p_vf->acquire.first_tlv.reply_address))
			ecore_iov_prepare_resp(p_hwfn, p_ptt, p_vf,
					       mbx->first_tlv.tl.type,
					       sizeof(struct pfvf_def_resp_tlv),
					       PFVF_STATUS_NOT_SUPPORTED);
		else
			DP_VERBOSE(p_hwfn, ECORE_MSG_IOV,
				   "VF[%02x]: Can't respond to TLV - no valid reply address\n",
				   p_vf->abs_vf_id);
	}

	ecore_iov_unlock_vf_pf_channel(p_hwfn, p_vf,
				       mbx->first_tlv.tl.type);

#ifdef CONFIG_ECORE_SW_CHANNEL
	mbx->sw_mbx.mbx_state = VF_PF_RESPONSE_READY;
	mbx->sw_mbx.response_offset = 0;
#endif
}