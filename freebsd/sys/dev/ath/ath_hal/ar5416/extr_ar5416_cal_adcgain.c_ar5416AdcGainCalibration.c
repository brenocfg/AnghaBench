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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;
struct ath_hal {int dummy; } ;
struct ar5416PerCal {scalar_t__ (* totalAdcIOddPhase ) (scalar_t__) ;scalar_t__ (* totalAdcIEvenPhase ) (scalar_t__) ;scalar_t__ (* totalAdcQOddPhase ) (scalar_t__) ;scalar_t__ (* totalAdcQEvenPhase ) (scalar_t__) ;} ;
struct TYPE_2__ {struct ar5416PerCal ah_cal; } ;

/* Variables and functions */
 TYPE_1__* AH5416 (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_PHY_NEW_ADC_DC_GAIN_CORR (scalar_t__) ; 
 int /*<<< orphan*/  AR_PHY_NEW_ADC_GAIN_CORR_ENABLE ; 
 int /*<<< orphan*/  HALDEBUG (struct ath_hal*,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  HAL_DEBUG_PERCAL ; 
 scalar_t__ OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_SET_BIT (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ stub1 (scalar_t__) ; 
 scalar_t__ stub2 (scalar_t__) ; 
 scalar_t__ stub3 (scalar_t__) ; 
 scalar_t__ stub4 (scalar_t__) ; 

void
ar5416AdcGainCalibration(struct ath_hal *ah, uint8_t numChains)
{
	struct ar5416PerCal *cal = &AH5416(ah)->ah_cal;
	uint32_t i;

	for (i = 0; i < numChains; i++) {
		uint32_t iOddMeasOffset  = cal->totalAdcIOddPhase(i);
		uint32_t iEvenMeasOffset = cal->totalAdcIEvenPhase(i);
		uint32_t qOddMeasOffset  = cal->totalAdcQOddPhase(i);
		uint32_t qEvenMeasOffset = cal->totalAdcQEvenPhase(i);

		HALDEBUG(ah, HAL_DEBUG_PERCAL,
		    "Start ADC Gain Cal for Chain %d\n", i);
		HALDEBUG(ah, HAL_DEBUG_PERCAL,
		    "  pwr_meas_odd_i = 0x%08x\n", iOddMeasOffset);
		HALDEBUG(ah, HAL_DEBUG_PERCAL,
		    "  pwr_meas_even_i = 0x%08x\n", iEvenMeasOffset);
		HALDEBUG(ah, HAL_DEBUG_PERCAL,
		    "  pwr_meas_odd_q = 0x%08x\n", qOddMeasOffset);
		HALDEBUG(ah, HAL_DEBUG_PERCAL,
		    "  pwr_meas_even_q = 0x%08x\n", qEvenMeasOffset);

		if (iOddMeasOffset != 0 && qEvenMeasOffset != 0) {
			uint32_t iGainMismatch =
			    ((iEvenMeasOffset*32)/iOddMeasOffset) & 0x3f;
			uint32_t qGainMismatch =
			    ((qOddMeasOffset*32)/qEvenMeasOffset) & 0x3f;
			uint32_t val;

			HALDEBUG(ah, HAL_DEBUG_PERCAL,
			    " gain_mismatch_i = 0x%08x\n",
			    iGainMismatch);
			HALDEBUG(ah, HAL_DEBUG_PERCAL,
			    " gain_mismatch_q = 0x%08x\n",
			    qGainMismatch);

			val = OS_REG_READ(ah, AR_PHY_NEW_ADC_DC_GAIN_CORR(i));
			val &= 0xfffff000;
			val |= (qGainMismatch) | (iGainMismatch << 6);
			OS_REG_WRITE(ah, AR_PHY_NEW_ADC_DC_GAIN_CORR(i), val); 

			HALDEBUG(ah,  HAL_DEBUG_PERCAL,
			    "ADC Gain Cal done for Chain %d\n", i);
		}
	}
	OS_REG_SET_BIT(ah, AR_PHY_NEW_ADC_DC_GAIN_CORR(0),
	    AR_PHY_NEW_ADC_GAIN_CORR_ENABLE);
}