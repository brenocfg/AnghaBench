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
struct TYPE_11__ {int update_enable_stag_pri_change; int enable_stag_pri_change; } ;
struct TYPE_12__ {TYPE_5__ pf_update; } ;
struct ecore_spq_entry {TYPE_6__ ramrod; } ;
struct ecore_sp_init_data {int /*<<< orphan*/  comp_mode; int /*<<< orphan*/  opaque_fid; int /*<<< orphan*/  cid; } ;
struct TYPE_8__ {scalar_t__ pri_type; } ;
struct TYPE_7__ {int /*<<< orphan*/  opaque_fid; } ;
struct ecore_hwfn {TYPE_4__* p_dcbx_info; TYPE_2__ ufp_info; TYPE_1__ hw_info; } ;
typedef  int /*<<< orphan*/  init_data ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_9__ {scalar_t__ dcbx_enabled; } ;
struct TYPE_10__ {TYPE_3__ results; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMON_RAMROD_PF_UPDATE ; 
 int /*<<< orphan*/  DP_INFO (struct ecore_hwfn*,char*,scalar_t__) ; 
 int ECORE_INVAL ; 
 int ECORE_NOTIMPL ; 
 int /*<<< orphan*/  ECORE_SPQ_MODE_CB ; 
 int ECORE_SUCCESS ; 
 scalar_t__ ECORE_UFP_PRI_OS ; 
 scalar_t__ ECORE_UFP_PRI_UNKNOWN ; 
 int /*<<< orphan*/  OSAL_MEMSET (struct ecore_sp_init_data*,int /*<<< orphan*/ ,int) ; 
 struct ecore_spq_entry* OSAL_NULL ; 
 int /*<<< orphan*/  PROTOCOLID_COMMON ; 
 int ecore_sp_init_request (struct ecore_hwfn*,struct ecore_spq_entry**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ecore_sp_init_data*) ; 
 int /*<<< orphan*/  ecore_spq_get_cid (struct ecore_hwfn*) ; 
 int ecore_spq_post (struct ecore_hwfn*,struct ecore_spq_entry*,struct ecore_spq_entry*) ; 

enum _ecore_status_t ecore_sp_pf_update_ufp(struct ecore_hwfn *p_hwfn)
{
	struct ecore_spq_entry *p_ent = OSAL_NULL;
	struct ecore_sp_init_data init_data;
	enum _ecore_status_t rc = ECORE_NOTIMPL;

	if (p_hwfn->ufp_info.pri_type == ECORE_UFP_PRI_UNKNOWN) {
		DP_INFO(p_hwfn, "Invalid priority type %d\n",
			p_hwfn->ufp_info.pri_type);
		return ECORE_INVAL;
	}

	/* Get SPQ entry */
	OSAL_MEMSET(&init_data, 0, sizeof(init_data));
	init_data.cid = ecore_spq_get_cid(p_hwfn);
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = ECORE_SPQ_MODE_CB;

	rc = ecore_sp_init_request(p_hwfn, &p_ent,
				   COMMON_RAMROD_PF_UPDATE, PROTOCOLID_COMMON,
				   &init_data);
	if (rc != ECORE_SUCCESS)
		return rc;

	p_ent->ramrod.pf_update.update_enable_stag_pri_change = true;
	if ((p_hwfn->ufp_info.pri_type == ECORE_UFP_PRI_OS) ||
	    (p_hwfn->p_dcbx_info->results.dcbx_enabled))
		p_ent->ramrod.pf_update.enable_stag_pri_change = 1;
	else
		p_ent->ramrod.pf_update.enable_stag_pri_change = 0;

	return ecore_spq_post(p_hwfn, p_ent, OSAL_NULL);
}