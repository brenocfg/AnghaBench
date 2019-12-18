#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ath_hal {int dummy; } ;
struct TYPE_5__ {int dma_dbg_4; int dma_dbg_5; int dma_dbg_6; int dma_dbg_3; } ;
typedef  TYPE_1__ mac_dbg_regs_t ;
struct TYPE_6__ {int states; int dcu_chain_state; int dcu_complete_state; int qcu_stitch_state; int qcu_fetch_state; int qcu_complete_state; } ;
typedef  TYPE_2__ hal_mac_hang_check_t ;
typedef  int HAL_BOOL ;

/* Variables and functions */
 int dcu_chain_state ; 
 int dcu_complete_state ; 
 int qcu_complete_state ; 
 int qcu_fetch_state ; 
 int qcu_stitch_state ; 

__attribute__((used)) static HAL_BOOL
ar5416CompareDbgHang(struct ath_hal *ah, const mac_dbg_regs_t *regs,
    const hal_mac_hang_check_t *check)
{
	int found_states;

	found_states = 0;
	if (check->states & dcu_chain_state) {
		int i;

		for (i = 0; i < 6; i++) {
			if (((regs->dma_dbg_4 >> (5*i)) & 0x1f) ==
			    check->dcu_chain_state)
				found_states |= dcu_chain_state;
		}
		for (i = 0; i < 4; i++) {
			if (((regs->dma_dbg_5 >> (5*i)) & 0x1f) ==
			    check->dcu_chain_state)
				found_states |= dcu_chain_state;
		}
	}
	if (check->states & dcu_complete_state) { 
		if ((regs->dma_dbg_6 & 0x3) == check->dcu_complete_state)
			found_states |= dcu_complete_state;
	}
	if (check->states & qcu_stitch_state) { 
		if (((regs->dma_dbg_3 >> 18) & 0xf) == check->qcu_stitch_state)
			found_states |= qcu_stitch_state;
	}
	if (check->states & qcu_fetch_state) { 
		if (((regs->dma_dbg_3 >> 22) & 0xf) == check->qcu_fetch_state)
			found_states |= qcu_fetch_state;
	}
	if (check->states & qcu_complete_state) { 
		if (((regs->dma_dbg_3 >> 26) & 0x7) == check->qcu_complete_state)
			found_states |= qcu_complete_state;
	}
	return (found_states == check->states);
}