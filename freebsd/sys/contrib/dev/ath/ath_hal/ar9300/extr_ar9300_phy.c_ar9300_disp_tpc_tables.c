#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct ieee80211_channel {int dummy; } ;
struct ath_hal_9300 {int** txpower; int** txpower_stbc; int /*<<< orphan*/  ah_tx_chainmask; } ;
struct TYPE_6__ {int /*<<< orphan*/  ath_hal_desc_tpc; } ;
struct ath_hal {TYPE_1__ ah_config; } ;
typedef  int int16_t ;
struct TYPE_9__ {struct ieee80211_channel* ah_curchan; } ;
struct TYPE_8__ {int rateCount; TYPE_2__* info; } ;
struct TYPE_7__ {scalar_t__ rateCode; int /*<<< orphan*/  rateKbps; } ;
typedef  TYPE_3__ HAL_RATE_TABLE ;

/* Variables and functions */
 struct ath_hal_9300* AH9300 (struct ath_hal*) ; 
 TYPE_5__* AH_PRIVATE (struct ath_hal*) ; 
 scalar_t__ AH_TRUE ; 
 int AR9300_MAX_CHAINS ; 
 scalar_t__ AR9300_MCS0_RATE_CODE ; 
 scalar_t__ AR9300_MCS23_RATE_CODE ; 
 int /*<<< orphan*/  HALASSERT (int /*<<< orphan*/ ) ; 
 int ar9300_get_ntxchains (int /*<<< orphan*/ ) ; 
 TYPE_3__* ar9300_get_rate_table (struct ath_hal*,int /*<<< orphan*/ ) ; 
 scalar_t__ ar9300_invalid_stbc_cfg (int,scalar_t__) ; 
 int /*<<< orphan*/  ath_hal_get_curmode (struct ath_hal*,struct ieee80211_channel const*) ; 
 int /*<<< orphan*/  ath_hal_printf (struct ath_hal*,char*,...) ; 

void ar9300_disp_tpc_tables(struct ath_hal *ah)
{
    struct ath_hal_9300 *ahp = AH9300(ah);
    const struct ieee80211_channel *chan = AH_PRIVATE(ah)->ah_curchan;
    u_int mode = ath_hal_get_curmode(ah, chan);
    const HAL_RATE_TABLE *rt;
    int i, j;

    /* Check whether TPC is enabled */
    if (!ah->ah_config.ath_hal_desc_tpc) {
        ath_hal_printf(ah, "\n TPC Register method in use\n");
        return;
    }
    
    rt = ar9300_get_rate_table(ah, mode);
    HALASSERT(rt != NULL);

    ath_hal_printf(ah, "\n===TARGET POWER TABLE===\n");
    for (j = 0 ; j < ar9300_get_ntxchains(ahp->ah_tx_chainmask) ; j++ ) {
        for (i = 0; i < rt->rateCount; i++) {
            int16_t txpower[AR9300_MAX_CHAINS]; 
            txpower[j] = ahp->txpower[i][j];
            ath_hal_printf(ah, " Index[%2d] Rate[0x%02x] %6d kbps "
                       "Power (%d Chain) [%2d.%1d dBm]\n",
                       i, rt->info[i].rateCode, rt->info[i].rateKbps,
                       j + 1, txpower[j] / 2, txpower[j]%2 * 5);
        }
    }
    ath_hal_printf(ah, "\n");

    ath_hal_printf(ah, "\n\n===TARGET POWER TABLE with STBC===\n");
    for ( j = 0 ; j < ar9300_get_ntxchains(ahp->ah_tx_chainmask) ; j++ ) {
        for (i = 0; i < rt->rateCount; i++) {
            int16_t txpower[AR9300_MAX_CHAINS]; 
            txpower[j] = ahp->txpower_stbc[i][j];

            /* Do not display invalid configurations */
            if ((rt->info[i].rateCode < AR9300_MCS0_RATE_CODE) ||
                (rt->info[i].rateCode > AR9300_MCS23_RATE_CODE) ||
                ar9300_invalid_stbc_cfg(j, rt->info[i].rateCode) == AH_TRUE) {
                continue;
            }

            ath_hal_printf(ah, " Index[%2d] Rate[0x%02x] %6d kbps "
                       "Power (%d Chain) [%2d.%1d dBm]\n",
                       i, rt->info[i].rateCode , rt->info[i].rateKbps,
                       j + 1, txpower[j] / 2, txpower[j]%2 * 5);
        }
    }
    ath_hal_printf(ah, "\n");
}