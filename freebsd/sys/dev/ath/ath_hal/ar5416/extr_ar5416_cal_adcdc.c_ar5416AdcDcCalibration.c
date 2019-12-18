#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct ath_hal {int dummy; } ;
struct ar5416PerCal {int (* totalAdcDcOffsetIOddPhase ) (int) ;int (* totalAdcDcOffsetIEvenPhase ) (int) ;int (* totalAdcDcOffsetQOddPhase ) (int) ;int (* totalAdcDcOffsetQEvenPhase ) (int) ;TYPE_1__* cal_curr; } ;
typedef  int int32_t ;
struct TYPE_6__ {struct ar5416PerCal ah_cal; } ;
struct TYPE_5__ {int calCountMax; int calNumSamples; } ;
struct TYPE_4__ {TYPE_2__* calData; } ;
typedef  TYPE_2__ HAL_PERCAL_DATA ;

/* Variables and functions */
 TYPE_3__* AH5416 (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_PHY_NEW_ADC_DC_GAIN_CORR (int) ; 
 int /*<<< orphan*/  AR_PHY_NEW_ADC_DC_OFFSET_CORR_ENABLE ; 
 int /*<<< orphan*/  HALASSERT (int) ; 
 int /*<<< orphan*/  HALDEBUG (struct ath_hal*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  HAL_DEBUG_PERCAL ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_SET_BIT (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 
 int stub1 (int) ; 
 int stub2 (int) ; 
 int stub3 (int) ; 
 int stub4 (int) ; 

void
ar5416AdcDcCalibration(struct ath_hal *ah, uint8_t numChains)
{
	struct ar5416PerCal *cal = &AH5416(ah)->ah_cal;
	const HAL_PERCAL_DATA *calData = cal->cal_curr->calData;
	uint32_t numSamples;
	int i;

	numSamples = (1 << (calData->calCountMax + 5)) * calData->calNumSamples;
	for (i = 0; i < numChains; i++) {
		uint32_t iOddMeasOffset = cal->totalAdcDcOffsetIOddPhase(i);
		uint32_t iEvenMeasOffset = cal->totalAdcDcOffsetIEvenPhase(i);
		int32_t qOddMeasOffset = cal->totalAdcDcOffsetQOddPhase(i);
		int32_t qEvenMeasOffset = cal->totalAdcDcOffsetQEvenPhase(i);
		int32_t qDcMismatch, iDcMismatch;
		uint32_t val;

		HALDEBUG(ah, HAL_DEBUG_PERCAL,
		    "Starting ADC DC Offset Cal for Chain %d\n", i);

		HALDEBUG(ah, HAL_DEBUG_PERCAL, " pwr_meas_odd_i = %d\n",
		    iOddMeasOffset);
		HALDEBUG(ah, HAL_DEBUG_PERCAL, " pwr_meas_even_i = %d\n",
		    iEvenMeasOffset);
		HALDEBUG(ah, HAL_DEBUG_PERCAL, " pwr_meas_odd_q = %d\n",
		    qOddMeasOffset);
		HALDEBUG(ah, HAL_DEBUG_PERCAL, " pwr_meas_even_q = %d\n",
		    qEvenMeasOffset);

		HALASSERT(numSamples);

		iDcMismatch = (((iEvenMeasOffset - iOddMeasOffset) * 2) /
		    numSamples) & 0x1ff;
		qDcMismatch = (((qOddMeasOffset - qEvenMeasOffset) * 2) /
		    numSamples) & 0x1ff;
		HALDEBUG(ah, HAL_DEBUG_PERCAL,
		    " dc_offset_mismatch_i = 0x%08x\n", iDcMismatch);
		HALDEBUG(ah, HAL_DEBUG_PERCAL,
		    " dc_offset_mismatch_q = 0x%08x\n", qDcMismatch);

		val = OS_REG_READ(ah, AR_PHY_NEW_ADC_DC_GAIN_CORR(i));
		val &= 0xc0000fff;
		val |= (qDcMismatch << 12) | (iDcMismatch << 21);
		OS_REG_WRITE(ah, AR_PHY_NEW_ADC_DC_GAIN_CORR(i), val); 

		HALDEBUG(ah, HAL_DEBUG_PERCAL,
		    "ADC DC Offset Cal done for Chain %d\n", i);
	}
	OS_REG_SET_BIT(ah, AR_PHY_NEW_ADC_DC_GAIN_CORR(0),
	    AR_PHY_NEW_ADC_DC_OFFSET_CORR_ENABLE);
}