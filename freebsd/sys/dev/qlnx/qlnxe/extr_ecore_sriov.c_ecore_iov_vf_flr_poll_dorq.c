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
struct ecore_vf_info {int /*<<< orphan*/  abs_vf_id; scalar_t__ concrete_fid; } ;
struct ecore_ptt {int dummy; } ;
struct TYPE_2__ {scalar_t__ concrete_fid; } ;
struct ecore_hwfn {TYPE_1__ hw_info; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DORQ_REG_VF_USAGE_CNT ; 
 int /*<<< orphan*/  DP_ERR (struct ecore_hwfn*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ECORE_SUCCESS ; 
 int ECORE_TIMEOUT ; 
 int /*<<< orphan*/  OSAL_MSLEEP (int) ; 
 int /*<<< orphan*/  ecore_fid_pretend (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_rd (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum _ecore_status_t
ecore_iov_vf_flr_poll_dorq(struct ecore_hwfn *p_hwfn,
			   struct ecore_vf_info *p_vf,
			   struct ecore_ptt *p_ptt)
{
	int cnt;
	u32 val;

	ecore_fid_pretend(p_hwfn, p_ptt, (u16)p_vf->concrete_fid);

	for (cnt = 0; cnt < 50; cnt++) {
		val = ecore_rd(p_hwfn, p_ptt, DORQ_REG_VF_USAGE_CNT);
		if (!val)
			break;
		OSAL_MSLEEP(20);
	}
	ecore_fid_pretend(p_hwfn, p_ptt, (u16)p_hwfn->hw_info.concrete_fid);

	if (cnt == 50) {
		DP_ERR(p_hwfn, "VF[%d] - dorq failed to cleanup [usage 0x%08x]\n",
		       p_vf->abs_vf_id, val);
		return ECORE_TIMEOUT;
	}

	return ECORE_SUCCESS;
}