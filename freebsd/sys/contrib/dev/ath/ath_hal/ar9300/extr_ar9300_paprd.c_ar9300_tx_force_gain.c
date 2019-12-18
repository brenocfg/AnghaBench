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
struct TYPE_2__ {int* paprd_gain_table_entries; } ;

/* Variables and functions */
 TYPE_1__* AH9300 (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_PHY_TPC_1 ; 
 int /*<<< orphan*/  AR_PHY_TPC_1_FORCED_DAC_GAIN ; 
 int /*<<< orphan*/  AR_PHY_TPC_1_FORCE_DAC_GAIN ; 
 int /*<<< orphan*/  AR_PHY_TX_FORCED_GAIN ; 
 int /*<<< orphan*/  AR_PHY_TX_FORCED_GAIN_FORCED_ENABLE_PAL ; 
 int /*<<< orphan*/  AR_PHY_TX_FORCED_GAIN_FORCED_PADRVGNA ; 
 int /*<<< orphan*/  AR_PHY_TX_FORCED_GAIN_FORCED_PADRVGNB ; 
 int /*<<< orphan*/  AR_PHY_TX_FORCED_GAIN_FORCED_PADRVGNC ; 
 int /*<<< orphan*/  AR_PHY_TX_FORCED_GAIN_FORCED_PADRVGND ; 
 int /*<<< orphan*/  AR_PHY_TX_FORCED_GAIN_FORCED_TXBB1DBGAIN ; 
 int /*<<< orphan*/  AR_PHY_TX_FORCED_GAIN_FORCED_TXBB6DBGAIN ; 
 int /*<<< orphan*/  AR_PHY_TX_FORCED_GAIN_FORCED_TXMXRGAIN ; 
 int /*<<< orphan*/  AR_PHY_TX_FORCED_GAIN_FORCE_TX_GAIN ; 
 int /*<<< orphan*/  OS_REG_RMW_FIELD_ALT (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ar9300_tx_force_gain(struct ath_hal *ah, unsigned int gain_index)
{
    int selected_gain_entry, txbb1dbgain, txbb6dbgain, txmxrgain;
    int padrvgn_a, padrvgn_b, padrvgn_c, padrvgn_d;
    u_int32_t *gain_table_entries = AH9300(ah)->paprd_gain_table_entries;

    /*u_int32_t *gain_vs_table_index = ah->paprd_gain_table_index;*/
    selected_gain_entry = gain_table_entries[gain_index];
    txbb1dbgain = selected_gain_entry & 0x7;
    txbb6dbgain = (selected_gain_entry >> 3) & 0x3;
    txmxrgain = (selected_gain_entry >> 5) & 0xf;
    padrvgn_a = (selected_gain_entry >> 9) & 0xf;
    padrvgn_b = (selected_gain_entry >> 13) & 0xf;
    padrvgn_c = (selected_gain_entry >> 17) & 0xf;
    padrvgn_d = (selected_gain_entry >> 21) & 0x3;

    OS_REG_RMW_FIELD_ALT(ah, AR_PHY_TX_FORCED_GAIN,
        AR_PHY_TX_FORCED_GAIN_FORCED_TXBB1DBGAIN, txbb1dbgain);
    OS_REG_RMW_FIELD_ALT(ah, AR_PHY_TX_FORCED_GAIN,
        AR_PHY_TX_FORCED_GAIN_FORCED_TXBB6DBGAIN, txbb6dbgain);
    OS_REG_RMW_FIELD_ALT(ah, AR_PHY_TX_FORCED_GAIN,
        AR_PHY_TX_FORCED_GAIN_FORCED_TXMXRGAIN, txmxrgain);
    OS_REG_RMW_FIELD_ALT(ah, AR_PHY_TX_FORCED_GAIN,
        AR_PHY_TX_FORCED_GAIN_FORCED_PADRVGNA, padrvgn_a);
    OS_REG_RMW_FIELD_ALT(ah, AR_PHY_TX_FORCED_GAIN,
        AR_PHY_TX_FORCED_GAIN_FORCED_PADRVGNB, padrvgn_b);
    OS_REG_RMW_FIELD_ALT(ah, AR_PHY_TX_FORCED_GAIN,
        AR_PHY_TX_FORCED_GAIN_FORCED_PADRVGNC, padrvgn_c);
    OS_REG_RMW_FIELD_ALT(ah, AR_PHY_TX_FORCED_GAIN,
        AR_PHY_TX_FORCED_GAIN_FORCED_PADRVGND, padrvgn_d);
    OS_REG_RMW_FIELD_ALT(ah, AR_PHY_TX_FORCED_GAIN,
        AR_PHY_TX_FORCED_GAIN_FORCED_ENABLE_PAL, 0);
    OS_REG_RMW_FIELD_ALT(ah, AR_PHY_TX_FORCED_GAIN,
        AR_PHY_TX_FORCED_GAIN_FORCE_TX_GAIN, 0);

    OS_REG_RMW_FIELD_ALT(ah, AR_PHY_TPC_1, AR_PHY_TPC_1_FORCED_DAC_GAIN, 0);
    OS_REG_RMW_FIELD_ALT(ah, AR_PHY_TPC_1, AR_PHY_TPC_1_FORCE_DAC_GAIN, 0);
}