#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct ath_hal {int dummy; } ;
struct TYPE_3__ {void* radar_bin_thresh_sel; void* ss_short_report; void* ss_count; void* ss_period; void* ss_fft_period; } ;
typedef  TYPE_1__ HAL_SPECTRAL_PARAM ;

/* Variables and functions */
 int /*<<< orphan*/  AR_PHY_RADAR_1 ; 
 int /*<<< orphan*/  AR_PHY_RADAR_1_BIN_THRESH_SELECT ; 
 int /*<<< orphan*/  AR_PHY_SPECTRAL_SCAN ; 
 int /*<<< orphan*/  AR_PHY_SPECTRAL_SCAN_COUNT ; 
 int /*<<< orphan*/  AR_PHY_SPECTRAL_SCAN_COUNT_KIWI ; 
 int /*<<< orphan*/  AR_PHY_SPECTRAL_SCAN_FFT_PERIOD ; 
 int /*<<< orphan*/  AR_PHY_SPECTRAL_SCAN_PERIOD ; 
 int /*<<< orphan*/  AR_PHY_SPECTRAL_SCAN_SHORT_REPEAT ; 
 int /*<<< orphan*/  AR_PHY_SPECTRAL_SCAN_SHORT_REPEAT_KIWI ; 
 scalar_t__ AR_SREV_MERLIN (struct ath_hal*) ; 
 void* MS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 

void
ar5416GetSpectralParams(struct ath_hal *ah, HAL_SPECTRAL_PARAM *ss)
{
	uint32_t val;

	val = OS_REG_READ(ah, AR_PHY_SPECTRAL_SCAN);

	ss->ss_fft_period = MS(val, AR_PHY_SPECTRAL_SCAN_FFT_PERIOD);
	ss->ss_period = MS(val, AR_PHY_SPECTRAL_SCAN_PERIOD);
	if (AR_SREV_MERLIN(ah) ) {
		ss->ss_count = MS(val, AR_PHY_SPECTRAL_SCAN_COUNT);
		ss->ss_short_report = MS(val, AR_PHY_SPECTRAL_SCAN_SHORT_REPEAT);
	} else {
		ss->ss_count = MS(val, AR_PHY_SPECTRAL_SCAN_COUNT_KIWI);
		ss->ss_short_report = MS(val, AR_PHY_SPECTRAL_SCAN_SHORT_REPEAT_KIWI);
	}
	val = OS_REG_READ(ah, AR_PHY_RADAR_1);
	ss->radar_bin_thresh_sel = MS(val, AR_PHY_RADAR_1_BIN_THRESH_SELECT);
}