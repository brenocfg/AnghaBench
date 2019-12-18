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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct ecore_hwfn {struct ecore_dev* p_dev; } ;
struct ecore_dev {scalar_t__ int_coalescing_mode; int rx_coalesce_usecs; int tx_coalesce_usecs; } ;
struct cau_sb_entry {int /*<<< orphan*/  data; int /*<<< orphan*/  params; } ;

/* Variables and functions */
 int CAU_HC_DISABLE_STATE ; 
 int CAU_HC_ENABLE_STATE ; 
 int /*<<< orphan*/  CAU_SB_ENTRY_PF_NUMBER ; 
 int /*<<< orphan*/  CAU_SB_ENTRY_SB_TIMESET0 ; 
 int /*<<< orphan*/  CAU_SB_ENTRY_SB_TIMESET1 ; 
 int /*<<< orphan*/  CAU_SB_ENTRY_STATE0 ; 
 int /*<<< orphan*/  CAU_SB_ENTRY_STATE1 ; 
 int /*<<< orphan*/  CAU_SB_ENTRY_TIMER_RES0 ; 
 int /*<<< orphan*/  CAU_SB_ENTRY_TIMER_RES1 ; 
 int /*<<< orphan*/  CAU_SB_ENTRY_VF_NUMBER ; 
 int /*<<< orphan*/  CAU_SB_ENTRY_VF_VALID ; 
 int ECORE_CAU_DEF_RX_USECS ; 
 int ECORE_CAU_DEF_TX_USECS ; 
 scalar_t__ ECORE_COAL_MODE_ENABLE ; 
 int /*<<< orphan*/  OSAL_MEMSET (struct cau_sb_entry*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void ecore_init_cau_sb_entry(struct ecore_hwfn *p_hwfn,
			     struct cau_sb_entry *p_sb_entry,
			     u8 pf_id, u16 vf_number, u8 vf_valid)
{
	struct ecore_dev *p_dev = p_hwfn->p_dev;
	u32 cau_state;
	u8 timer_res;

	OSAL_MEMSET(p_sb_entry, 0, sizeof(*p_sb_entry));

	SET_FIELD(p_sb_entry->params, CAU_SB_ENTRY_PF_NUMBER, pf_id);
	SET_FIELD(p_sb_entry->params, CAU_SB_ENTRY_VF_NUMBER, vf_number);
	SET_FIELD(p_sb_entry->params, CAU_SB_ENTRY_VF_VALID, vf_valid);
	SET_FIELD(p_sb_entry->params, CAU_SB_ENTRY_SB_TIMESET0, 0x7F);
	SET_FIELD(p_sb_entry->params, CAU_SB_ENTRY_SB_TIMESET1, 0x7F);

	cau_state = CAU_HC_DISABLE_STATE;

	if (p_dev->int_coalescing_mode == ECORE_COAL_MODE_ENABLE) {
		cau_state = CAU_HC_ENABLE_STATE;
		if (!p_dev->rx_coalesce_usecs)
			p_dev->rx_coalesce_usecs = ECORE_CAU_DEF_RX_USECS;
		if (!p_dev->tx_coalesce_usecs)
			p_dev->tx_coalesce_usecs = ECORE_CAU_DEF_TX_USECS;
	}

	/* Coalesce = (timeset << timer-res), timeset is 7bit wide */
	if (p_dev->rx_coalesce_usecs <= 0x7F)
		timer_res = 0;
	else if (p_dev->rx_coalesce_usecs <= 0xFF)
		timer_res = 1;
	else
		timer_res = 2;
	SET_FIELD(p_sb_entry->params, CAU_SB_ENTRY_TIMER_RES0, timer_res);

	if (p_dev->tx_coalesce_usecs <= 0x7F)
		timer_res = 0;
	else if (p_dev->tx_coalesce_usecs <= 0xFF)
		timer_res = 1;
	else
		timer_res = 2;
	SET_FIELD(p_sb_entry->params, CAU_SB_ENTRY_TIMER_RES1, timer_res);

	SET_FIELD(p_sb_entry->data, CAU_SB_ENTRY_STATE0, cau_state);
	SET_FIELD(p_sb_entry->data, CAU_SB_ENTRY_STATE1, cau_state);
}