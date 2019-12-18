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
typedef  int /*<<< orphan*/  u16 ;
struct ecore_vf_info {int req_spoofchk_val; } ;
struct ecore_hwfn {int dummy; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*) ; 
 int ECORE_INVAL ; 
 int ECORE_SUCCESS ; 
 int __ecore_iov_spoofchk_set (struct ecore_hwfn*,struct ecore_vf_info*,int) ; 
 struct ecore_vf_info* ecore_iov_get_vf_info (struct ecore_hwfn*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ecore_iov_pf_sanity_check (struct ecore_hwfn*,int) ; 
 int /*<<< orphan*/  ecore_iov_vf_has_vport_instance (struct ecore_hwfn*,int) ; 

enum _ecore_status_t ecore_iov_spoofchk_set(struct ecore_hwfn *p_hwfn,
					    int vfid, bool val)
{
	struct ecore_vf_info *vf;
	enum _ecore_status_t rc = ECORE_INVAL;

	if (!ecore_iov_pf_sanity_check(p_hwfn, vfid)) {
		DP_NOTICE(p_hwfn, true,
			  "SR-IOV sanity check failed, can't set spoofchk\n");
		goto out;
	}

	vf = ecore_iov_get_vf_info(p_hwfn, (u16)vfid, true);
	if (!vf)
		goto out;

	if (!ecore_iov_vf_has_vport_instance(p_hwfn, vfid)) {
		/* After VF VPORT start PF will configure spoof check */
		vf->req_spoofchk_val = val;
		rc = ECORE_SUCCESS;
		goto out;
	}

	rc = __ecore_iov_spoofchk_set(p_hwfn, vf, val);

out:
	return rc;
}