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
typedef  int u_int32_t ;
struct ath_hal {int dummy; } ;
struct TYPE_2__ {int* paprd_gain_table_entries; int* paprd_gain_table_index; } ;

/* Variables and functions */
 TYPE_1__* AH9300 (struct ath_hal*) ; 
 int AR_PHY_TXGAIN_TAB (int) ; 
 int OS_REG_READ (struct ath_hal*,int) ; 

__attribute__((used)) static void ar9300_gain_table_entries(struct ath_hal *ah)
{
    int i;
    u_int32_t reg;
    u_int32_t *gain_table_entries = AH9300(ah)->paprd_gain_table_entries;
    u_int32_t *gain_vs_table_index = AH9300(ah)->paprd_gain_table_index;

    reg = AR_PHY_TXGAIN_TAB(1);

    for (i = 0; i < 32; i++) {
        gain_table_entries[i] = OS_REG_READ(ah, reg);
        gain_vs_table_index[i] = (gain_table_entries[i] >> 24) & 0xff;
        /*
         * ath_hal_printf(
         *     ah, "+++reg 0x%08x gain_table_entries[%d] = 0x%08x \n", 
         *     reg, i, gain_table_entries[i]);
         */
        reg = reg + 4;
    }
}