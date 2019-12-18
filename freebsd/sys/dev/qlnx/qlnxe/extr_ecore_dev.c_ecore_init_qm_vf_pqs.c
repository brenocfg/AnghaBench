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
typedef  scalar_t__ u16 ;
struct ecore_qm_info {scalar_t__ num_vf_pqs; int /*<<< orphan*/  num_pqs; } ;
struct ecore_hwfn {struct ecore_qm_info qm_info; } ;

/* Variables and functions */
 int PQ_FLAGS_VFS ; 
 int /*<<< orphan*/  PQ_INIT_DEFAULT_TC ; 
 int /*<<< orphan*/  PQ_INIT_VF_RL ; 
 int ecore_get_pq_flags (struct ecore_hwfn*) ; 
 scalar_t__ ecore_init_qm_get_num_vfs (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_init_qm_pq (struct ecore_hwfn*,struct ecore_qm_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_init_qm_set_idx (struct ecore_hwfn*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ecore_init_qm_vf_pqs(struct ecore_hwfn *p_hwfn)
{
	struct ecore_qm_info *qm_info = &p_hwfn->qm_info;
	u16 vf_idx, num_vfs = ecore_init_qm_get_num_vfs(p_hwfn);

	if (!(ecore_get_pq_flags(p_hwfn) & PQ_FLAGS_VFS))
		return;

	ecore_init_qm_set_idx(p_hwfn, PQ_FLAGS_VFS, qm_info->num_pqs);
	qm_info->num_vf_pqs = num_vfs;
	for (vf_idx = 0; vf_idx < num_vfs; vf_idx++)
		ecore_init_qm_pq(p_hwfn, qm_info, PQ_INIT_DEFAULT_TC, PQ_INIT_VF_RL);
}