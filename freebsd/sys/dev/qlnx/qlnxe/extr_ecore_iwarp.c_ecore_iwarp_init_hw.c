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
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int b_rdma_enabled_in_prs; int /*<<< orphan*/  rdma_prs_search_reg; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  PRS_REG_SEARCH_TCP ; 
 int /*<<< orphan*/  ecore_wr (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int) ; 

enum _ecore_status_t
ecore_iwarp_init_hw(struct ecore_hwfn *p_hwfn, struct ecore_ptt *p_ptt)
{
	p_hwfn->rdma_prs_search_reg = PRS_REG_SEARCH_TCP;
	ecore_wr(p_hwfn, p_ptt, p_hwfn->rdma_prs_search_reg, 1);
	p_hwfn->b_rdma_enabled_in_prs = true;

	return 0;
}