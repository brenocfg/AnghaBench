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
typedef  size_t u8 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*) ; 
 size_t NUM_OF_TCS ; 
 int QM_INVALID_PQ_ID ; 
 scalar_t__ QM_REG_WFQVPWEIGHT ; 
 scalar_t__ QM_WFQ_INC_VAL (int) ; 
 scalar_t__ QM_WFQ_MAX_INC_VAL ; 
 int /*<<< orphan*/  ecore_wr (struct ecore_hwfn*,struct ecore_ptt*,scalar_t__,scalar_t__) ; 

int ecore_init_vport_wfq(struct ecore_hwfn *p_hwfn,
						 struct ecore_ptt *p_ptt,
						 u16 first_tx_pq_id[NUM_OF_TCS],
						 u16 vport_wfq)
{
	u16 vport_pq_id;
	u32 inc_val;
	u8 tc;

	inc_val = QM_WFQ_INC_VAL(vport_wfq);
	if (!inc_val || inc_val > QM_WFQ_MAX_INC_VAL) {
		DP_NOTICE(p_hwfn, true, "Invalid VPORT WFQ weight configuration\n");
		return -1;
	}

	for (tc = 0; tc < NUM_OF_TCS; tc++) {
		vport_pq_id = first_tx_pq_id[tc];
		if (vport_pq_id != QM_INVALID_PQ_ID) {
			ecore_wr(p_hwfn, p_ptt, QM_REG_WFQVPWEIGHT + vport_pq_id * 4, inc_val);
		}
	}

	return 0;
}