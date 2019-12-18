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
struct ecore_hwfn {int /*<<< orphan*/  pf_iov_info; int /*<<< orphan*/  p_dev; } ;

/* Variables and functions */
 scalar_t__ IS_PF_SRIOV_ALLOC (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  OSAL_FREE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSAL_NULL ; 
 int /*<<< orphan*/  PROTOCOLID_COMMON ; 
 int /*<<< orphan*/  ecore_iov_free_vfdb (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_spq_unregister_async_cb (struct ecore_hwfn*,int /*<<< orphan*/ ) ; 

void ecore_iov_free(struct ecore_hwfn *p_hwfn)
{
	ecore_spq_unregister_async_cb(p_hwfn, PROTOCOLID_COMMON);

	if (IS_PF_SRIOV_ALLOC(p_hwfn)) {
		ecore_iov_free_vfdb(p_hwfn);
		OSAL_FREE(p_hwfn->p_dev, p_hwfn->pf_iov_info);
		p_hwfn->pf_iov_info = OSAL_NULL;
	}
}