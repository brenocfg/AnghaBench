#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_5__ {int /*<<< orphan*/  numChannels; int /*<<< orphan*/  pChannelList; } ;
typedef  TYPE_1__ PCDACS_EEPROM ;

/* Variables and functions */
 scalar_t__ ar5212FindValueInList (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ar5212GetLowerUpperPcdacs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ar5212GetLowerUpperValues (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  interpolate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint16_t
ar5212GetScaledPower(uint16_t channel, uint16_t pcdacValue,
	const PCDACS_EEPROM *pSrcStruct)
{
	uint16_t powerValue;
	uint16_t lFreq, rFreq;		/* left and right frequency values */
	uint16_t llPcdac, ulPcdac;	/* lower and upper left pcdac values */
	uint16_t lrPcdac, urPcdac;	/* lower and upper right pcdac values */
	uint16_t lPwr, uPwr;		/* lower and upper temp pwr values */
	uint16_t lScaledPwr, rScaledPwr; /* left and right scaled power */

	if (ar5212FindValueInList(channel, pcdacValue, pSrcStruct, &powerValue)) {
		/* value was copied from srcStruct */
		return powerValue;
	}

	ar5212GetLowerUpperValues(channel,
		pSrcStruct->pChannelList, pSrcStruct->numChannels,
		&lFreq, &rFreq);
	ar5212GetLowerUpperPcdacs(pcdacValue,
		lFreq, pSrcStruct, &llPcdac, &ulPcdac);
	ar5212GetLowerUpperPcdacs(pcdacValue,
		rFreq, pSrcStruct, &lrPcdac, &urPcdac);

	/* get the power index for the pcdac value */
	ar5212FindValueInList(lFreq, llPcdac, pSrcStruct, &lPwr);
	ar5212FindValueInList(lFreq, ulPcdac, pSrcStruct, &uPwr);
	lScaledPwr = interpolate(pcdacValue, llPcdac, ulPcdac, lPwr, uPwr);

	ar5212FindValueInList(rFreq, lrPcdac, pSrcStruct, &lPwr);
	ar5212FindValueInList(rFreq, urPcdac, pSrcStruct, &uPwr);
	rScaledPwr = interpolate(pcdacValue, lrPcdac, urPcdac, lPwr, uPwr);

	return interpolate(channel, lFreq, rFreq, lScaledPwr, rScaledPwr);
}