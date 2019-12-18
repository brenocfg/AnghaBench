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
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int /*<<< orphan*/  rdma_prs_search_reg; scalar_t__ b_rdma_enabled_in_prs; TYPE_1__* p_rdma_info; int /*<<< orphan*/  p_dev; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_2__ {scalar_t__ active; } ;

/* Variables and functions */
 int ECORE_AGAIN ; 
 int ECORE_SUCCESS ; 
 scalar_t__ IS_VF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NIG_REG_RX_LLH_BRB_GATE_DNTFWD_PERPF ; 
 struct ecore_ptt* ecore_ptt_acquire (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_ptt_release (struct ecore_hwfn*,struct ecore_ptt*) ; 
 int /*<<< orphan*/  ecore_wr (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int) ; 

enum _ecore_status_t ecore_hw_start_fastpath(struct ecore_hwfn *p_hwfn)
{
	struct ecore_ptt *p_ptt;

	if (IS_VF(p_hwfn->p_dev))
		return ECORE_SUCCESS;

	p_ptt = ecore_ptt_acquire(p_hwfn);
	if (!p_ptt)
		return ECORE_AGAIN;

	/* If roce info is allocated it means roce is initialized and should
	 * be enabled in searcher.
	 */
	if (p_hwfn->p_rdma_info &&
	    p_hwfn->p_rdma_info->active &&
	    p_hwfn->b_rdma_enabled_in_prs)
		ecore_wr(p_hwfn, p_ptt, p_hwfn->rdma_prs_search_reg, 0x1);

	/* Re-open incoming traffic */
	ecore_wr(p_hwfn, p_ptt,
		 NIG_REG_RX_LLH_BRB_GATE_DNTFWD_PERPF, 0x0);
	ecore_ptt_release(p_hwfn, p_ptt);

	return ECORE_SUCCESS;
}