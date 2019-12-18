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
struct ecore_qm_info {int /*<<< orphan*/  num_pqs; } ;
struct ecore_hwfn {struct ecore_qm_info qm_info; } ;

/* Variables and functions */
 int PQ_FLAGS_OFLD ; 
 int /*<<< orphan*/  PQ_INIT_OFLD_TC ; 
 int /*<<< orphan*/  PQ_INIT_SHARE_VPORT ; 
 int ecore_get_pq_flags (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_init_qm_pq (struct ecore_hwfn*,struct ecore_qm_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_init_qm_set_idx (struct ecore_hwfn*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ecore_init_qm_offload_pq(struct ecore_hwfn *p_hwfn)
{
	struct ecore_qm_info *qm_info = &p_hwfn->qm_info;

	if (!(ecore_get_pq_flags(p_hwfn) & PQ_FLAGS_OFLD))
		return;

	ecore_init_qm_set_idx(p_hwfn, PQ_FLAGS_OFLD, qm_info->num_pqs);
	ecore_init_qm_pq(p_hwfn, qm_info, PQ_INIT_OFLD_TC, PQ_INIT_SHARE_VPORT);
}