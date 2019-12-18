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
typedef  scalar_t__ u_int32_t ;
typedef  int u_int16_t ;

/* Variables and functions */
 int EEP_DELTA ; 
 int EEP_SCALE ; 
 int abs (scalar_t__) ; 

__attribute__((used)) static void
ar5212GetLowerUpperValues(u_int16_t v, u_int16_t *lp, u_int16_t listSize,
                          u_int16_t *vlo, u_int16_t *vhi)
{
	u_int32_t target = v * EEP_SCALE;
	u_int16_t *ep = lp+listSize;

	/*
	 * Check first and last elements for out-of-bounds conditions.
	 */
	if (target < (u_int32_t)(lp[0] * EEP_SCALE - EEP_DELTA)) {
		*vlo = *vhi = lp[0];
		return;
	}
	if (target > (u_int32_t)(ep[-1] * EEP_SCALE + EEP_DELTA)) {
		*vlo = *vhi = ep[-1];
		return;
	}

	/* look for value being near or between 2 values in list */
	for (; lp < ep; lp++) {
		/*
		 * If value is close to the current value of the list
		 * then target is not between values, it is one of the values
		 */
		if (abs(lp[0] * EEP_SCALE - target) < EEP_DELTA) {
			*vlo = *vhi = lp[0];
			return;
		}
		/*
		 * Look for value being between current value and next value
		 * if so return these 2 values
		 */
		if (target < (u_int32_t)(lp[1] * EEP_SCALE - EEP_DELTA)) {
			*vlo = lp[0];
			*vhi = lp[1];
			return;
		}
	}
}