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
struct ath_hal_9300 {scalar_t__ ah_hw_green_tx_enable; } ;
struct ath_hal {int dummy; } ;

/* Variables and functions */
 struct ath_hal_9300* AH9300 (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_PHY_PAPRD_VALID_OBDB_0 ; 
 int /*<<< orphan*/  AR_PHY_PAPRD_VALID_OBDB_1 ; 
 int /*<<< orphan*/  AR_PHY_PAPRD_VALID_OBDB_2 ; 
 int /*<<< orphan*/  AR_PHY_PAPRD_VALID_OBDB_3 ; 
 int /*<<< orphan*/  AR_PHY_PAPRD_VALID_OBDB_4 ; 
 int /*<<< orphan*/  AR_PHY_PAPRD_VALID_OBDB_POSEIDON ; 
 scalar_t__ AR_SREV_POSEIDON (struct ath_hal*) ; 
 int /*<<< orphan*/  OS_REG_RMW_FIELD_ALT (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

void
ar9300_control_signals_for_green_tx_mode(struct ath_hal *ah)
{
    unsigned int valid_obdb_0_b0 = 0x2d; // 5,5 - dB[0:2],oB[5:3]  
    unsigned int valid_obdb_1_b0 = 0x25; // 4,5 - dB[0:2],oB[5:3]  
    unsigned int valid_obdb_2_b0 = 0x1d; // 3,5 - dB[0:2],oB[5:3] 
    unsigned int valid_obdb_3_b0 = 0x15; // 2,5 - dB[0:2],oB[5:3] 
    unsigned int valid_obdb_4_b0 = 0xd;  // 1,5 - dB[0:2],oB[5:3]
    struct ath_hal_9300 *ahp = AH9300(ah);

    if (AR_SREV_POSEIDON(ah) && ahp->ah_hw_green_tx_enable) {
        OS_REG_RMW_FIELD_ALT(ah, AR_PHY_PAPRD_VALID_OBDB_POSEIDON, 
                             AR_PHY_PAPRD_VALID_OBDB_0, valid_obdb_0_b0);
        OS_REG_RMW_FIELD_ALT(ah, AR_PHY_PAPRD_VALID_OBDB_POSEIDON, 
                             AR_PHY_PAPRD_VALID_OBDB_1, valid_obdb_1_b0);
        OS_REG_RMW_FIELD_ALT(ah, AR_PHY_PAPRD_VALID_OBDB_POSEIDON, 
                             AR_PHY_PAPRD_VALID_OBDB_2, valid_obdb_2_b0);
        OS_REG_RMW_FIELD_ALT(ah, AR_PHY_PAPRD_VALID_OBDB_POSEIDON, 
                             AR_PHY_PAPRD_VALID_OBDB_3, valid_obdb_3_b0);
        OS_REG_RMW_FIELD_ALT(ah, AR_PHY_PAPRD_VALID_OBDB_POSEIDON, 
                             AR_PHY_PAPRD_VALID_OBDB_4, valid_obdb_4_b0);
    }
}