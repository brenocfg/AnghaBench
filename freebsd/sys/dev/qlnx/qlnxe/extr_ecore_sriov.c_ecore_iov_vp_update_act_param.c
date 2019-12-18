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
typedef  int u16 ;
struct vfpf_vport_update_activate_tlv {int /*<<< orphan*/  active_tx; int /*<<< orphan*/  update_tx; int /*<<< orphan*/  active_rx; int /*<<< orphan*/  update_rx; } ;
struct ecore_sp_vport_update_params {int /*<<< orphan*/  vport_active_tx_flg; int /*<<< orphan*/  update_vport_active_tx_flg; int /*<<< orphan*/  vport_active_rx_flg; int /*<<< orphan*/  update_vport_active_rx_flg; } ;
struct ecore_iov_vf_mbx {int /*<<< orphan*/  req_virt; } ;
struct ecore_hwfn {int dummy; } ;

/* Variables and functions */
 int CHANNEL_TLV_VPORT_UPDATE_ACTIVATE ; 
 int ECORE_IOV_VP_UPDATE_ACTIVATE ; 
 scalar_t__ ecore_iov_search_list_tlvs (struct ecore_hwfn*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ecore_iov_vp_update_act_param(struct ecore_hwfn *p_hwfn,
			      struct ecore_sp_vport_update_params *p_data,
			      struct ecore_iov_vf_mbx *p_mbx, u16 *tlvs_mask)
{
	struct vfpf_vport_update_activate_tlv *p_act_tlv;
	u16 tlv = CHANNEL_TLV_VPORT_UPDATE_ACTIVATE;

	p_act_tlv = (struct vfpf_vport_update_activate_tlv *)
		    ecore_iov_search_list_tlvs(p_hwfn, p_mbx->req_virt,
					       tlv);
	if (!p_act_tlv)
		return;

	p_data->update_vport_active_rx_flg = p_act_tlv->update_rx;
	p_data->vport_active_rx_flg = p_act_tlv->active_rx;
	p_data->update_vport_active_tx_flg = p_act_tlv->update_tx;
	p_data->vport_active_tx_flg = p_act_tlv->active_tx;
	*tlvs_mask |= 1 << ECORE_IOV_VP_UPDATE_ACTIVATE;
}