#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int8_t ;
struct ath_hal_9300 {scalar_t__ ah_cal_samples; } ;
struct ath_hal {int dummy; } ;
struct TYPE_10__ {scalar_t__ cal_state; TYPE_1__* cal_data; } ;
struct TYPE_9__ {int calValid; } ;
struct TYPE_8__ {scalar_t__ cal_num_samples; int cal_type; int /*<<< orphan*/  (* cal_post_proc ) (struct ath_hal*,int) ;int /*<<< orphan*/  (* cal_collect ) (struct ath_hal*,int) ;} ;
typedef  TYPE_2__ HAL_CHANNEL_INTERNAL ;
typedef  TYPE_3__ HAL_CAL_LIST ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 struct ath_hal_9300* AH9300 (struct ath_hal*) ; 
 int /*<<< orphan*/  AH_FALSE ; 
 int /*<<< orphan*/  AH_TRUE ; 
 int AR9300_MAX_CHAINS ; 
 int /*<<< orphan*/  AR_PHY_TIMING4 ; 
 int AR_PHY_TIMING4_DO_CAL ; 
 scalar_t__ CAL_DONE ; 
 scalar_t__ CAL_RUNNING ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar9300_reset_calibration (struct ath_hal*,TYPE_3__*) ; 
 int /*<<< orphan*/  ar9300_setup_calibration (struct ath_hal*,TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (struct ath_hal*,int) ; 
 int /*<<< orphan*/  stub2 (struct ath_hal*,int) ; 

__attribute__((used)) inline static void
ar9300_per_calibration(struct ath_hal *ah,  HAL_CHANNEL_INTERNAL *ichan,
    u_int8_t rxchainmask, HAL_CAL_LIST *curr_cal, HAL_BOOL *is_cal_done)
{
    struct ath_hal_9300 *ahp = AH9300(ah);

    /* Cal is assumed not done until explicitly set below */
    *is_cal_done = AH_FALSE;

    /* Calibration in progress. */
    if (curr_cal->cal_state == CAL_RUNNING) {
        /* Check to see if it has finished. */
        if (!(OS_REG_READ(ah, AR_PHY_TIMING4) & AR_PHY_TIMING4_DO_CAL)) {
            int i, num_chains = 0;
            for (i = 0; i < AR9300_MAX_CHAINS; i++) {
                if (rxchainmask & (1 << i)) {
                    num_chains++;
                }
            }

            /*
             * Accumulate cal measures for active chains
             */
            curr_cal->cal_data->cal_collect(ah, num_chains);

            ahp->ah_cal_samples++;

            if (ahp->ah_cal_samples >= curr_cal->cal_data->cal_num_samples) {
                /*
                 * Process accumulated data
                 */
                curr_cal->cal_data->cal_post_proc(ah, num_chains);

                /* Calibration has finished. */
                ichan->calValid |= curr_cal->cal_data->cal_type;
                curr_cal->cal_state = CAL_DONE;
                *is_cal_done = AH_TRUE;
            } else {
                /* Set-up collection of another sub-sample until we
                 * get desired number
                 */
                ar9300_setup_calibration(ah, curr_cal);
            }
        }
    } else if (!(ichan->calValid & curr_cal->cal_data->cal_type)) {
        /* If current cal is marked invalid in channel, kick it off */
        ar9300_reset_calibration(ah, curr_cal);
    }
}