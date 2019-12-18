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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct ecore_vf_info {int b_malicious; int /*<<< orphan*/  state; int /*<<< orphan*/  abs_vf_id; scalar_t__ concrete_fid; int /*<<< orphan*/  num_sbs; scalar_t__ to_disable; } ;
struct ecore_ptt {int dummy; } ;
struct TYPE_2__ {scalar_t__ concrete_fid; int /*<<< orphan*/  hw_mode; } ;
struct ecore_hwfn {TYPE_1__ hw_info; int /*<<< orphan*/  rel_pf_id; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECORE_MSG_IOV ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  ECORE_VF_ABS_ID (struct ecore_hwfn*,struct ecore_vf_info*) ; 
 int /*<<< orphan*/  IGU_REG_VF_CONFIGURATION_RT_OFFSET ; 
 int /*<<< orphan*/  IGU_VF_CONF_FUNC_EN ; 
 int /*<<< orphan*/  IGU_VF_CONF_PARENT ; 
 int /*<<< orphan*/  PHASE_VF ; 
 int /*<<< orphan*/  SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STORE_RT_REG (struct ecore_hwfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VF_FREE ; 
 int /*<<< orphan*/  ecore_fid_pretend (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_init_run (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ecore_iov_enable_vf_access_msix (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_iov_vf_igu_reset (struct ecore_hwfn*,struct ecore_ptt*,struct ecore_vf_info*) ; 
 int /*<<< orphan*/  ecore_iov_vf_pglue_clear_err (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum _ecore_status_t ecore_iov_enable_vf_access(struct ecore_hwfn *p_hwfn,
						       struct ecore_ptt *p_ptt,
						       struct ecore_vf_info *vf)
{
	u32 igu_vf_conf = IGU_VF_CONF_FUNC_EN;
	enum _ecore_status_t rc = ECORE_SUCCESS;

	/* It's possible VF was previously considered malicious -
	 * clear the indication even if we're only going to disable VF.
	 */
	vf->b_malicious = false;

	if (vf->to_disable)
		return ECORE_SUCCESS;

	DP_VERBOSE(p_hwfn, ECORE_MSG_IOV, "Enable internal access for vf %x [abs %x]\n",
		   vf->abs_vf_id, ECORE_VF_ABS_ID(p_hwfn, vf));

	ecore_iov_vf_pglue_clear_err(p_hwfn, p_ptt,
				     ECORE_VF_ABS_ID(p_hwfn, vf));

	ecore_iov_vf_igu_reset(p_hwfn, p_ptt, vf);

	rc = ecore_iov_enable_vf_access_msix(p_hwfn, p_ptt,
					     vf->abs_vf_id, vf->num_sbs);
	if (rc != ECORE_SUCCESS)
		return rc;

	ecore_fid_pretend(p_hwfn, p_ptt, (u16)vf->concrete_fid);

	SET_FIELD(igu_vf_conf, IGU_VF_CONF_PARENT, p_hwfn->rel_pf_id);
	STORE_RT_REG(p_hwfn, IGU_REG_VF_CONFIGURATION_RT_OFFSET, igu_vf_conf);

	ecore_init_run(p_hwfn, p_ptt, PHASE_VF, vf->abs_vf_id,
		       p_hwfn->hw_info.hw_mode);

	/* unpretend */
	ecore_fid_pretend(p_hwfn, p_ptt, (u16)p_hwfn->hw_info.concrete_fid);

	vf->state = VF_FREE;

	return rc;
}