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
typedef  size_t u16 ;
struct TYPE_2__ {scalar_t__ status; } ;
struct pfvf_def_resp_tlv {TYPE_1__ hdr; } ;
struct ecore_vf_iov {int /*<<< orphan*/  pf2vf_reply; } ;
struct ecore_sp_vport_update_params {int dummy; } ;
struct ecore_hwfn {struct ecore_vf_iov* vf_iov_info; } ;

/* Variables and functions */
 size_t CHANNEL_TLV_VPORT_UPDATE_ACTIVATE ; 
 size_t CHANNEL_TLV_VPORT_UPDATE_MAX ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ECORE_MSG_IOV ; 
 int /*<<< orphan*/ * ecore_channel_tlvs_string ; 
 scalar_t__ ecore_iov_search_list_tlvs (struct ecore_hwfn*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ecore_vf_handle_vp_update_is_needed (struct ecore_hwfn*,struct ecore_sp_vport_update_params*,size_t) ; 

__attribute__((used)) static void
ecore_vf_handle_vp_update_tlvs_resp(struct ecore_hwfn *p_hwfn,
				    struct ecore_sp_vport_update_params *p_data)
{
	struct ecore_vf_iov *p_iov = p_hwfn->vf_iov_info;
	struct pfvf_def_resp_tlv *p_resp;
	u16 tlv;

	for (tlv = CHANNEL_TLV_VPORT_UPDATE_ACTIVATE;
	     tlv < CHANNEL_TLV_VPORT_UPDATE_MAX;
	     tlv++) {
		if (!ecore_vf_handle_vp_update_is_needed(p_hwfn, p_data, tlv))
			continue;

		p_resp = (struct pfvf_def_resp_tlv *)
			 ecore_iov_search_list_tlvs(p_hwfn, p_iov->pf2vf_reply,
						    tlv);
		if (p_resp && p_resp->hdr.status)
			DP_VERBOSE(p_hwfn, ECORE_MSG_IOV,
				   "TLV[%d] type %s Configuration %s\n",
				   tlv, ecore_channel_tlvs_string[tlv],
				   (p_resp && p_resp->hdr.status) ? "succeeded"
								  : "failed");
	}
}