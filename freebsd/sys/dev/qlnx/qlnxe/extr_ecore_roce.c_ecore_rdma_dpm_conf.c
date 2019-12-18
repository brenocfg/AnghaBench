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
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int /*<<< orphan*/  db_bar_no_edpm; int /*<<< orphan*/  dcbx_no_edpm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DORQ_REG_PF_DPM_ENABLE ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ECORE_MSG_DCB ; 
 int ECORE_MSG_RDMA ; 
 int /*<<< orphan*/  ecore_wr (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ecore_rdma_dpm_conf(struct ecore_hwfn *p_hwfn,
				struct ecore_ptt *p_ptt)
{
	u32 val;

	val = (p_hwfn->dcbx_no_edpm || p_hwfn->db_bar_no_edpm) ? 0 : 1;

	ecore_wr(p_hwfn, p_ptt, DORQ_REG_PF_DPM_ENABLE, val);
	DP_VERBOSE(p_hwfn, (ECORE_MSG_DCB | ECORE_MSG_RDMA),
		   "Changing DPM_EN state to %d (DCBX=%d, DB_BAR=%d)\n",
		   val, p_hwfn->dcbx_no_edpm, p_hwfn->db_bar_no_edpm);
}