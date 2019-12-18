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
struct ecore_hwfn {int /*<<< orphan*/  p_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ECORE_SRIOV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_PF_SRIOV_ALLOC (struct ecore_hwfn*) ; 
 scalar_t__ IS_VF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_iov_is_valid_vfid (struct ecore_hwfn*,int,int,int) ; 

__attribute__((used)) static bool _ecore_iov_pf_sanity_check(struct ecore_hwfn *p_hwfn, int vfid,
				       bool b_fail_malicious)
{
	/* Check PF supports sriov */
	if (IS_VF(p_hwfn->p_dev) || !IS_ECORE_SRIOV(p_hwfn->p_dev) ||
	    !IS_PF_SRIOV_ALLOC(p_hwfn))
		return false;

	/* Check VF validity */
	if (!ecore_iov_is_valid_vfid(p_hwfn, vfid, true, b_fail_malicious))
		return false;

	return true;
}