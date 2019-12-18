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
struct ath_hal {int dummy; } ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AH_FALSE ; 
 int /*<<< orphan*/  AH_TRUE ; 
 int /*<<< orphan*/  AR_PHY_65NM_CH0_TXRF3 ; 
 int /*<<< orphan*/  AR_PHY_65NM_CH0_TXRF3_CAPDIV2G ; 
 int /*<<< orphan*/  AR_PHY_PAPRD_TRAINER_CNTL3 ; 
 int /*<<< orphan*/  AR_PHY_PAPRD_TRAINER_CNTL3_CF_PAPRD_QUICK_DROP ; 
 int /*<<< orphan*/  AR_PHY_PAPRD_TRAINER_CNTL3_POSEIDON ; 
 scalar_t__ AR_SREV_HORNET (struct ath_hal*) ; 
 scalar_t__ AR_SREV_POSEIDON (struct ath_hal*) ; 
 int NUM_BIN ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int OS_REG_READ_FIELD_ALT (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_RMW_FIELD (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OS_REG_RMW_FIELD_ALT (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static HAL_BOOL ar9300_paprd_retrain_pain(struct ath_hal * ah, int * pa_in)
{
    int count = 0, i;
    int capdiv_offset = 0, quick_drop_offset;
    int capdiv2g, quick_drop;

    capdiv2g = (OS_REG_READ(ah, AR_PHY_65NM_CH0_TXRF3) >> 1) & 0xF;
    if (!AR_SREV_POSEIDON(ah)) {
        quick_drop = 
            OS_REG_READ_FIELD_ALT(ah, AR_PHY_PAPRD_TRAINER_CNTL3,
                AR_PHY_PAPRD_TRAINER_CNTL3_CF_PAPRD_QUICK_DROP);
    } else {
        quick_drop = 
            OS_REG_READ_FIELD_ALT(ah, AR_PHY_PAPRD_TRAINER_CNTL3_POSEIDON,
                AR_PHY_PAPRD_TRAINER_CNTL3_CF_PAPRD_QUICK_DROP);
    }

    if ( quick_drop != 0 ) {
        quick_drop -= 0x40; 
    }
    for (i = 0; i < (NUM_BIN + 1); i++) {
        if (pa_in[i] == 1400) {
            count++;
        }            
    }

    if (AR_SREV_POSEIDON(ah)) {
        if ((pa_in[23] < 800) || (pa_in[23] == 1400)) {
            if (pa_in[23] < 800) {
                capdiv_offset = (int)((1000 - pa_in[23] + 75) / 150);
                capdiv2g = capdiv2g + capdiv_offset;
                if (capdiv2g > 7) {
                    capdiv2g = 7;
                    if (pa_in[23] < 600) {
                        quick_drop = quick_drop + 1;
                        if (quick_drop > 0) {
                            quick_drop = 0;
                        }
                    }
                }
                
                OS_REG_RMW_FIELD(ah, 
                    AR_PHY_65NM_CH0_TXRF3, 
    			    AR_PHY_65NM_CH0_TXRF3_CAPDIV2G, 
    			    capdiv2g);

                OS_REG_RMW_FIELD_ALT(ah, 
                    AR_PHY_PAPRD_TRAINER_CNTL3_POSEIDON, 
                    AR_PHY_PAPRD_TRAINER_CNTL3_CF_PAPRD_QUICK_DROP, 
                    quick_drop);
                
                return AH_TRUE;
            } /* end of if (pa_in[23] < 800) */
            else if (pa_in[23] == 1400) {
                quick_drop_offset = (int)(count / 3);
                if (quick_drop_offset > 2) {
                    quick_drop_offset = 2;
                }
                quick_drop = quick_drop + quick_drop_offset;
                capdiv2g = capdiv2g + (int)(quick_drop_offset / 2); 
                if (capdiv2g > 7) {
                    capdiv2g = 7;
                }
                if (quick_drop > 0) {
                    quick_drop = 0;
                    capdiv2g = capdiv2g - (int)(quick_drop_offset / 1);
    				if (capdiv2g < 0) {
                        capdiv2g = 0;
    				}
                }
                OS_REG_RMW_FIELD(ah, 
                        AR_PHY_65NM_CH0_TXRF3, 
    			        AR_PHY_65NM_CH0_TXRF3_CAPDIV2G, 
    			        capdiv2g);

                OS_REG_RMW_FIELD_ALT(ah, 
                        AR_PHY_PAPRD_TRAINER_CNTL3_POSEIDON, 
        			    AR_PHY_PAPRD_TRAINER_CNTL3_CF_PAPRD_QUICK_DROP, 
                        quick_drop);
                
                return AH_TRUE;
                /* sleep(1); */            
            } /* end of if (pa_in[23] == 1400)*/
        } /* end of if ((pa_in[23] < 800) || (pa_in[23] == 1400)) */
    }else if (AR_SREV_HORNET(ah)) {
        if ((pa_in[23] < 1000) || (pa_in[23] == 1400)) {
            if (pa_in[23] < 1000) {
                capdiv_offset = ((1000 - pa_in[23]) / 100);   
                capdiv2g = capdiv2g + capdiv_offset;
                if (capdiv_offset > 3) {
                    quick_drop_offset = 1;
                    quick_drop = quick_drop - quick_drop_offset;
                    capdiv2g = capdiv2g + 1;
                    if (capdiv2g > 6) {
                        capdiv2g = 6;
                    }
                    if (quick_drop < -4) {
                        quick_drop = -4;
                    }
                    OS_REG_RMW_FIELD(ah, 
                        AR_PHY_65NM_CH0_TXRF3, 
                        AR_PHY_65NM_CH0_TXRF3_CAPDIV2G, 
                        capdiv2g);
                    OS_REG_RMW_FIELD_ALT(ah, 
                        AR_PHY_PAPRD_TRAINER_CNTL3, 
                        AR_PHY_PAPRD_TRAINER_CNTL3_CF_PAPRD_QUICK_DROP, 
                        quick_drop);
                    return AH_TRUE;
                } else {
                    capdiv2g = capdiv2g + capdiv_offset;
                    if (capdiv2g > 6) {
                        capdiv2g = 6;
                    }
                    if (quick_drop < -4) {
                        quick_drop = -4;
                    }
                    OS_REG_RMW_FIELD(ah, 
                        AR_PHY_65NM_CH0_TXRF3, 
                        AR_PHY_65NM_CH0_TXRF3_CAPDIV2G, 
                        capdiv2g);
                    OS_REG_RMW_FIELD_ALT(ah, 
                        AR_PHY_PAPRD_TRAINER_CNTL3, 
                        AR_PHY_PAPRD_TRAINER_CNTL3_CF_PAPRD_QUICK_DROP, 
                        quick_drop);
                    return AH_TRUE;
                }
            } /* end of if (PA_in[23] < 1000) */
            else if (pa_in[23] == 1400) {
                if (count > 3) {
                    quick_drop_offset = 1;
                    quick_drop = quick_drop + quick_drop_offset;
                    capdiv2g = capdiv2g - (count / 4);  
                    if (capdiv2g < 0) {
                        capdiv2g = 0;
                    }
                    if (quick_drop > -2) {
                        quick_drop = -2;
                    }
                    OS_REG_RMW_FIELD(ah, AR_PHY_65NM_CH0_TXRF3, 
                        AR_PHY_65NM_CH0_TXRF3_CAPDIV2G, 
                        capdiv2g);
                    OS_REG_RMW_FIELD_ALT(ah, AR_PHY_PAPRD_TRAINER_CNTL3, 
                        AR_PHY_PAPRD_TRAINER_CNTL3_CF_PAPRD_QUICK_DROP,
                        quick_drop);
                    return AH_TRUE;
                } else {
                    capdiv2g = capdiv2g - 1;  
                    if (capdiv2g < 0) {
                        capdiv2g = 0;
                    }
                    OS_REG_RMW_FIELD(ah, AR_PHY_65NM_CH0_TXRF3, 
                        AR_PHY_65NM_CH0_TXRF3_CAPDIV2G, 
                        capdiv2g);
                    OS_REG_RMW_FIELD_ALT(ah, AR_PHY_PAPRD_TRAINER_CNTL3, 
                        AR_PHY_PAPRD_TRAINER_CNTL3_CF_PAPRD_QUICK_DROP, 
                        quick_drop);
                    return AH_TRUE; 
                }
            } /* end of if (PA_in[23] == 1400)*/
        } /* end of if ((PA_in[23] < 1000) || (PA_in[23] == 1400)) */
    }

    return AH_FALSE;
}