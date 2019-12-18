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
struct hal_bb_panic_info {int status; scalar_t__ txf_pcnt; scalar_t__ rxf_pcnt; scalar_t__ rxc_pcnt; scalar_t__ cycles; void* phy_gen_ctrl; void* phy_panic_wd_ctl2; void* phy_panic_wd_ctl1; void* src; void* agc; void* t_cck; void* t_odfm; void* r_cck; void* r_odfm; void* rdar; void* det; void* wd; int /*<<< orphan*/  tsf; } ;
struct TYPE_3__ {scalar_t__ ath_hal_show_bb_panic; } ;
struct ath_hal {TYPE_1__ ah_config; } ;
struct TYPE_4__ {int ah_bb_panic_last_status; } ;

/* Variables and functions */
 TYPE_2__* AH9300 (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_PHY_BB_WD_AGC_SM ; 
 int /*<<< orphan*/  AR_PHY_BB_WD_DET_HANG ; 
 int /*<<< orphan*/  AR_PHY_BB_WD_RADAR_SM ; 
 int /*<<< orphan*/  AR_PHY_BB_WD_RX_CCK_SM ; 
 int /*<<< orphan*/  AR_PHY_BB_WD_RX_OFDM_SM ; 
 int /*<<< orphan*/  AR_PHY_BB_WD_SRCH_SM ; 
 int /*<<< orphan*/  AR_PHY_BB_WD_STATUS ; 
 int /*<<< orphan*/  AR_PHY_BB_WD_TX_CCK_SM ; 
 int /*<<< orphan*/  AR_PHY_BB_WD_TX_OFDM_SM ; 
 int /*<<< orphan*/  AR_PHY_GEN_CTRL ; 
 int /*<<< orphan*/  AR_PHY_PANIC_WD_CTL_1 ; 
 int /*<<< orphan*/  AR_PHY_PANIC_WD_CTL_2 ; 
 void* MS (int,int /*<<< orphan*/ ) ; 
 void* OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 scalar_t__ ar9300_get_mib_cycle_counts_pct (struct ath_hal*,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  ar9300_get_tsf32 (struct ath_hal*) ; 
 int /*<<< orphan*/  ath_hal_printf (struct ath_hal*,char*,...) ; 

int
ar9300_get_bb_panic_info(struct ath_hal *ah, struct hal_bb_panic_info *bb_panic)
{
    bb_panic->status = AH9300(ah)->ah_bb_panic_last_status;

    /*
     * For signature 04000539 do not print anything.
     * This is a very common occurence as a compromise between
     * BB Panic and AH_FALSE detects (EV71009). It indicates 
     * radar hang, which can be cleared by reprogramming
     * radar related register and does not requre a chip reset 
     */

    /* Suppress BB Status mesg following signature */
    switch (bb_panic->status) {
        case 0x04000539:
        case 0x04008009:    
        case 0x04000b09:
        case 0x1300000a:
        return -1;
    }

    bb_panic->tsf = ar9300_get_tsf32(ah);
    bb_panic->wd = MS(bb_panic->status, AR_PHY_BB_WD_STATUS);
    bb_panic->det = MS(bb_panic->status, AR_PHY_BB_WD_DET_HANG);
    bb_panic->rdar = MS(bb_panic->status, AR_PHY_BB_WD_RADAR_SM);
    bb_panic->r_odfm = MS(bb_panic->status, AR_PHY_BB_WD_RX_OFDM_SM);
    bb_panic->r_cck = MS(bb_panic->status, AR_PHY_BB_WD_RX_CCK_SM);
    bb_panic->t_odfm = MS(bb_panic->status, AR_PHY_BB_WD_TX_OFDM_SM);
    bb_panic->t_cck = MS(bb_panic->status, AR_PHY_BB_WD_TX_CCK_SM);
    bb_panic->agc = MS(bb_panic->status, AR_PHY_BB_WD_AGC_SM);
    bb_panic->src = MS(bb_panic->status, AR_PHY_BB_WD_SRCH_SM);
    bb_panic->phy_panic_wd_ctl1 = OS_REG_READ(ah, AR_PHY_PANIC_WD_CTL_1);
    bb_panic->phy_panic_wd_ctl2 = OS_REG_READ(ah, AR_PHY_PANIC_WD_CTL_2);
    bb_panic->phy_gen_ctrl = OS_REG_READ(ah, AR_PHY_GEN_CTRL);
    bb_panic->rxc_pcnt = bb_panic->rxf_pcnt = bb_panic->txf_pcnt = 0;
    bb_panic->cycles = ar9300_get_mib_cycle_counts_pct(ah, 
                                        &bb_panic->rxc_pcnt,
                                        &bb_panic->rxf_pcnt, 
                                        &bb_panic->txf_pcnt);

    if (ah->ah_config.ath_hal_show_bb_panic) {
        ath_hal_printf(ah, "\n==== BB update: BB status=0x%08x, "
            "tsf=0x%08x ====\n", bb_panic->status, bb_panic->tsf);
        ath_hal_printf(ah, "** BB state: wd=%u det=%u rdar=%u rOFDM=%d "
            "rCCK=%u tOFDM=%u tCCK=%u agc=%u src=%u **\n",
            bb_panic->wd, bb_panic->det, bb_panic->rdar,
            bb_panic->r_odfm, bb_panic->r_cck, bb_panic->t_odfm,
            bb_panic->t_cck, bb_panic->agc, bb_panic->src);
        ath_hal_printf(ah, "** BB WD cntl: cntl1=0x%08x cntl2=0x%08x **\n",
            bb_panic->phy_panic_wd_ctl1, bb_panic->phy_panic_wd_ctl2);
        ath_hal_printf(ah, "** BB mode: BB_gen_controls=0x%08x **\n", 
            bb_panic->phy_gen_ctrl);
        if (bb_panic->cycles) {
            ath_hal_printf(ah, "** BB busy times: rx_clear=%d%%, "
                "rx_frame=%d%%, tx_frame=%d%% **\n", bb_panic->rxc_pcnt, 
                bb_panic->rxf_pcnt, bb_panic->txf_pcnt);
        }
        ath_hal_printf(ah, "==== BB update: done ====\n\n");
    }

    return 0; //The returned data will be stored for athstats to retrieve it
}