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
typedef  scalar_t__ u_int32_t ;
struct ath_hal {int dummy; } ;

/* Variables and functions */
 scalar_t__ AH_FALSE ; 
 int /*<<< orphan*/  AR_PHY_CHAN_INFO_MEMORY ; 
 int /*<<< orphan*/  AR_PHY_CHAN_INFO_MEMORY_CHANINFOMEM_S2_READ ; 
 scalar_t__ AR_PHY_CHAN_INFO_TAB_0 ; 
 int /*<<< orphan*/  AR_PHY_PAPRD_TRAINER_STAT1 ; 
 int /*<<< orphan*/  AR_PHY_PAPRD_TRAINER_STAT1_PAPRD_TRAIN_DONE ; 
 int /*<<< orphan*/  AR_PHY_PAPRD_TRAINER_STAT1_POSEIDON ; 
 scalar_t__ AR_SREV_POSEIDON (struct ath_hal*) ; 
 scalar_t__ OS_REG_READ (struct ath_hal*,scalar_t__) ; 
 int /*<<< orphan*/  OS_REG_RMW_FIELD_ALT (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ar9300_paprd_debug_print (struct ath_hal*) ; 
 scalar_t__ create_pa_curve (scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*,int*) ; 

__attribute__((used)) static int ar9300_create_pa_curve(struct ath_hal *ah, u_int32_t * pa_table,
    u_int32_t * small_signal_gain, int * pa_in)
{
    int i;
    int status;
    /*char field_name[100];*/
    u_int32_t paprd_train_data_l[48], paprd_train_data_u[48];
    u_int32_t reg;

    ar9300_paprd_debug_print(ah);
    OS_REG_RMW_FIELD_ALT(ah, AR_PHY_CHAN_INFO_MEMORY,
        AR_PHY_CHAN_INFO_MEMORY_CHANINFOMEM_S2_READ, 0);
    reg = AR_PHY_CHAN_INFO_TAB_0;

    for (i = 0; i < 48; i++) {
        /*
         * sprintf(
         *     field_name, "%s%d%s\0", "BB_chan_info_chan_tab_b0[", 
         *     i, "].chaninfo_word");
         */
        /*field_read(field_name, &paprd_train_data_l[i]);*/
        paprd_train_data_l[i] = OS_REG_READ(ah, reg);
        reg = reg + 4;
    }

    OS_REG_RMW_FIELD_ALT(ah, AR_PHY_CHAN_INFO_MEMORY,
        AR_PHY_CHAN_INFO_MEMORY_CHANINFOMEM_S2_READ, 1);
    reg = AR_PHY_CHAN_INFO_TAB_0;

    for (i = 0; i < 48; i++) {
        /*
         * sprintf(
         *     field_name, "%s%d%s\0", "BB_chan_info_chan_tab_b0[", 
         *     i, "].chaninfo_word");
         */
        /*field_read(field_name, &paprd_train_data_u[i]);*/
        paprd_train_data_u[i] = OS_REG_READ(ah, reg);
        reg = reg + 4;
    }

    /*
     * for(i=0; i<48; i++)
     *     ath_hal_printf(
     *         ah, "%08x%08x\n", paprd_train_data_u[i], paprd_train_data_l[i]);
     */
    status = 0;
    if (create_pa_curve(
            paprd_train_data_l, paprd_train_data_u, 
            pa_table, small_signal_gain, pa_in) ==
            AH_FALSE)
    {
        status = -2;
    }
    /* Clear the training done bit */
    if (AR_SREV_POSEIDON(ah)) {
        OS_REG_RMW_FIELD_ALT(ah, AR_PHY_PAPRD_TRAINER_STAT1_POSEIDON,
            AR_PHY_PAPRD_TRAINER_STAT1_PAPRD_TRAIN_DONE, 0);
    } else {
        OS_REG_RMW_FIELD_ALT(ah, AR_PHY_PAPRD_TRAINER_STAT1,
            AR_PHY_PAPRD_TRAINER_STAT1_PAPRD_TRAIN_DONE, 0);
    }
    return status;
}