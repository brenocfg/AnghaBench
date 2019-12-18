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

/* Variables and functions */
 int /*<<< orphan*/  AR_PHY_CL_TAB_0 ; 
 int /*<<< orphan*/  AR_PHY_CL_TAB_0_CL_GAIN_MOD ; 
 int /*<<< orphan*/  AR_PHY_CL_TAB_1 ; 
 int /*<<< orphan*/  AR_PHY_CL_TAB_1_CL_GAIN_MOD ; 
 int /*<<< orphan*/  AR_PHY_CL_TAB_2 ; 
 int /*<<< orphan*/  AR_PHY_CL_TAB_2_CL_GAIN_MOD ; 
 int /*<<< orphan*/  AR_PHY_PAPRD_TRAINER_STAT1 ; 
 int /*<<< orphan*/  AR_PHY_PAPRD_TRAINER_STAT1_PAPRD_TRAIN_DONE ; 
 int /*<<< orphan*/  AR_PHY_PAPRD_TRAINER_STAT1_POSEIDON ; 
 int /*<<< orphan*/  AR_PHY_THERM_ADC_4 ; 
 int /*<<< orphan*/  AR_PHY_THERM_ADC_4_LATEST_THERM_VALUE ; 
 int /*<<< orphan*/  AR_PHY_THERM_ADC_4_LATEST_VOLT_VALUE ; 
 int /*<<< orphan*/  AR_PHY_TPC_11_B0 ; 
 int /*<<< orphan*/  AR_PHY_TPC_11_B0_OLPC_GAIN_DELTA_0 ; 
 int /*<<< orphan*/  AR_PHY_TPC_11_B1 ; 
 int /*<<< orphan*/  AR_PHY_TPC_11_B1_OLPC_GAIN_DELTA_1 ; 
 int /*<<< orphan*/  AR_PHY_TPC_11_B2 ; 
 int /*<<< orphan*/  AR_PHY_TPC_11_B2_OLPC_GAIN_DELTA_2 ; 
 int /*<<< orphan*/  AR_PHY_TPC_12 ; 
 int /*<<< orphan*/  AR_PHY_TPC_12_DESIRED_SCALE_HT40_5 ; 
 int /*<<< orphan*/  AR_PHY_TPC_18 ; 
 int /*<<< orphan*/  AR_PHY_TPC_18_ALT_THERM_CAL_VALUE ; 
 int /*<<< orphan*/  AR_PHY_TPC_18_ALT_VOLT_CAL_VALUE ; 
 int /*<<< orphan*/  AR_PHY_TPC_19 ; 
 int /*<<< orphan*/  AR_PHY_TPC_19_ALPHA_THERM ; 
 int /*<<< orphan*/  AR_PHY_TPC_19_ALT_ALPHA_VOLT ; 
 scalar_t__ AR_SREV_POSEIDON (struct ath_hal*) ; 
 int OS_REG_READ_FIELD (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int OS_REG_READ_FIELD_ALT (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_RMW_FIELD_ALT (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_hal_printf (struct ath_hal*,char*,int,int,int,int,int,int,int) ; 

__attribute__((used)) static unsigned int ar9300_get_desired_gain_for_chain(struct ath_hal *ah,
    int chain_num, int target_power)
{
    int olpc_gain_delta = 0;
    int alpha_therm = 0, alpha_volt = 0;
    int therm_cal_value = 0, volt_cal_value = 0;
    int latest_therm_value = 0, latest_volt_value = 0, olpc_gain_delta_tmp = 0;
    int thermal_gain_corr = 0, voltage_gain_corr = 0, desired_scale = 0;
    int desired_gain = 0;
    int cl_gain_mod = 0;

    /* Clear the training done bit */
    if (AR_SREV_POSEIDON(ah)) {
        OS_REG_RMW_FIELD_ALT(ah, AR_PHY_PAPRD_TRAINER_STAT1_POSEIDON,
            AR_PHY_PAPRD_TRAINER_STAT1_PAPRD_TRAIN_DONE, 0);
    } else {
        OS_REG_RMW_FIELD_ALT(ah, AR_PHY_PAPRD_TRAINER_STAT1,
            AR_PHY_PAPRD_TRAINER_STAT1_PAPRD_TRAIN_DONE, 0);
    }
    /*field_read("BB_tpc_12.desired_scale_ht40_5", &desired_scale);*/
    desired_scale =
        OS_REG_READ_FIELD_ALT(ah, AR_PHY_TPC_12,
        AR_PHY_TPC_12_DESIRED_SCALE_HT40_5);
    /*field_read("BB_tpc_19.alpha_therm", &alpha_therm);*/
    alpha_therm =
        OS_REG_READ_FIELD(ah, AR_PHY_TPC_19, AR_PHY_TPC_19_ALPHA_THERM);
    /*field_read("BB_tpc_19.alpha_volt", &alpha_volt);*/
    alpha_volt =
        OS_REG_READ_FIELD_ALT(ah, AR_PHY_TPC_19, AR_PHY_TPC_19_ALT_ALPHA_VOLT);

    /*field_read("BB_tpc_18.therm_cal_value", &therm_cal_value);*/
    therm_cal_value =
        OS_REG_READ_FIELD_ALT(ah, AR_PHY_TPC_18,
        AR_PHY_TPC_18_ALT_THERM_CAL_VALUE);
    /*field_read("BB_tpc_18.volt_cal_value", &volt_cal_value);*/
    volt_cal_value =
        OS_REG_READ_FIELD_ALT(ah, AR_PHY_TPC_18,
        AR_PHY_TPC_18_ALT_VOLT_CAL_VALUE);

    /*field_read("BB_therm_adc_4.latest_therm_value", &latest_therm_value);*/
    latest_therm_value =
        OS_REG_READ_FIELD_ALT(ah, AR_PHY_THERM_ADC_4,
        AR_PHY_THERM_ADC_4_LATEST_THERM_VALUE);
    /*field_read("BB_therm_adc_4.latest_volt_value", &latest_volt_value);*/
    latest_volt_value =
        OS_REG_READ_FIELD_ALT(ah, AR_PHY_THERM_ADC_4,
        AR_PHY_THERM_ADC_4_LATEST_VOLT_VALUE);

    /*
     * sprintf(
     *     field_name, "%s%d%s%d\0", "BB_tpc_11_b", 
     *     chain_num, ".olpc_gain_delta_", chain_num);
     */
    /*field_read(field_name, &olpc_gain_delta_tmp);*/


    if (chain_num == 0) {
        olpc_gain_delta_tmp =
            OS_REG_READ_FIELD_ALT(ah, AR_PHY_TPC_11_B0,
            AR_PHY_TPC_11_B0_OLPC_GAIN_DELTA_0);
        cl_gain_mod = OS_REG_READ_FIELD_ALT(ah, AR_PHY_CL_TAB_0, 
            AR_PHY_CL_TAB_0_CL_GAIN_MOD);
    } else if (chain_num == 1) {
        if (!AR_SREV_POSEIDON(ah)) {
            olpc_gain_delta_tmp =
                OS_REG_READ_FIELD_ALT(ah, AR_PHY_TPC_11_B1,
                AR_PHY_TPC_11_B1_OLPC_GAIN_DELTA_1);
            cl_gain_mod = OS_REG_READ_FIELD_ALT(ah, AR_PHY_CL_TAB_1, 
                AR_PHY_CL_TAB_1_CL_GAIN_MOD);
        }
    } else if (chain_num == 2) {
        if (!AR_SREV_POSEIDON(ah)) {
            olpc_gain_delta_tmp =
                OS_REG_READ_FIELD_ALT(ah, AR_PHY_TPC_11_B2,
                AR_PHY_TPC_11_B2_OLPC_GAIN_DELTA_2);
            cl_gain_mod = OS_REG_READ_FIELD_ALT(ah, AR_PHY_CL_TAB_2, 
                AR_PHY_CL_TAB_2_CL_GAIN_MOD);
        }
    } else {
        /* invalid chain_num */
    }

    if (olpc_gain_delta_tmp < 128) {
        olpc_gain_delta = olpc_gain_delta_tmp;
    } else {
        olpc_gain_delta = olpc_gain_delta_tmp - 256;
    }

    thermal_gain_corr =
        (int) (alpha_therm * (latest_therm_value - therm_cal_value) +
        128) >> 8;
    voltage_gain_corr =
        (int) (alpha_volt * (latest_volt_value - volt_cal_value) + 64) >> 7;
    desired_gain =
        target_power - olpc_gain_delta - thermal_gain_corr -
        voltage_gain_corr + desired_scale + cl_gain_mod;
    /*
     * printf(
     *     "olpc_gain_delta %d, desired_gain %d\n", 
     *     olpc_gain_delta, desired_gain);
     */
#if 0
    ath_hal_printf(ah,
        "+++ target_power %d olpc_gain_delta %d, cl_gain_mod %d,"
        "thermal_gain_corr %d  voltage_gain_corr %d desired_scale %d"
        "desired_gain %d\n",
        target_power, olpc_gain_delta, cl_gain_mod, thermal_gain_corr,
        voltage_gain_corr,
        desired_scale, desired_gain);
#endif
    return (unsigned int) desired_gain;
}