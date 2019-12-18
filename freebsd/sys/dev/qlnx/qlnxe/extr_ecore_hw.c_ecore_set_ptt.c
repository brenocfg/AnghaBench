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
typedef  scalar_t__ u32 ;
struct ecore_ptt {scalar_t__ hwfn_id; int /*<<< orphan*/  idx; } ;
struct ecore_hwfn {scalar_t__ my_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ PXP_EXTERNAL_BAR_PF_WINDOW_SINGLE_SIZE ; 
 scalar_t__ ecore_ptt_get_bar_addr (struct ecore_ptt*) ; 
 scalar_t__ ecore_ptt_get_hw_addr (struct ecore_ptt*) ; 
 int /*<<< orphan*/  ecore_ptt_set_win (struct ecore_hwfn*,struct ecore_ptt*,scalar_t__) ; 

__attribute__((used)) static u32 ecore_set_ptt(struct ecore_hwfn *p_hwfn,
			 struct ecore_ptt *p_ptt,
			 u32 hw_addr)
{
	u32 win_hw_addr = ecore_ptt_get_hw_addr(p_ptt);
	u32 offset;

	offset = hw_addr - win_hw_addr;

	if (p_ptt->hwfn_id != p_hwfn->my_id)
		DP_NOTICE(p_hwfn, true,
			  "ptt[%d] of hwfn[%02x] is used by hwfn[%02x]!\n",
			  p_ptt->idx, p_ptt->hwfn_id, p_hwfn->my_id);

	/* Verify the address is within the window */
	if (hw_addr < win_hw_addr ||
	    offset >= PXP_EXTERNAL_BAR_PF_WINDOW_SINGLE_SIZE) {
		ecore_ptt_set_win(p_hwfn, p_ptt, hw_addr);
		offset = 0;
	}

	return ecore_ptt_get_bar_addr(p_ptt) + offset;
}