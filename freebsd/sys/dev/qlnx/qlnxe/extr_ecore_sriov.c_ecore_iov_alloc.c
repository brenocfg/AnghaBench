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
struct ecore_pf_iov {int dummy; } ;
struct ecore_hwfn {struct ecore_pf_iov* pf_iov_info; int /*<<< orphan*/  p_dev; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ECORE_MSG_IOV ; 
 int ECORE_NOMEM ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_PF_SRIOV (struct ecore_hwfn*) ; 
 struct ecore_pf_iov* OSAL_ZALLOC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PROTOCOLID_COMMON ; 
 int ecore_iov_allocate_vfdb (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_spq_register_async_cb (struct ecore_hwfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_sriov_eqe_event ; 

enum _ecore_status_t ecore_iov_alloc(struct ecore_hwfn *p_hwfn)
{
	struct ecore_pf_iov *p_sriov;

	if (!IS_PF_SRIOV(p_hwfn)) {
		DP_VERBOSE(p_hwfn, ECORE_MSG_IOV,
			   "No SR-IOV - no need for IOV db\n");
		return ECORE_SUCCESS;
	}

	p_sriov = OSAL_ZALLOC(p_hwfn->p_dev, GFP_KERNEL, sizeof(*p_sriov));
	if (!p_sriov) {
		DP_NOTICE(p_hwfn, false, "Failed to allocate `struct ecore_sriov'\n");
		return ECORE_NOMEM;
	}

	p_hwfn->pf_iov_info = p_sriov;

	ecore_spq_register_async_cb(p_hwfn, PROTOCOLID_COMMON,
				    ecore_sriov_eqe_event);

	return ecore_iov_allocate_vfdb(p_hwfn);
}