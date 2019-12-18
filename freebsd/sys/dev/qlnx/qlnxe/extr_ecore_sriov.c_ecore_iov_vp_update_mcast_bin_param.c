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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct vfpf_vport_update_mcast_bin_tlv {int /*<<< orphan*/  bins; } ;
struct ecore_sp_vport_update_params {int update_approx_mcast_flg; int /*<<< orphan*/  bins; } ;
struct ecore_iov_vf_mbx {int /*<<< orphan*/  req_virt; } ;
struct ecore_hwfn {int dummy; } ;

/* Variables and functions */
 int CHANNEL_TLV_VPORT_UPDATE_MCAST ; 
 int ECORE_IOV_VP_UPDATE_MCAST ; 
 int ETH_MULTICAST_MAC_BINS_IN_REGS ; 
 int /*<<< orphan*/  OSAL_MEMCPY (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ecore_iov_search_list_tlvs (struct ecore_hwfn*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ecore_iov_vp_update_mcast_bin_param(struct ecore_hwfn *p_hwfn,
				    struct ecore_sp_vport_update_params *p_data,
				    struct ecore_iov_vf_mbx *p_mbx,
				    u16 *tlvs_mask)
{
	struct vfpf_vport_update_mcast_bin_tlv *p_mcast_tlv;
	u16 tlv = CHANNEL_TLV_VPORT_UPDATE_MCAST;

	p_mcast_tlv = (struct vfpf_vport_update_mcast_bin_tlv *)
		      ecore_iov_search_list_tlvs(p_hwfn, p_mbx->req_virt,
						 tlv);
	if (!p_mcast_tlv)
		return;

	p_data->update_approx_mcast_flg = 1;
	OSAL_MEMCPY(p_data->bins, p_mcast_tlv->bins,
		    sizeof(u32) * ETH_MULTICAST_MAC_BINS_IN_REGS);
	*tlvs_mask |= 1 << ECORE_IOV_VP_UPDATE_MCAST;
}