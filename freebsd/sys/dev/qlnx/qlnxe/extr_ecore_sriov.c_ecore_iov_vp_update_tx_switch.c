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
struct vfpf_vport_update_tx_switch_tlv {int /*<<< orphan*/  tx_switching; } ;
struct ecore_sp_vport_update_params {int update_tx_switching_flg; int /*<<< orphan*/  tx_switching_flg; } ;
struct ecore_iov_vf_mbx {int /*<<< orphan*/  req_virt; } ;
struct ecore_hwfn {int /*<<< orphan*/  p_dev; } ;

/* Variables and functions */
 int CHANNEL_TLV_VPORT_UPDATE_TX_SWITCH ; 
 scalar_t__ CHIP_REV_IS_FPGA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*) ; 
 int ECORE_IOV_VP_UPDATE_TX_SWITCH ; 
 scalar_t__ ecore_iov_search_list_tlvs (struct ecore_hwfn*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ecore_iov_vp_update_tx_switch(struct ecore_hwfn *p_hwfn,
			      struct ecore_sp_vport_update_params *p_data,
			      struct ecore_iov_vf_mbx *p_mbx, u16 *tlvs_mask)
{
	struct vfpf_vport_update_tx_switch_tlv *p_tx_switch_tlv;
	u16 tlv = CHANNEL_TLV_VPORT_UPDATE_TX_SWITCH;

	p_tx_switch_tlv = (struct vfpf_vport_update_tx_switch_tlv *)
			  ecore_iov_search_list_tlvs(p_hwfn, p_mbx->req_virt,
						     tlv);
	if (!p_tx_switch_tlv)
		return;

#ifndef ASIC_ONLY
	if (CHIP_REV_IS_FPGA(p_hwfn->p_dev)) {
		DP_NOTICE(p_hwfn, false, "FPGA: Ignore tx-switching configuration originating from VFs\n");
		return;
	}
#endif

	p_data->update_tx_switching_flg = 1;
	p_data->tx_switching_flg = p_tx_switch_tlv->tx_switching;
	*tlvs_mask |= 1 << ECORE_IOV_VP_UPDATE_TX_SWITCH;
}