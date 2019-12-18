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
struct ecore_qm_info {scalar_t__ first_rl_pq; scalar_t__ first_mcos_pq; scalar_t__ first_vf_pq; scalar_t__ num_vf_pqs; scalar_t__ num_pf_rls; scalar_t__ num_vports; scalar_t__ num_pqs; } ;
struct ecore_hwfn {struct ecore_qm_info qm_info; } ;

/* Variables and functions */

__attribute__((used)) static void ecore_init_qm_reset_params(struct ecore_hwfn *p_hwfn)
{
	struct ecore_qm_info *qm_info = &p_hwfn->qm_info;

	qm_info->num_pqs = 0;
	qm_info->num_vports = 0;
	qm_info->num_pf_rls = 0;
	qm_info->num_vf_pqs = 0;
	qm_info->first_vf_pq = 0;
	qm_info->first_mcos_pq = 0;
	qm_info->first_rl_pq = 0;
}