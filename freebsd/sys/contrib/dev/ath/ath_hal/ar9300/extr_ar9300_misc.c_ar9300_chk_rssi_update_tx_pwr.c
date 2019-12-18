#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int u_int32_t ;
typedef  int /*<<< orphan*/  target_power_val_t ;
struct ath_hal_9300 {scalar_t__ green_tx_status; int* ah_ob_db1; scalar_t__ ah_hw_green_tx_enable; scalar_t__* ah_db2; int /*<<< orphan*/  ah_default_tx_power; } ;
struct TYPE_3__ {scalar_t__ ath_hal_sta_update_tx_pwr_enable_S3; scalar_t__ ath_hal_sta_update_tx_pwr_enable_S2; scalar_t__ ath_hal_sta_update_tx_pwr_enable_S1; int /*<<< orphan*/  ath_hal_sta_update_tx_pwr_enable; } ;
struct ath_hal {TYPE_1__ ah_config; } ;
typedef  int int8_t ;
struct TYPE_4__ {scalar_t__ ah_opmode; } ;
typedef  scalar_t__ HAL_RSSI_TX_POWER ;

/* Variables and functions */
 struct ath_hal_9300* AH9300 (struct ath_hal*) ; 
 TYPE_2__* AH_PRIVATE (struct ath_hal*) ; 
 int AR9485_BBPWRTXRATE9_HW_GREEN_TX_MIDDLE_VALUE ; 
 int AR9485_BBPWRTXRATE9_HW_GREEN_TX_SHORT_VALUE ; 
 int AR9485_HW_GREEN_TX_THRES1_DB ; 
 int AR9485_HW_GREEN_TX_THRES2_DB ; 
 int /*<<< orphan*/  AR_PHY_65NM_CH0_TXRF2 ; 
 int AR_PHY_65NM_CH0_TXRF2_DB2G ; 
 int AR_PHY_65NM_CH0_TXRF2_OB2G_CCK ; 
 int AR_PHY_65NM_CH0_TXRF2_OB2G_PSK ; 
 int AR_PHY_65NM_CH0_TXRF2_OB2G_QAM ; 
 int /*<<< orphan*/  AR_PHY_BB_POWERTX_RATE9 ; 
 int /*<<< orphan*/  AR_PHY_TPC_11_B0 ; 
 int /*<<< orphan*/  AR_PHY_TPC_OLPC_GAIN_DELTA ; 
 int AR_PHY_TPC_OLPC_GAIN_DELTA_S ; 
 scalar_t__ AR_SREV_POSEIDON (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_TPC ; 
 int AR_TPC_ACK ; 
 int AR_TPC_CHIRP ; 
 int AR_TPC_CTS ; 
 int AR_TPC_RPT ; 
 scalar_t__ HAL_M_STA ; 
#define  HAL_RSSI_TX_POWER_LONG 130 
#define  HAL_RSSI_TX_POWER_MIDDLE 129 
 scalar_t__ HAL_RSSI_TX_POWER_NONE ; 
#define  HAL_RSSI_TX_POWER_SHORT 128 
 int /*<<< orphan*/  OS_MEMCPY (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OS_REG_RMW (struct ath_hal*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 
 size_t POSEIDON_STORED_REG_BB_PWRTX_RATE9 ; 
 size_t POSEIDON_STORED_REG_G2_OLPC_OFFSET ; 
 size_t POSEIDON_STORED_REG_OBDB ; 
 size_t POSEIDON_STORED_REG_TPC ; 
 int SM (int,int) ; 
 int WB225_BBPWRTXRATE9_SW_GREEN_TX_MIDDLE_VALUE ; 
 int WB225_BBPWRTXRATE9_SW_GREEN_TX_SHORT_VALUE ; 
 size_t WB225_OB_CALIBRATION_VALUE ; 
 size_t WB225_OB_GREEN_TX_LONG_VALUE ; 
 size_t WB225_OB_GREEN_TX_MIDDLE_VALUE ; 
 size_t WB225_OB_GREEN_TX_SHORT_VALUE ; 
 int WB225_SW_GREEN_TX_THRES1_DB ; 
 int WB225_SW_GREEN_TX_THRES2_DB ; 
 int ar9300_rate_size ; 
 int /*<<< orphan*/  ar9300_transmit_power_reg_write (struct ath_hal*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ar9485_hw_gtx_tp_distance_middle ; 
 int /*<<< orphan*/  ar9485_hw_gtx_tp_distance_short ; 
 int* wb225_gtx_olpc_cal_offset ; 
 int /*<<< orphan*/  wb225_sw_gtx_tp_distance_middle ; 
 int /*<<< orphan*/  wb225_sw_gtx_tp_distance_short ; 

void ar9300_chk_rssi_update_tx_pwr(struct ath_hal *ah, int rssi)
{
    struct ath_hal_9300 *ahp = AH9300(ah);
    u_int32_t           temp_obdb_reg_val = 0, temp_tcp_reg_val;
    u_int32_t           temp_powertx_rate9_reg_val;
    int8_t              olpc_power_offset = 0;
    int8_t              tmp_olpc_val = 0;
    HAL_RSSI_TX_POWER   old_greentx_status;
    u_int8_t            target_power_val_t[ar9300_rate_size];
    int8_t              tmp_rss1_thr1, tmp_rss1_thr2;

    if ((AH_PRIVATE(ah)->ah_opmode != HAL_M_STA) || 
        !ah->ah_config.ath_hal_sta_update_tx_pwr_enable) {
        return;
    }
    
    old_greentx_status = AH9300(ah)->green_tx_status;
    if (ahp->ah_hw_green_tx_enable) {
        tmp_rss1_thr1 = AR9485_HW_GREEN_TX_THRES1_DB;
        tmp_rss1_thr2 = AR9485_HW_GREEN_TX_THRES2_DB;
    } else {
        tmp_rss1_thr1 = WB225_SW_GREEN_TX_THRES1_DB;
        tmp_rss1_thr2 = WB225_SW_GREEN_TX_THRES2_DB;
    }
    
    if ((ah->ah_config.ath_hal_sta_update_tx_pwr_enable_S1) 
        && (rssi > tmp_rss1_thr1)) 
    {
        if (old_greentx_status != HAL_RSSI_TX_POWER_SHORT) {
            AH9300(ah)->green_tx_status = HAL_RSSI_TX_POWER_SHORT;
        }
    } else if (ah->ah_config.ath_hal_sta_update_tx_pwr_enable_S2 
        && (rssi > tmp_rss1_thr2)) 
    {
        if (old_greentx_status != HAL_RSSI_TX_POWER_MIDDLE) {
            AH9300(ah)->green_tx_status = HAL_RSSI_TX_POWER_MIDDLE;
        }
    } else if (ah->ah_config.ath_hal_sta_update_tx_pwr_enable_S3) {
        if (old_greentx_status != HAL_RSSI_TX_POWER_LONG) {
            AH9300(ah)->green_tx_status = HAL_RSSI_TX_POWER_LONG;
        }
    }

    /* If status is not change, don't do anything */
    if (old_greentx_status == AH9300(ah)->green_tx_status) {
        return;
    }
    
    /* for Poseidon which ath_hal_sta_update_tx_pwr_enable is enabled */
    if ((AH9300(ah)->green_tx_status != HAL_RSSI_TX_POWER_NONE) 
        && AR_SREV_POSEIDON(ah)) 
    {
        if (ahp->ah_hw_green_tx_enable) {
            switch (AH9300(ah)->green_tx_status) {
            case HAL_RSSI_TX_POWER_SHORT:
                /* 1. TxPower Config */
                OS_MEMCPY(target_power_val_t, ar9485_hw_gtx_tp_distance_short,
                    sizeof(target_power_val_t));
                /* 1.1 Store OLPC Delta Calibration Offset*/
                olpc_power_offset = 0;
                /* 2. Store OB/DB */
                /* 3. Store TPC settting */
                temp_tcp_reg_val = (SM(14, AR_TPC_ACK) |
                                    SM(14, AR_TPC_CTS) |
                                    SM(14, AR_TPC_CHIRP) |
                                    SM(14, AR_TPC_RPT));
                /* 4. Store BB_powertx_rate9 value */
                temp_powertx_rate9_reg_val = 
                    AR9485_BBPWRTXRATE9_HW_GREEN_TX_SHORT_VALUE;
                break;
            case HAL_RSSI_TX_POWER_MIDDLE:
                /* 1. TxPower Config */
                OS_MEMCPY(target_power_val_t, ar9485_hw_gtx_tp_distance_middle,
                    sizeof(target_power_val_t));
                /* 1.1 Store OLPC Delta Calibration Offset*/
                olpc_power_offset = 0;
                /* 2. Store OB/DB */
                /* 3. Store TPC settting */
                temp_tcp_reg_val = (SM(18, AR_TPC_ACK) |
                                    SM(18, AR_TPC_CTS) |
                                    SM(18, AR_TPC_CHIRP) |
                                    SM(18, AR_TPC_RPT));
                /* 4. Store BB_powertx_rate9 value */
                temp_powertx_rate9_reg_val = 
                    AR9485_BBPWRTXRATE9_HW_GREEN_TX_MIDDLE_VALUE;
                break;
            case HAL_RSSI_TX_POWER_LONG:
            default:
                /* 1. TxPower Config */
                OS_MEMCPY(target_power_val_t, ahp->ah_default_tx_power,
                    sizeof(target_power_val_t));
                /* 1.1 Store OLPC Delta Calibration Offset*/
                olpc_power_offset = 0;
                /* 2. Store OB/DB1/DB2 */
                /* 3. Store TPC settting */
                temp_tcp_reg_val = 
                    AH9300(ah)->ah_ob_db1[POSEIDON_STORED_REG_TPC];
                /* 4. Store BB_powertx_rate9 value */
                temp_powertx_rate9_reg_val = 
                  AH9300(ah)->ah_ob_db1[POSEIDON_STORED_REG_BB_PWRTX_RATE9];
                break;
            }
        } else {
            switch (AH9300(ah)->green_tx_status) {
            case HAL_RSSI_TX_POWER_SHORT:
                /* 1. TxPower Config */
                OS_MEMCPY(target_power_val_t, wb225_sw_gtx_tp_distance_short,
                    sizeof(target_power_val_t));
                /* 1.1 Store OLPC Delta Calibration Offset*/
                olpc_power_offset = 
                    wb225_gtx_olpc_cal_offset[WB225_OB_GREEN_TX_SHORT_VALUE] -
                    wb225_gtx_olpc_cal_offset[WB225_OB_CALIBRATION_VALUE];
                /* 2. Store OB/DB */
                temp_obdb_reg_val =
                    AH9300(ah)->ah_ob_db1[POSEIDON_STORED_REG_OBDB];
                temp_obdb_reg_val &= ~(AR_PHY_65NM_CH0_TXRF2_DB2G | 
                                       AR_PHY_65NM_CH0_TXRF2_OB2G_CCK |
                                       AR_PHY_65NM_CH0_TXRF2_OB2G_PSK |
                                       AR_PHY_65NM_CH0_TXRF2_OB2G_QAM);
                temp_obdb_reg_val |= (SM(5, AR_PHY_65NM_CH0_TXRF2_DB2G) |
                SM(WB225_OB_GREEN_TX_SHORT_VALUE,
                    AR_PHY_65NM_CH0_TXRF2_OB2G_CCK) |
                SM(WB225_OB_GREEN_TX_SHORT_VALUE,
                    AR_PHY_65NM_CH0_TXRF2_OB2G_PSK) |
                SM(WB225_OB_GREEN_TX_SHORT_VALUE,
                    AR_PHY_65NM_CH0_TXRF2_OB2G_QAM));
                /* 3. Store TPC settting */
                temp_tcp_reg_val = (SM(6, AR_TPC_ACK) |
                                    SM(6, AR_TPC_CTS) |
                                    SM(6, AR_TPC_CHIRP) |
                                    SM(6, AR_TPC_RPT));
                /* 4. Store BB_powertx_rate9 value */
                temp_powertx_rate9_reg_val = 
                    WB225_BBPWRTXRATE9_SW_GREEN_TX_SHORT_VALUE;
                break;
            case HAL_RSSI_TX_POWER_MIDDLE:
                /* 1. TxPower Config */
                OS_MEMCPY(target_power_val_t, wb225_sw_gtx_tp_distance_middle,
                    sizeof(target_power_val_t));
                /* 1.1 Store OLPC Delta Calibration Offset*/
                olpc_power_offset = 
                    wb225_gtx_olpc_cal_offset[WB225_OB_GREEN_TX_MIDDLE_VALUE] -
                    wb225_gtx_olpc_cal_offset[WB225_OB_CALIBRATION_VALUE];
                /* 2. Store OB/DB */
                temp_obdb_reg_val =
                    AH9300(ah)->ah_ob_db1[POSEIDON_STORED_REG_OBDB];
                temp_obdb_reg_val &= ~(AR_PHY_65NM_CH0_TXRF2_DB2G | 
                                       AR_PHY_65NM_CH0_TXRF2_OB2G_CCK |
                                       AR_PHY_65NM_CH0_TXRF2_OB2G_PSK |
                                       AR_PHY_65NM_CH0_TXRF2_OB2G_QAM);
                temp_obdb_reg_val |= (SM(5, AR_PHY_65NM_CH0_TXRF2_DB2G) |
                    SM(WB225_OB_GREEN_TX_MIDDLE_VALUE,
                        AR_PHY_65NM_CH0_TXRF2_OB2G_CCK) |
                    SM(WB225_OB_GREEN_TX_MIDDLE_VALUE,
                        AR_PHY_65NM_CH0_TXRF2_OB2G_PSK) |
                    SM(WB225_OB_GREEN_TX_MIDDLE_VALUE,
                        AR_PHY_65NM_CH0_TXRF2_OB2G_QAM));
                /* 3. Store TPC settting */
                temp_tcp_reg_val = (SM(14, AR_TPC_ACK) |
                                    SM(14, AR_TPC_CTS) |
                                    SM(14, AR_TPC_CHIRP) |
                                    SM(14, AR_TPC_RPT));
                /* 4. Store BB_powertx_rate9 value */
                temp_powertx_rate9_reg_val = 
                    WB225_BBPWRTXRATE9_SW_GREEN_TX_MIDDLE_VALUE;
                break;
            case HAL_RSSI_TX_POWER_LONG:
            default:
                /* 1. TxPower Config */
                OS_MEMCPY(target_power_val_t, ahp->ah_default_tx_power,
                    sizeof(target_power_val_t));
                /* 1.1 Store OLPC Delta Calibration Offset*/
                olpc_power_offset = 
                    wb225_gtx_olpc_cal_offset[WB225_OB_GREEN_TX_LONG_VALUE] -
                    wb225_gtx_olpc_cal_offset[WB225_OB_CALIBRATION_VALUE];
                /* 2. Store OB/DB1/DB2 */
                temp_obdb_reg_val =
                    AH9300(ah)->ah_ob_db1[POSEIDON_STORED_REG_OBDB];
                /* 3. Store TPC settting */
                temp_tcp_reg_val =
                    AH9300(ah)->ah_ob_db1[POSEIDON_STORED_REG_TPC];
                /* 4. Store BB_powertx_rate9 value */
                temp_powertx_rate9_reg_val = 
                  AH9300(ah)->ah_ob_db1[POSEIDON_STORED_REG_BB_PWRTX_RATE9];
                break;
            }
        }
        /* 1.1 Do OLPC Delta Calibration Offset */
        tmp_olpc_val = 
            (int8_t) AH9300(ah)->ah_db2[POSEIDON_STORED_REG_G2_OLPC_OFFSET];
        tmp_olpc_val += olpc_power_offset;
        OS_REG_RMW(ah, AR_PHY_TPC_11_B0, 
            (tmp_olpc_val << AR_PHY_TPC_OLPC_GAIN_DELTA_S), 
            AR_PHY_TPC_OLPC_GAIN_DELTA);
 
        /* 1.2 TxPower Config */
        ar9300_transmit_power_reg_write(ah, target_power_val_t);     
        /* 2. Config OB/DB */
        if (!ahp->ah_hw_green_tx_enable) {
            OS_REG_WRITE(ah, AR_PHY_65NM_CH0_TXRF2, temp_obdb_reg_val);
        }
        /* 3. config TPC settting */
        OS_REG_WRITE(ah, AR_TPC, temp_tcp_reg_val);
        /* 4. config BB_powertx_rate9 value */
        OS_REG_WRITE(ah, AR_PHY_BB_POWERTX_RATE9, temp_powertx_rate9_reg_val);
    }
}