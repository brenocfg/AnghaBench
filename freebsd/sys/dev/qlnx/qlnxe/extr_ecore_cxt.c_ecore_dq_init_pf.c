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
typedef  int u32 ;
struct ecore_hwfn {struct ecore_cxt_mngr* p_cxt_mngr; } ;
struct ecore_cxt_mngr {TYPE_1__* conn_cfg; } ;
struct TYPE_2__ {int cid_count; int cids_per_vf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DORQ_REG_PF_MAX_ICID_0_RT_OFFSET ; 
 int /*<<< orphan*/  DORQ_REG_PF_MAX_ICID_1_RT_OFFSET ; 
 int /*<<< orphan*/  DORQ_REG_PF_MAX_ICID_2_RT_OFFSET ; 
 int /*<<< orphan*/  DORQ_REG_PF_MAX_ICID_3_RT_OFFSET ; 
 int /*<<< orphan*/  DORQ_REG_PF_MAX_ICID_4_RT_OFFSET ; 
 int /*<<< orphan*/  DORQ_REG_PF_MAX_ICID_5_RT_OFFSET ; 
 int /*<<< orphan*/  DORQ_REG_PF_MAX_ICID_6_RT_OFFSET ; 
 int /*<<< orphan*/  DORQ_REG_PF_MAX_ICID_7_RT_OFFSET ; 
 int /*<<< orphan*/  DORQ_REG_VF_MAX_ICID_0_RT_OFFSET ; 
 int /*<<< orphan*/  DORQ_REG_VF_MAX_ICID_1_RT_OFFSET ; 
 int /*<<< orphan*/  DORQ_REG_VF_MAX_ICID_2_RT_OFFSET ; 
 int /*<<< orphan*/  DORQ_REG_VF_MAX_ICID_3_RT_OFFSET ; 
 int /*<<< orphan*/  DORQ_REG_VF_MAX_ICID_4_RT_OFFSET ; 
 int /*<<< orphan*/  DORQ_REG_VF_MAX_ICID_5_RT_OFFSET ; 
 int /*<<< orphan*/  DORQ_REG_VF_MAX_ICID_6_RT_OFFSET ; 
 int /*<<< orphan*/  DORQ_REG_VF_MAX_ICID_7_RT_OFFSET ; 
 int DQ_RANGE_SHIFT ; 
 int /*<<< orphan*/  STORE_RT_REG (struct ecore_hwfn*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ecore_dq_init_pf(struct ecore_hwfn *p_hwfn)
{
	struct ecore_cxt_mngr *p_mngr = p_hwfn->p_cxt_mngr;
	u32 dq_pf_max_cid = 0, dq_vf_max_cid = 0;

	dq_pf_max_cid += (p_mngr->conn_cfg[0].cid_count >> DQ_RANGE_SHIFT);
	STORE_RT_REG(p_hwfn, DORQ_REG_PF_MAX_ICID_0_RT_OFFSET, dq_pf_max_cid);

	dq_vf_max_cid += (p_mngr->conn_cfg[0].cids_per_vf >> DQ_RANGE_SHIFT);
	STORE_RT_REG(p_hwfn, DORQ_REG_VF_MAX_ICID_0_RT_OFFSET, dq_vf_max_cid);

	dq_pf_max_cid += (p_mngr->conn_cfg[1].cid_count >> DQ_RANGE_SHIFT);
	STORE_RT_REG(p_hwfn, DORQ_REG_PF_MAX_ICID_1_RT_OFFSET, dq_pf_max_cid);

	dq_vf_max_cid += (p_mngr->conn_cfg[1].cids_per_vf >> DQ_RANGE_SHIFT);
	STORE_RT_REG(p_hwfn, DORQ_REG_VF_MAX_ICID_1_RT_OFFSET, dq_vf_max_cid);

	dq_pf_max_cid += (p_mngr->conn_cfg[2].cid_count >> DQ_RANGE_SHIFT);
	STORE_RT_REG(p_hwfn, DORQ_REG_PF_MAX_ICID_2_RT_OFFSET, dq_pf_max_cid);

	dq_vf_max_cid += (p_mngr->conn_cfg[2].cids_per_vf >> DQ_RANGE_SHIFT);
	STORE_RT_REG(p_hwfn, DORQ_REG_VF_MAX_ICID_2_RT_OFFSET, dq_vf_max_cid);

	dq_pf_max_cid += (p_mngr->conn_cfg[3].cid_count >> DQ_RANGE_SHIFT);
	STORE_RT_REG(p_hwfn, DORQ_REG_PF_MAX_ICID_3_RT_OFFSET, dq_pf_max_cid);

	dq_vf_max_cid += (p_mngr->conn_cfg[3].cids_per_vf >> DQ_RANGE_SHIFT);
	STORE_RT_REG(p_hwfn, DORQ_REG_VF_MAX_ICID_3_RT_OFFSET, dq_vf_max_cid);

	dq_pf_max_cid += (p_mngr->conn_cfg[4].cid_count >> DQ_RANGE_SHIFT);
	STORE_RT_REG(p_hwfn, DORQ_REG_PF_MAX_ICID_4_RT_OFFSET, dq_pf_max_cid);

	dq_vf_max_cid += (p_mngr->conn_cfg[4].cids_per_vf >> DQ_RANGE_SHIFT);
	STORE_RT_REG(p_hwfn, DORQ_REG_VF_MAX_ICID_4_RT_OFFSET, dq_vf_max_cid);

	dq_pf_max_cid += (p_mngr->conn_cfg[5].cid_count >> DQ_RANGE_SHIFT);
	STORE_RT_REG(p_hwfn, DORQ_REG_PF_MAX_ICID_5_RT_OFFSET, dq_pf_max_cid);

	dq_vf_max_cid += (p_mngr->conn_cfg[5].cids_per_vf >> DQ_RANGE_SHIFT);
	STORE_RT_REG(p_hwfn, DORQ_REG_VF_MAX_ICID_5_RT_OFFSET, dq_vf_max_cid);

	/* Connection types 6 & 7 are not in use, yet they must be configured
	 * as the highest possible connection. Not configuring them means the
	 * defaults will be  used, and with a large number of cids a bug may
	 * occur, if the defaults will be smaller than dq_pf_max_cid /
	 * dq_vf_max_cid.
	 */
	STORE_RT_REG(p_hwfn, DORQ_REG_PF_MAX_ICID_6_RT_OFFSET, dq_pf_max_cid);
	STORE_RT_REG(p_hwfn, DORQ_REG_VF_MAX_ICID_6_RT_OFFSET, dq_vf_max_cid);

	STORE_RT_REG(p_hwfn, DORQ_REG_PF_MAX_ICID_7_RT_OFFSET, dq_pf_max_cid);
	STORE_RT_REG(p_hwfn, DORQ_REG_VF_MAX_ICID_7_RT_OFFSET, dq_vf_max_cid);
}