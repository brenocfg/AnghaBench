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
typedef  int u_int8_t ;
struct ath_hal {int dummy; } ;
struct TYPE_5__ {int dma_dbg_4; int dma_dbg_5; int dma_dbg_6; } ;
typedef  TYPE_1__ mac_dbg_regs_t ;
typedef  int hal_mac_hangs_t ;
struct TYPE_6__ {int dcu_chain_state; int dcu_complete_state; } ;
typedef  TYPE_2__ hal_mac_hang_check_t ;

/* Variables and functions */
 int dcu_chain_state ; 
 int dcu_complete_state ; 

__attribute__((used)) static hal_mac_hangs_t
ar9300_compare_dbg_hang(struct ath_hal *ah, mac_dbg_regs_t mac_dbg,
  hal_mac_hang_check_t hang_check, hal_mac_hangs_t hangs, u_int8_t *dcu_chain)
{
    int i = 0;
    hal_mac_hangs_t found_hangs = 0;

    if (hangs & dcu_chain_state) {
        for (i = 0; i < 6; i++) {
            if (((mac_dbg.dma_dbg_4 >> (5 * i)) & 0x1f) ==
                 hang_check.dcu_chain_state)
            {
                found_hangs |= dcu_chain_state;
                *dcu_chain = i;
            }
        }
        for (i = 0; i < 4; i++) {
            if (((mac_dbg.dma_dbg_5 >> (5 * i)) & 0x1f) ==
                  hang_check.dcu_chain_state)
            {
                found_hangs |= dcu_chain_state;
                *dcu_chain = i + 6;
            }
        }
    }

    if (hangs & dcu_complete_state) {
        if ((mac_dbg.dma_dbg_6 & 0x3) == hang_check.dcu_complete_state) {
            found_hangs |= dcu_complete_state;
        }
    }

    return found_hangs;

}