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
typedef  int u_int8_t ;
typedef  int u_int32_t ;
struct ieee80211_channel {int dummy; } ;
struct ath_hal {int dummy; } ;

/* Variables and functions */
 size_t ALL_TARGET_LEGACY_1L_5L ; 
 size_t ALL_TARGET_LEGACY_6_24 ; 
 int /*<<< orphan*/  AR_TPC ; 
 int /*<<< orphan*/  AR_TPC_ACK ; 
 int /*<<< orphan*/  AR_TPC_CHIRP ; 
 int /*<<< orphan*/  AR_TPC_CTS ; 
 int /*<<< orphan*/  AR_TPC_RPT ; 
 scalar_t__ IEEE80211_IS_CHAN_2GHZ (struct ieee80211_channel const*) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 
 int SM (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ar9300_selfgen_tpc_reg_write(struct ath_hal *ah, const struct ieee80211_channel *chan,
                             u_int8_t *p_pwr_array) 
{
    u_int32_t tpc_reg_val;

    /* Set the target power values for self generated frames (ACK,RTS/CTS) to
     * be within limits. This is just a safety measure.With per packet TPC mode
     * enabled the target power value used with self generated frames will be
     * MIN( TPC reg, BB_powertx_rate register)
     */
    
    if (IEEE80211_IS_CHAN_2GHZ(chan)) {
        tpc_reg_val = (SM(p_pwr_array[ALL_TARGET_LEGACY_1L_5L], AR_TPC_ACK) |
                       SM(p_pwr_array[ALL_TARGET_LEGACY_1L_5L], AR_TPC_CTS) |
                       SM(0x3f, AR_TPC_CHIRP) |
                       SM(0x3f, AR_TPC_RPT));
    } else {
        tpc_reg_val = (SM(p_pwr_array[ALL_TARGET_LEGACY_6_24], AR_TPC_ACK) |
                       SM(p_pwr_array[ALL_TARGET_LEGACY_6_24], AR_TPC_CTS) |
                       SM(0x3f, AR_TPC_CHIRP) |
                       SM(0x3f, AR_TPC_RPT));
    }
    OS_REG_WRITE(ah, AR_TPC, tpc_reg_val);
}