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
typedef  void* u8 ;
struct vport_update_ramrod_data_cmn {int update_tx_switching_en_flg; void* update_anti_spoofing_en_flg; int /*<<< orphan*/  anti_spoofing_en; scalar_t__ tx_switching_en; int /*<<< orphan*/  silent_vlan_removal_en; int /*<<< orphan*/  update_default_vlan_flg; int /*<<< orphan*/  default_vlan; void* update_default_vlan_en_flg; int /*<<< orphan*/  default_vlan_en; void* update_inner_vlan_removal_en_flg; int /*<<< orphan*/  inner_vlan_removal_en; void* update_accept_any_vlan_flg; int /*<<< orphan*/  accept_any_vlan; int /*<<< orphan*/  update_tx_active_flg; int /*<<< orphan*/  tx_active_flg; int /*<<< orphan*/  update_rx_active_flg; int /*<<< orphan*/  rx_active_flg; void* vport_id; } ;
struct vport_update_ramrod_data {struct vport_update_ramrod_data_cmn common; } ;
struct TYPE_2__ {struct vport_update_ramrod_data vport_update; } ;
struct ecore_spq_entry {TYPE_1__ ramrod; } ;
struct ecore_spq_comp_cb {int dummy; } ;
struct ecore_sp_vport_update_params {int update_tx_switching_flg; int /*<<< orphan*/  sge_tpa_params; int /*<<< orphan*/  accept_flags; void* update_anti_spoofing_en_flg; int /*<<< orphan*/  anti_spoofing_en; scalar_t__ tx_switching_flg; int /*<<< orphan*/  silent_vlan_removal_flg; int /*<<< orphan*/  update_default_vlan_flg; int /*<<< orphan*/  default_vlan; void* update_default_vlan_enable_flg; int /*<<< orphan*/  default_vlan_enable_flg; void* update_inner_vlan_removal_flg; int /*<<< orphan*/  inner_vlan_removal_flg; void* update_accept_any_vlan_flg; int /*<<< orphan*/  accept_any_vlan; int /*<<< orphan*/  update_vport_active_tx_flg; int /*<<< orphan*/  vport_active_tx_flg; int /*<<< orphan*/  update_vport_active_rx_flg; int /*<<< orphan*/  vport_active_rx_flg; int /*<<< orphan*/  opaque_fid; int /*<<< orphan*/  vport_id; struct ecore_rss_params* rss_params; } ;
struct ecore_sp_init_data {int comp_mode; struct ecore_spq_comp_cb* p_comp_data; int /*<<< orphan*/  opaque_fid; int /*<<< orphan*/  cid; } ;
struct ecore_rss_params {int dummy; } ;
struct ecore_hwfn {int /*<<< orphan*/  p_dev; } ;
typedef  int /*<<< orphan*/  init_data ;
typedef  enum spq_mode { ____Placeholder_spq_mode } spq_mode ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 scalar_t__ CHIP_REV_IS_FPGA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*) ; 
 int ECORE_NOTIMPL ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  ETH_RAMROD_VPORT_UPDATE ; 
 scalar_t__ IS_VF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSAL_CPU_TO_LE16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSAL_MEMSET (struct ecore_sp_init_data*,int /*<<< orphan*/ ,int) ; 
 void* OSAL_NULL ; 
 int /*<<< orphan*/  PROTOCOLID_ETH ; 
 int ecore_fw_vport (struct ecore_hwfn*,int /*<<< orphan*/ ,void**) ; 
 int ecore_sp_init_request (struct ecore_hwfn*,struct ecore_spq_entry**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ecore_sp_init_data*) ; 
 int /*<<< orphan*/  ecore_sp_update_accept_mode (struct ecore_hwfn*,struct vport_update_ramrod_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_sp_update_mcast_bin (struct vport_update_ramrod_data*,struct ecore_sp_vport_update_params*) ; 
 int ecore_sp_vport_update_rss (struct ecore_hwfn*,struct vport_update_ramrod_data*,struct ecore_rss_params*) ; 
 int /*<<< orphan*/  ecore_sp_vport_update_sge_tpa (struct vport_update_ramrod_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_spq_get_cid (struct ecore_hwfn*) ; 
 int ecore_spq_post (struct ecore_hwfn*,struct ecore_spq_entry*,void*) ; 
 int /*<<< orphan*/  ecore_spq_return_entry (struct ecore_hwfn*,struct ecore_spq_entry*) ; 
 int ecore_vf_pf_vport_update (struct ecore_hwfn*,struct ecore_sp_vport_update_params*) ; 

enum _ecore_status_t ecore_sp_vport_update(struct ecore_hwfn *p_hwfn,
					   struct ecore_sp_vport_update_params *p_params,
					   enum spq_mode comp_mode,
					   struct ecore_spq_comp_cb *p_comp_data)
{
	struct ecore_rss_params *p_rss_params = p_params->rss_params;
	struct vport_update_ramrod_data_cmn *p_cmn;
	struct ecore_sp_init_data init_data;
	struct vport_update_ramrod_data *p_ramrod = OSAL_NULL;
	struct ecore_spq_entry *p_ent = OSAL_NULL;
	u8 abs_vport_id = 0, val;
	enum _ecore_status_t rc = ECORE_NOTIMPL;

	if (IS_VF(p_hwfn->p_dev)) {
		rc = ecore_vf_pf_vport_update(p_hwfn, p_params);
		return rc;
	}

	rc = ecore_fw_vport(p_hwfn, p_params->vport_id, &abs_vport_id);
	if (rc != ECORE_SUCCESS)
		return rc;

	/* Get SPQ entry */
	OSAL_MEMSET(&init_data, 0, sizeof(init_data));
	init_data.cid = ecore_spq_get_cid(p_hwfn);
	init_data.opaque_fid = p_params->opaque_fid;
	init_data.comp_mode = comp_mode;
	init_data.p_comp_data = p_comp_data;

	rc = ecore_sp_init_request(p_hwfn, &p_ent,
				   ETH_RAMROD_VPORT_UPDATE,
				   PROTOCOLID_ETH, &init_data);
	if (rc != ECORE_SUCCESS)
		return rc;

	/* Copy input params to ramrod according to FW struct */
	p_ramrod = &p_ent->ramrod.vport_update;
	p_cmn = &p_ramrod->common;

	p_cmn->vport_id = abs_vport_id;

	p_cmn->rx_active_flg = p_params->vport_active_rx_flg;
	p_cmn->update_rx_active_flg = p_params->update_vport_active_rx_flg;
	p_cmn->tx_active_flg = p_params->vport_active_tx_flg;
	p_cmn->update_tx_active_flg = p_params->update_vport_active_tx_flg;

	p_cmn->accept_any_vlan = p_params->accept_any_vlan;
	val = p_params->update_accept_any_vlan_flg;
	p_cmn->update_accept_any_vlan_flg = val;

	p_cmn->inner_vlan_removal_en = p_params->inner_vlan_removal_flg;
	val = p_params->update_inner_vlan_removal_flg;
	p_cmn->update_inner_vlan_removal_en_flg = val;

	p_cmn->default_vlan_en = p_params->default_vlan_enable_flg;
	val = p_params->update_default_vlan_enable_flg;
	p_cmn->update_default_vlan_en_flg = val;

	p_cmn->default_vlan = OSAL_CPU_TO_LE16(p_params->default_vlan);
	p_cmn->update_default_vlan_flg = p_params->update_default_vlan_flg;

	p_cmn->silent_vlan_removal_en = p_params->silent_vlan_removal_flg;

	p_ramrod->common.tx_switching_en = p_params->tx_switching_flg;
#ifndef ASIC_ONLY
	if (CHIP_REV_IS_FPGA(p_hwfn->p_dev))
		if (p_ramrod->common.tx_switching_en ||
		    p_ramrod->common.update_tx_switching_en_flg) {
			DP_NOTICE(p_hwfn, false, "FPGA - why are we seeing tx-switching? Overriding it\n");
			p_ramrod->common.tx_switching_en = 0;
			p_ramrod->common.update_tx_switching_en_flg = 1;
		}
#endif
	p_cmn->update_tx_switching_en_flg = p_params->update_tx_switching_flg;

	p_cmn->anti_spoofing_en = p_params->anti_spoofing_en;
	val = p_params->update_anti_spoofing_en_flg;
	p_ramrod->common.update_anti_spoofing_en_flg = val;
	
	rc = ecore_sp_vport_update_rss(p_hwfn, p_ramrod, p_rss_params);
	if (rc != ECORE_SUCCESS) {
		/* Return spq entry which is taken in ecore_sp_init_request()*/
		ecore_spq_return_entry(p_hwfn, p_ent);
		return rc;
	}

	/* Update mcast bins for VFs, PF doesn't use this functionality */
	ecore_sp_update_mcast_bin(p_ramrod, p_params);

	ecore_sp_update_accept_mode(p_hwfn, p_ramrod, p_params->accept_flags);
	ecore_sp_vport_update_sge_tpa(p_ramrod, p_params->sge_tpa_params);
	return ecore_spq_post(p_hwfn, p_ent, OSAL_NULL);
}