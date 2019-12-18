#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct ath_hal {int dummy; } ;
struct TYPE_4__ {scalar_t__ ss_fft_period; scalar_t__ ss_period; scalar_t__ ss_count; scalar_t__ ss_short_report; } ;
typedef  TYPE_1__ HAL_SPECTRAL_PARAM ;

/* Variables and functions */
 scalar_t__ AH_TRUE ; 
 int /*<<< orphan*/  AR_PHY_SPECTRAL_SCAN ; 
 int AR_PHY_SPECTRAL_SCAN_COUNT ; 
 int AR_PHY_SPECTRAL_SCAN_COUNT_KIWI ; 
 int AR_PHY_SPECTRAL_SCAN_ENA ; 
 int AR_PHY_SPECTRAL_SCAN_FFT_PERIOD ; 
 int AR_PHY_SPECTRAL_SCAN_PERIOD ; 
 int AR_PHY_SPECTRAL_SCAN_PHYERR_MASK_SELECT_KIWI ; 
 int AR_PHY_SPECTRAL_SCAN_SHORT_REPEAT ; 
 int AR_PHY_SPECTRAL_SCAN_SHORT_REPEAT_KIWI ; 
 scalar_t__ AR_SREV_MERLIN (struct ath_hal*) ; 
 scalar_t__ HAL_SPECTRAL_PARAM_NOVAL ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 
 int SM (scalar_t__,int) ; 
 int /*<<< orphan*/  ar5416GetSpectralParams (struct ath_hal*,TYPE_1__*) ; 
 int /*<<< orphan*/  ar5416PrepSpectralScan (struct ath_hal*) ; 

void
ar5416ConfigureSpectralScan(struct ath_hal *ah, HAL_SPECTRAL_PARAM *ss)
{
	uint32_t val;

	ar5416PrepSpectralScan(ah);

	val = OS_REG_READ(ah, AR_PHY_SPECTRAL_SCAN);

	if (ss->ss_fft_period != HAL_SPECTRAL_PARAM_NOVAL) {
		val &= ~AR_PHY_SPECTRAL_SCAN_FFT_PERIOD;
		val |= SM(ss->ss_fft_period, AR_PHY_SPECTRAL_SCAN_FFT_PERIOD);
	}

	if (ss->ss_period != HAL_SPECTRAL_PARAM_NOVAL) {
		val &= ~AR_PHY_SPECTRAL_SCAN_PERIOD;
		val |= SM(ss->ss_period, AR_PHY_SPECTRAL_SCAN_PERIOD);
	}

	if (ss->ss_period != HAL_SPECTRAL_PARAM_NOVAL) {
		val &= ~AR_PHY_SPECTRAL_SCAN_PERIOD;
		val |= SM(ss->ss_period, AR_PHY_SPECTRAL_SCAN_PERIOD);
	}

	/* This section is different for Kiwi and Merlin */
	if (AR_SREV_MERLIN(ah) ) {
		if (ss->ss_count != HAL_SPECTRAL_PARAM_NOVAL) {
			val &= ~AR_PHY_SPECTRAL_SCAN_COUNT;
			val |= SM(ss->ss_count, AR_PHY_SPECTRAL_SCAN_COUNT);
		}

		if (ss->ss_short_report == AH_TRUE) {
			val |= AR_PHY_SPECTRAL_SCAN_SHORT_REPEAT;
		} else if (ss->ss_short_report != HAL_SPECTRAL_PARAM_NOVAL) {
			val &= ~AR_PHY_SPECTRAL_SCAN_SHORT_REPEAT;
		}
	} else {
		if (ss->ss_count != HAL_SPECTRAL_PARAM_NOVAL) {
			/*
			 * In Merlin, for continuous scan, scan_count = 128.
			 * In case of Kiwi, this value should be 0
			 */
			if (ss->ss_count == 128)
				ss->ss_count = 0;
			val &= ~AR_PHY_SPECTRAL_SCAN_COUNT_KIWI;
			val |= SM(ss->ss_count, AR_PHY_SPECTRAL_SCAN_COUNT_KIWI);
		}

		if (ss->ss_short_report == AH_TRUE) {
			val |= AR_PHY_SPECTRAL_SCAN_SHORT_REPEAT_KIWI;
		} else if (ss->ss_short_report != HAL_SPECTRAL_PARAM_NOVAL) {
			val &= ~AR_PHY_SPECTRAL_SCAN_SHORT_REPEAT_KIWI;
		}

		//Select the mask to be same as before
		val |= AR_PHY_SPECTRAL_SCAN_PHYERR_MASK_SELECT_KIWI;
	}
	// Enable spectral scan
	OS_REG_WRITE(ah, AR_PHY_SPECTRAL_SCAN, val | AR_PHY_SPECTRAL_SCAN_ENA);

	ar5416GetSpectralParams(ah, ss);
}