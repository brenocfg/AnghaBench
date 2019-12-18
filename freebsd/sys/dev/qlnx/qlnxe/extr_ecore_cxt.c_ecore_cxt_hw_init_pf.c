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
struct ecore_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ecore_cdu_init_pf (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_cm_init_pf (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_dq_init_pf (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_ilt_init_pf (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_prs_init_pf (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_qm_init_pf (struct ecore_hwfn*,struct ecore_ptt*,int) ; 
 int /*<<< orphan*/  ecore_src_init_pf (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_tm_init_pf (struct ecore_hwfn*) ; 

void ecore_cxt_hw_init_pf(struct ecore_hwfn *p_hwfn, struct ecore_ptt *p_ptt)
{
	ecore_qm_init_pf(p_hwfn, p_ptt, true);
	ecore_cm_init_pf(p_hwfn);
	ecore_dq_init_pf(p_hwfn);
	ecore_cdu_init_pf(p_hwfn);
	ecore_ilt_init_pf(p_hwfn);
	ecore_src_init_pf(p_hwfn);
	ecore_tm_init_pf(p_hwfn);
	ecore_prs_init_pf(p_hwfn);
}