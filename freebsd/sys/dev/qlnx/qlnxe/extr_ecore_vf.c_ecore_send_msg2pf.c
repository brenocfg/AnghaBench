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
struct TYPE_11__ {int /*<<< orphan*/  type; } ;
struct TYPE_12__ {TYPE_5__ tl; } ;
union vfpf_tlvs {TYPE_6__ first_tlv; } ;
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct TYPE_8__ {int /*<<< orphan*/  hi; int /*<<< orphan*/  lo; } ;
struct TYPE_9__ {TYPE_2__ vf_pf_msg_addr; } ;
struct ustorm_vf_zone {int /*<<< orphan*/  trigger; TYPE_3__ non_trigger; } ;
struct ustorm_trigger_vf_zone {int vf_pf_msg_valid; } ;
struct TYPE_7__ {int /*<<< orphan*/  concrete_fid; } ;
struct ecore_hwfn {int /*<<< orphan*/  p_dev; TYPE_4__* vf_iov_info; TYPE_1__ hw_info; } ;
struct channel_list_end_tlv {int dummy; } ;
typedef  int /*<<< orphan*/  osal_uintptr_t ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_10__ {int /*<<< orphan*/  vf2pf_request_phys; int /*<<< orphan*/  pf2vf_reply; int /*<<< orphan*/  b_hw_channel; union vfpf_tlvs* vf2pf_request; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,scalar_t__,int,...) ; 
 int /*<<< orphan*/  ECORE_MSG_IOV ; 
 int ECORE_SUCCESS ; 
 int ECORE_TIMEOUT ; 
 int /*<<< orphan*/  GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSAL_MEMSET (struct ustorm_trigger_vf_zone*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OSAL_MSLEEP (int) ; 
 int OSAL_VF_SEND_MSG2PF (int /*<<< orphan*/ ,scalar_t__*,union vfpf_tlvs*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  OSAL_WMB (int /*<<< orphan*/ ) ; 
 scalar_t__ PFVF_STATUS_NO_RESOURCE ; 
 scalar_t__ PFVF_STATUS_SUCCESS ; 
 int /*<<< orphan*/  PXP_CONCRETE_FID_PFID ; 
 scalar_t__ PXP_VF_BAR0_START_USDM_ZONE_B ; 
 int /*<<< orphan*/  REG_WR (struct ecore_hwfn*,int /*<<< orphan*/ ,int) ; 
 int U64_HI (int /*<<< orphan*/ ) ; 
 int U64_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_dp_tlv_list (struct ecore_hwfn*,union vfpf_tlvs*) ; 

__attribute__((used)) static enum _ecore_status_t
ecore_send_msg2pf(struct ecore_hwfn *p_hwfn,
		  u8 *done, u32 resp_size)
{
	union vfpf_tlvs *p_req = p_hwfn->vf_iov_info->vf2pf_request;
	struct ustorm_trigger_vf_zone trigger;
	struct ustorm_vf_zone *zone_data;
	enum _ecore_status_t rc = ECORE_SUCCESS;
	int time = 100;

	zone_data = (struct ustorm_vf_zone *)PXP_VF_BAR0_START_USDM_ZONE_B;

	/* output tlvs list */
	ecore_dp_tlv_list(p_hwfn, p_req);

	/* need to add the END TLV to the message size */
	resp_size += sizeof(struct channel_list_end_tlv);

#ifdef CONFIG_ECORE_SW_CHANNEL
	if (!p_hwfn->vf_iov_info->b_hw_channel) {
		rc =  OSAL_VF_SEND_MSG2PF(p_hwfn->p_dev,
					   done,
					   p_req,
					   p_hwfn->vf_iov_info->pf2vf_reply,
					   sizeof(union vfpf_tlvs),
					   resp_size);
		/* TODO - no prints about message ? */
		return rc;
	}
#endif

	/* Send TLVs over HW channel */
	OSAL_MEMSET(&trigger, 0, sizeof(struct ustorm_trigger_vf_zone));
	trigger.vf_pf_msg_valid = 1;

	DP_VERBOSE(p_hwfn, ECORE_MSG_IOV,
		   "VF -> PF [%02x] message: [%08x, %08x] --> %p, %08x --> %p\n",
		   GET_FIELD(p_hwfn->hw_info.concrete_fid,
			     PXP_CONCRETE_FID_PFID),
		   U64_HI(p_hwfn->vf_iov_info->vf2pf_request_phys),
		   U64_LO(p_hwfn->vf_iov_info->vf2pf_request_phys),
		   &zone_data->non_trigger.vf_pf_msg_addr,
		   *((u32 *)&trigger),
		   &zone_data->trigger);

	REG_WR(p_hwfn,
	       (osal_uintptr_t)&zone_data->non_trigger.vf_pf_msg_addr.lo,
	       U64_LO(p_hwfn->vf_iov_info->vf2pf_request_phys));

	REG_WR(p_hwfn,
	       (osal_uintptr_t)&zone_data->non_trigger.vf_pf_msg_addr.hi,
	       U64_HI(p_hwfn->vf_iov_info->vf2pf_request_phys));

	/* The message data must be written first, to prevent trigger before
	 * data is written.
	 */
	OSAL_WMB(p_hwfn->p_dev);

	REG_WR(p_hwfn, (osal_uintptr_t)&zone_data->trigger, *((u32 *)&trigger));

	/* When PF would be done with the response, it would write back to the
	 * `done' address. Poll until then.
	 */
	while ((!*done) && time) {
		OSAL_MSLEEP(25);
		time--;
	}

	if (!*done) {
		DP_NOTICE(p_hwfn, true,
			  "VF <-- PF Timeout [Type %d]\n",
			  p_req->first_tlv.tl.type);
		rc =  ECORE_TIMEOUT;
	} else {
		if ((*done != PFVF_STATUS_SUCCESS) &&
		    (*done != PFVF_STATUS_NO_RESOURCE))
			DP_NOTICE(p_hwfn, false,
				  "PF response: %d [Type %d]\n",
				  *done, p_req->first_tlv.tl.type);
		else
			DP_VERBOSE(p_hwfn, ECORE_MSG_IOV,
				   "PF response: %d [Type %d]\n",
				   *done, p_req->first_tlv.tl.type);
	}

	return rc;
}