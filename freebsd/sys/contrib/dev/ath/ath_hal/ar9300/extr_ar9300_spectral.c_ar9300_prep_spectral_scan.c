#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ath_hal {int dummy; } ;
struct TYPE_2__ {scalar_t__ ah_curchan; } ;

/* Variables and functions */
 TYPE_1__* AH_PRIVATE (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_PHY_ERR ; 
 int /*<<< orphan*/  HAL_PHYERR_SPECTRAL ; 
 scalar_t__ IS_5GHZ_FAST_CLOCK_EN (struct ath_hal*,scalar_t__) ; 
 int /*<<< orphan*/  MAX_CCA_THRESH ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar9300_classify_strong_bins (struct ath_hal*) ; 
 int /*<<< orphan*/  ar9300_disable_dc_offset (struct ath_hal*) ; 
 int /*<<< orphan*/  ar9300_disable_radar (struct ath_hal*) ; 
 int /*<<< orphan*/  ar9300_disable_strong_signal (struct ath_hal*) ; 
 int /*<<< orphan*/  ar9300_disable_weak_signal (struct ath_hal*) ; 
 int /*<<< orphan*/  ar9300_enable_cck_detect (struct ath_hal*) ; 
 int /*<<< orphan*/  ar9300_set_cca_threshold (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar9300_set_radar_dc_thresh (struct ath_hal*) ; 

void ar9300_prep_spectral_scan(struct ath_hal *ah)
{
    ar9300_disable_radar(ah);
    ar9300_classify_strong_bins(ah);
    ar9300_disable_dc_offset(ah);
    if (AH_PRIVATE(ah)->ah_curchan &&
        IS_5GHZ_FAST_CLOCK_EN(ah, AH_PRIVATE(ah)->ah_curchan))
    { /* fast clock */
        ar9300_enable_cck_detect(ah);
    }
#ifdef DEMO_MODE
    ar9300_disable_strong_signal(ah);
    ar9300_disable_weak_signal(ah);
    ar9300_set_radar_dc_thresh(ah);
    ar9300_set_cca_threshold(ah, MAX_CCA_THRESH);
    /*ar9300_disable_restart(ah);*/
#endif
    OS_REG_WRITE(ah, AR_PHY_ERR, HAL_PHYERR_SPECTRAL);
}