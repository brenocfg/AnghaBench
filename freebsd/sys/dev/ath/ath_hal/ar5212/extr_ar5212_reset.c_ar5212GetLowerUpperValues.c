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

/* Variables and functions */
 int /*<<< orphan*/  AH_FALSE ; 
 int EEP_DELTA ; 
 int EEP_SCALE ; 
 int /*<<< orphan*/  HALASSERT (int /*<<< orphan*/ ) ; 
 int udiff (int,scalar_t__) ; 

void
ar5212GetLowerUpperValues(uint16_t v, uint16_t *lp, uint16_t listSize,
                          uint16_t *vlo, uint16_t *vhi)
{
	uint32_t target = v * EEP_SCALE;
	uint16_t *ep = lp+listSize;

	/*
	 * Check first and last elements for out-of-bounds conditions.
	 */
	if (target < (uint32_t)(lp[0] * EEP_SCALE - EEP_DELTA)) {
		*vlo = *vhi = lp[0];
		return;
	}
	if (target > (uint32_t)(ep[-1] * EEP_SCALE + EEP_DELTA)) {
		*vlo = *vhi = ep[-1];
		return;
	}

	/* look for value being near or between 2 values in list */
	for (; lp < ep; lp++) {
		/*
		 * If value is close to the current value of the list
		 * then target is not between values, it is one of the values
		 */
		if (udiff(lp[0] * EEP_SCALE, target) < EEP_DELTA) {
			*vlo = *vhi = lp[0];
			return;
		}
		/*
		 * Look for value being between current value and next value
		 * if so return these 2 values
		 */
		if (target < (uint32_t)(lp[1] * EEP_SCALE - EEP_DELTA)) {
			*vlo = lp[0];
			*vhi = lp[1];
			return;
		}
	}
	HALASSERT(AH_FALSE);		/* should not reach here */
}