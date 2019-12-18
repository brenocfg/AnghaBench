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
struct ecore_queue_cid {scalar_t__ b_is_rx; } ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int /*<<< orphan*/  p_dev; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*) ; 
 int ECORE_AGAIN ; 
 int ECORE_SUCCESS ; 
 scalar_t__ IS_VF (int /*<<< orphan*/ ) ; 
 int ecore_get_rxq_coalesce (struct ecore_hwfn*,struct ecore_ptt*,struct ecore_queue_cid*,int /*<<< orphan*/ *) ; 
 int ecore_get_txq_coalesce (struct ecore_hwfn*,struct ecore_ptt*,struct ecore_queue_cid*,int /*<<< orphan*/ *) ; 
 struct ecore_ptt* ecore_ptt_acquire (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_ptt_release (struct ecore_hwfn*,struct ecore_ptt*) ; 
 int ecore_vf_pf_get_coalesce (struct ecore_hwfn*,int /*<<< orphan*/ *,struct ecore_queue_cid*) ; 

enum _ecore_status_t
ecore_get_queue_coalesce(struct ecore_hwfn *p_hwfn, u16 *p_coal,
			 void *handle)
{
	struct ecore_queue_cid *p_cid = (struct ecore_queue_cid *)handle;
	enum _ecore_status_t rc = ECORE_SUCCESS;
	struct ecore_ptt *p_ptt;

#ifdef CONFIG_ECORE_SRIOV
	if (IS_VF(p_hwfn->p_dev)) {
		rc = ecore_vf_pf_get_coalesce(p_hwfn, p_coal, p_cid);
		if (rc != ECORE_SUCCESS)
			DP_NOTICE(p_hwfn, false,
				  "Unable to read queue calescing\n");

		return rc;
	}
#endif

	p_ptt = ecore_ptt_acquire(p_hwfn);
	if (!p_ptt)
		return ECORE_AGAIN;

	if (p_cid->b_is_rx) {
		rc = ecore_get_rxq_coalesce(p_hwfn, p_ptt, p_cid, p_coal);
		if (rc != ECORE_SUCCESS)
			goto out;
	} else {
		rc = ecore_get_txq_coalesce(p_hwfn, p_ptt, p_cid, p_coal);
		if (rc != ECORE_SUCCESS)
			goto out;
	}

out:
	ecore_ptt_release(p_hwfn, p_ptt);

	return rc;
}