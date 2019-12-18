#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct eth_vport_tpa_param {int tpa_max_size; int tpa_min_size_to_cont; int tpa_min_size_to_start; int tpa_ipv4_en_flg; int tpa_ipv6_en_flg; int tpa_ipv4_tunn_en_flg; int tpa_ipv6_tunn_en_flg; int tpa_pkt_split_flg; int tpa_gro_consistent_flg; int /*<<< orphan*/  tpa_max_aggs_num; int /*<<< orphan*/  max_buff_num; int /*<<< orphan*/  comp_mode; int /*<<< orphan*/  opaque_fid; int /*<<< orphan*/  cid; } ;
struct TYPE_6__ {void* values; } ;
struct TYPE_5__ {void* state; } ;
struct vport_start_ramrod_data {int ctl_frame_mac_check_en; int ctl_frame_ethtype_check_en; int /*<<< orphan*/  sw_fid; scalar_t__ tx_switching_en; struct eth_vport_tpa_param tpa_param; TYPE_3__ tx_err_behav; TYPE_2__ rx_mode; int /*<<< orphan*/  zero_placement_offset; int /*<<< orphan*/  untagged; int /*<<< orphan*/  drop_ttl0_en; int /*<<< orphan*/  inner_vlan_removal_en; int /*<<< orphan*/  handle_ptp_pkts; void* mtu; int /*<<< orphan*/  vport_id; } ;
struct TYPE_4__ {struct vport_start_ramrod_data vport_start; } ;
struct ecore_spq_entry {TYPE_1__ ramrod; } ;
struct ecore_sp_vport_start_params {int mtu; int tpa_mode; int /*<<< orphan*/  concrete_fid; int /*<<< orphan*/  check_ethtype; int /*<<< orphan*/  check_mac; scalar_t__ tx_switching; int /*<<< orphan*/  max_buffers_per_cqe; scalar_t__ b_err_ctrl_frame; scalar_t__ b_err_big_pkt; scalar_t__ b_err_vlan_insert_with_inband; scalar_t__ b_err_illegal_inband_mode; scalar_t__ b_err_anti_spoof; scalar_t__ b_err_small_pkt; scalar_t__ b_err_illegal_vlan_mode; int /*<<< orphan*/  zero_placement_offset; int /*<<< orphan*/  only_untagged; int /*<<< orphan*/  drop_ttl0; int /*<<< orphan*/  remove_inner_vlan; int /*<<< orphan*/  handle_ptp_pkts; int /*<<< orphan*/  opaque_fid; int /*<<< orphan*/  vport_id; } ;
struct ecore_sp_init_data {int tpa_max_size; int tpa_min_size_to_cont; int tpa_min_size_to_start; int tpa_ipv4_en_flg; int tpa_ipv6_en_flg; int tpa_ipv4_tunn_en_flg; int tpa_ipv6_tunn_en_flg; int tpa_pkt_split_flg; int tpa_gro_consistent_flg; int /*<<< orphan*/  tpa_max_aggs_num; int /*<<< orphan*/  max_buff_num; int /*<<< orphan*/  comp_mode; int /*<<< orphan*/  opaque_fid; int /*<<< orphan*/  cid; } ;
struct ecore_hwfn {int /*<<< orphan*/  p_dev; } ;
typedef  int /*<<< orphan*/  init_data ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 scalar_t__ CHIP_REV_IS_SLOW (int /*<<< orphan*/ ) ; 
 int ECORE_NOTIMPL ; 
 int /*<<< orphan*/  ECORE_SPQ_MODE_EBLOCK ; 
 int ECORE_SUCCESS ; 
#define  ECORE_TPA_MODE_GRO 128 
 int /*<<< orphan*/  ETH_RAMROD_VPORT_START ; 
 int /*<<< orphan*/  ETH_TPA_MAX_AGGS_NUM ; 
 int ETH_TX_ERR_ASSERT_MALICIOUS ; 
 int /*<<< orphan*/  ETH_TX_ERR_VALS_ANTI_SPOOFING_ERR ; 
 int /*<<< orphan*/  ETH_TX_ERR_VALS_ILLEGAL_CONTROL_FRAME ; 
 int /*<<< orphan*/  ETH_TX_ERR_VALS_ILLEGAL_INBAND_TAGS ; 
 int /*<<< orphan*/  ETH_TX_ERR_VALS_ILLEGAL_VLAN_MODE ; 
 int /*<<< orphan*/  ETH_TX_ERR_VALS_MTU_VIOLATION ; 
 int /*<<< orphan*/  ETH_TX_ERR_VALS_PACKET_TOO_SMALL ; 
 int /*<<< orphan*/  ETH_TX_ERR_VALS_VLAN_INSERTION_W_INBAND_TAG ; 
 int /*<<< orphan*/  ETH_VPORT_RX_MODE_MCAST_DROP_ALL ; 
 int /*<<< orphan*/  ETH_VPORT_RX_MODE_UCAST_DROP_ALL ; 
 void* OSAL_CPU_TO_LE16 (int) ; 
 int /*<<< orphan*/  OSAL_MEMSET (struct eth_vport_tpa_param*,int /*<<< orphan*/ ,int) ; 
 void* OSAL_NULL ; 
 int /*<<< orphan*/  PROTOCOLID_ETH ; 
 int /*<<< orphan*/  SET_FIELD (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ecore_concrete_to_sw_fid (int /*<<< orphan*/ ) ; 
 int ecore_fw_vport (struct ecore_hwfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ecore_sp_init_request (struct ecore_hwfn*,struct ecore_spq_entry**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct eth_vport_tpa_param*) ; 
 int /*<<< orphan*/  ecore_spq_get_cid (struct ecore_hwfn*) ; 
 int ecore_spq_post (struct ecore_hwfn*,struct ecore_spq_entry*,void*) ; 

enum _ecore_status_t ecore_sp_eth_vport_start(struct ecore_hwfn *p_hwfn,
					      struct ecore_sp_vport_start_params *p_params)
{
	struct vport_start_ramrod_data *p_ramrod = OSAL_NULL;
	struct ecore_spq_entry *p_ent = OSAL_NULL;
	struct ecore_sp_init_data init_data;
	struct eth_vport_tpa_param *p_tpa;
	u16 rx_mode = 0, tx_err = 0;
	u8 abs_vport_id = 0;
	enum _ecore_status_t rc = ECORE_NOTIMPL;

	rc = ecore_fw_vport(p_hwfn, p_params->vport_id, &abs_vport_id);
	if (rc != ECORE_SUCCESS)
		return rc;

	/* Get SPQ entry */
	OSAL_MEMSET(&init_data, 0, sizeof(init_data));
	init_data.cid = ecore_spq_get_cid(p_hwfn);
	init_data.opaque_fid = p_params->opaque_fid;
	init_data.comp_mode = ECORE_SPQ_MODE_EBLOCK;

	rc = ecore_sp_init_request(p_hwfn, &p_ent,
				   ETH_RAMROD_VPORT_START,
				   PROTOCOLID_ETH, &init_data);
	if (rc != ECORE_SUCCESS)
		return rc;

	p_ramrod = &p_ent->ramrod.vport_start;
	p_ramrod->vport_id = abs_vport_id;

	p_ramrod->mtu = OSAL_CPU_TO_LE16(p_params->mtu);
	p_ramrod->handle_ptp_pkts = p_params->handle_ptp_pkts;
	p_ramrod->inner_vlan_removal_en	= p_params->remove_inner_vlan;
	p_ramrod->drop_ttl0_en	= p_params->drop_ttl0;
	p_ramrod->untagged = p_params->only_untagged;
	p_ramrod->zero_placement_offset = p_params->zero_placement_offset;

	SET_FIELD(rx_mode, ETH_VPORT_RX_MODE_UCAST_DROP_ALL, 1);
	SET_FIELD(rx_mode, ETH_VPORT_RX_MODE_MCAST_DROP_ALL, 1);

	p_ramrod->rx_mode.state	= OSAL_CPU_TO_LE16(rx_mode);

	/* Handle requests for strict behavior on transmission errors */
	SET_FIELD(tx_err, ETH_TX_ERR_VALS_ILLEGAL_VLAN_MODE,
		  p_params->b_err_illegal_vlan_mode ?
		  ETH_TX_ERR_ASSERT_MALICIOUS : 0);
	SET_FIELD(tx_err, ETH_TX_ERR_VALS_PACKET_TOO_SMALL,
		  p_params->b_err_small_pkt ?
		  ETH_TX_ERR_ASSERT_MALICIOUS : 0);
	SET_FIELD(tx_err, ETH_TX_ERR_VALS_ANTI_SPOOFING_ERR,
		  p_params->b_err_anti_spoof ?
		  ETH_TX_ERR_ASSERT_MALICIOUS : 0);
	SET_FIELD(tx_err, ETH_TX_ERR_VALS_ILLEGAL_INBAND_TAGS,
		  p_params->b_err_illegal_inband_mode ?
		  ETH_TX_ERR_ASSERT_MALICIOUS : 0);
	SET_FIELD(tx_err, ETH_TX_ERR_VALS_VLAN_INSERTION_W_INBAND_TAG,
		  p_params->b_err_vlan_insert_with_inband ?
		  ETH_TX_ERR_ASSERT_MALICIOUS : 0);
	SET_FIELD(tx_err, ETH_TX_ERR_VALS_MTU_VIOLATION,
		  p_params->b_err_big_pkt ?
		  ETH_TX_ERR_ASSERT_MALICIOUS : 0);
	SET_FIELD(tx_err, ETH_TX_ERR_VALS_ILLEGAL_CONTROL_FRAME,
		  p_params->b_err_ctrl_frame ?
		  ETH_TX_ERR_ASSERT_MALICIOUS : 0);
	p_ramrod->tx_err_behav.values = OSAL_CPU_TO_LE16(tx_err);

	/* TPA related fields */
	p_tpa = &p_ramrod->tpa_param;
	OSAL_MEMSET(p_tpa, 0, sizeof(struct eth_vport_tpa_param));
	p_tpa->max_buff_num = p_params->max_buffers_per_cqe;

	switch (p_params->tpa_mode) {
	case ECORE_TPA_MODE_GRO:
		p_tpa->tpa_max_aggs_num = ETH_TPA_MAX_AGGS_NUM;
		p_tpa->tpa_max_size = (u16)-1;
		p_tpa->tpa_min_size_to_cont = p_params->mtu/2;
		p_tpa->tpa_min_size_to_start = p_params->mtu/2;
		p_tpa->tpa_ipv4_en_flg = 1;
		p_tpa->tpa_ipv6_en_flg = 1;
		p_tpa->tpa_ipv4_tunn_en_flg = 1;
		p_tpa->tpa_ipv6_tunn_en_flg = 1;
		p_tpa->tpa_pkt_split_flg = 1;
		p_tpa->tpa_gro_consistent_flg = 1;
		break;
	default:
		break;
	}

	p_ramrod->tx_switching_en = p_params->tx_switching;
#ifndef ASIC_ONLY
	if (CHIP_REV_IS_SLOW(p_hwfn->p_dev))
		p_ramrod->tx_switching_en = 0;
#endif

	p_ramrod->ctl_frame_mac_check_en = !!p_params->check_mac;
	p_ramrod->ctl_frame_ethtype_check_en = !!p_params->check_ethtype;

	/* Software Function ID in hwfn (PFs are 0 - 15, VFs are 16 - 135) */
	p_ramrod->sw_fid = ecore_concrete_to_sw_fid(p_params->concrete_fid);

	return ecore_spq_post(p_hwfn, p_ent, OSAL_NULL);
}