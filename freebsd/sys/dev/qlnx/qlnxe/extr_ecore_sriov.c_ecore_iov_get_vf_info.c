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
struct ecore_vf_info {int dummy; } ;
struct ecore_hwfn {TYPE_1__* pf_iov_info; int /*<<< orphan*/  p_dev; } ;
struct TYPE_2__ {struct ecore_vf_info* vfs_array; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct ecore_hwfn*,char*,size_t) ; 
 int /*<<< orphan*/  DP_NOTICE (int /*<<< orphan*/ ,int,char*) ; 
 struct ecore_vf_info* OSAL_NULL ; 
 scalar_t__ ecore_iov_is_valid_vfid (struct ecore_hwfn*,size_t,int,int) ; 

struct ecore_vf_info *ecore_iov_get_vf_info(struct ecore_hwfn *p_hwfn,
					    u16 relative_vf_id,
					    bool b_enabled_only)
{
	struct ecore_vf_info *vf = OSAL_NULL;

	if (!p_hwfn->pf_iov_info) {
		DP_NOTICE(p_hwfn->p_dev, true, "No iov info\n");
		return OSAL_NULL;
	}

	if (ecore_iov_is_valid_vfid(p_hwfn, relative_vf_id,
				    b_enabled_only, false))
		vf = &p_hwfn->pf_iov_info->vfs_array[relative_vf_id];
	else
		DP_ERR(p_hwfn, "ecore_iov_get_vf_info: VF[%d] is not enabled\n",
		       relative_vf_id);

	return vf;
}