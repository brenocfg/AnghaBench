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
typedef  scalar_t__ uint32_t ;
typedef  int uint16_t ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int const EEP_DELTA ; 
 int EEP_SCALE ; 
 int const abs (scalar_t__) ; 

void
ar5211GetLowerUpperValues(uint16_t value,
	const uint16_t *pList, uint16_t listSize,
	uint16_t *pLowerValue, uint16_t *pUpperValue)
{
	const uint16_t listEndValue = *(pList + listSize - 1);
	uint32_t target = value * EEP_SCALE;
	int i;

	/*
	 * See if value is lower than the first value in the list
	 * if so return first value
	 */
	if (target < (uint32_t)(*pList * EEP_SCALE - EEP_DELTA)) {
		*pLowerValue = *pList;
		*pUpperValue = *pList;
		return;
	}

	/*
	 * See if value is greater than last value in list
	 * if so return last value
	 */
	if (target > (uint32_t)(listEndValue * EEP_SCALE + EEP_DELTA)) {
		*pLowerValue = listEndValue;
		*pUpperValue = listEndValue;
		return;
	}

	/* look for value being near or between 2 values in list */
	for (i = 0; i < listSize; i++) {
		/*
		 * If value is close to the current value of the list
		 * then target is not between values, it is one of the values
		 */
		if (abs(pList[i] * EEP_SCALE - (int32_t) target) < EEP_DELTA) {
			*pLowerValue = pList[i];
			*pUpperValue = pList[i];
			return;
		}

		/*
		 * Look for value being between current value and next value
		 * if so return these 2 values
		 */
		if (target < (uint32_t)(pList[i + 1] * EEP_SCALE - EEP_DELTA)) {
			*pLowerValue = pList[i];
			*pUpperValue = pList[i + 1];
			return;
		}
	}
}