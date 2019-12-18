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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct ecore_qm_info {int /*<<< orphan*/  first_vf_pq; int /*<<< orphan*/  low_latency_pq; int /*<<< orphan*/  offload_pq; int /*<<< orphan*/  pure_ack_pq; int /*<<< orphan*/  ooo_pq; int /*<<< orphan*/  pure_lb_pq; int /*<<< orphan*/  first_mcos_pq; int /*<<< orphan*/  first_rl_pq; } ;
struct ecore_hwfn {struct ecore_qm_info qm_info; } ;
typedef  int /*<<< orphan*/  pq_flags ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct ecore_hwfn*,char*,int) ; 
 int OSAL_BITMAP_WEIGHT (unsigned long*,int) ; 
 int /*<<< orphan*/ * OSAL_NULL ; 
#define  PQ_FLAGS_ACK 135 
#define  PQ_FLAGS_LB 134 
#define  PQ_FLAGS_LLT 133 
#define  PQ_FLAGS_MCOS 132 
#define  PQ_FLAGS_OFLD 131 
#define  PQ_FLAGS_OOO 130 
#define  PQ_FLAGS_RLS 129 
#define  PQ_FLAGS_VFS 128 

__attribute__((used)) static u16 *ecore_init_qm_get_idx_from_flags(struct ecore_hwfn *p_hwfn,
					     u32 pq_flags)
{
	struct ecore_qm_info *qm_info = &p_hwfn->qm_info;

	/* Can't have multiple flags set here */
	if (OSAL_BITMAP_WEIGHT((unsigned long *)&pq_flags, sizeof(pq_flags)) > 1)
		goto err;

	switch (pq_flags) {
	case PQ_FLAGS_RLS:
		return &qm_info->first_rl_pq;
	case PQ_FLAGS_MCOS:
		return &qm_info->first_mcos_pq;
	case PQ_FLAGS_LB:
		return &qm_info->pure_lb_pq;
	case PQ_FLAGS_OOO:
		return &qm_info->ooo_pq;
	case PQ_FLAGS_ACK:
		return &qm_info->pure_ack_pq;
	case PQ_FLAGS_OFLD:
		return &qm_info->offload_pq;
	case PQ_FLAGS_LLT:
		return &qm_info->low_latency_pq;
	case PQ_FLAGS_VFS:
		return &qm_info->first_vf_pq;
	default:
		goto err;
	}

err:
	DP_ERR(p_hwfn, "BAD pq flags %d\n", pq_flags);
	return OSAL_NULL;
}