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
struct malicious_vf_eqe_data {int /*<<< orphan*/  err_id; int /*<<< orphan*/  vf_id; } ;
struct ecore_vf_info {int b_malicious; int /*<<< orphan*/  relative_vf_id; int /*<<< orphan*/  abs_vf_id; } ;
struct ecore_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_INFO (struct ecore_hwfn*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSAL_PF_VF_MALICIOUS (struct ecore_hwfn*,int /*<<< orphan*/ ) ; 
 struct ecore_vf_info* ecore_sriov_get_vf_from_absid (struct ecore_hwfn*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ecore_sriov_vfpf_malicious(struct ecore_hwfn *p_hwfn,
				       struct malicious_vf_eqe_data *p_data)
{
	struct ecore_vf_info *p_vf;

	p_vf = ecore_sriov_get_vf_from_absid(p_hwfn, p_data->vf_id);

	if (!p_vf)
		return;

	if (!p_vf->b_malicious) {
		DP_NOTICE(p_hwfn, false,
			  "VF [%d] - Malicious behavior [%02x]\n",
			  p_vf->abs_vf_id, p_data->err_id);

		p_vf->b_malicious = true;
	} else {
		DP_INFO(p_hwfn,
			"VF [%d] - Malicious behavior [%02x]\n",
			p_vf->abs_vf_id, p_data->err_id);
	}

	OSAL_PF_VF_MALICIOUS(p_hwfn, p_vf->relative_vf_id);
}