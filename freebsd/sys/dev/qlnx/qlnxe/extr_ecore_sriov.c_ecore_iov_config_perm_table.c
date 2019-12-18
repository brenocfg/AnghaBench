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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct ecore_vf_info {int num_rxqs; int abs_vf_id; TYPE_1__* vf_queues; } ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  fw_rx_qid; } ;

/* Variables and functions */
 int PSWHST_REG_ZONE_PERMISSION_TABLE ; 
 int /*<<< orphan*/  ecore_fw_l2_queue (struct ecore_hwfn*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ecore_wr (struct ecore_hwfn*,struct ecore_ptt*,int,int) ; 

__attribute__((used)) static void ecore_iov_config_perm_table(struct ecore_hwfn	*p_hwfn,
					struct ecore_ptt	*p_ptt,
					struct ecore_vf_info	*vf,
					u8			enable)
{
	u32 reg_addr, val;
	u16 qzone_id = 0;
	int qid;

	for (qid = 0; qid < vf->num_rxqs; qid++) {
		ecore_fw_l2_queue(p_hwfn, vf->vf_queues[qid].fw_rx_qid,
				  &qzone_id);

		reg_addr = PSWHST_REG_ZONE_PERMISSION_TABLE + qzone_id * 4;
		val = enable ? (vf->abs_vf_id | (1 << 8)) : 0;
		ecore_wr(p_hwfn, p_ptt, reg_addr, val);
	}
}