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
typedef  unsigned long u_int8_t ;
struct ath_hal {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_PHY_TPC_7 ; 
 int /*<<< orphan*/  AR_PHY_TPC_7_TX_GAIN_TABLE_MAX ; 
 unsigned long OS_REG_READ_FIELD (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int8_t ar9300_eeprom_get_tx_gain_table_number_max(struct ath_hal *ah)
{
    unsigned long tx_gain_table_max;
    tx_gain_table_max = OS_REG_READ_FIELD(ah,
        AR_PHY_TPC_7, AR_PHY_TPC_7_TX_GAIN_TABLE_MAX);
    return tx_gain_table_max;
}