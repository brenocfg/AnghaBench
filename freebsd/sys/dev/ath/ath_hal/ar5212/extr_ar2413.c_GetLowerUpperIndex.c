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
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  int const int16_t ;

/* Variables and functions */

__attribute__((used)) static void
GetLowerUpperIndex(int16_t v, const uint16_t *lp, uint16_t listSize,
                          uint32_t *vlo, uint32_t *vhi)
{
	int16_t target = v;
	const uint16_t *ep = lp+listSize;
	const uint16_t *tp;

	/*
	 * Check first and last elements for out-of-bounds conditions.
	 */
	if (target < lp[0]) {
		*vlo = *vhi = 0;
		return;
	}
	if (target >= ep[-1]) {
		*vlo = *vhi = listSize - 1;
		return;
	}

	/* look for value being near or between 2 values in list */
	for (tp = lp; tp < ep; tp++) {
		/*
		 * If value is close to the current value of the list
		 * then target is not between values, it is one of the values
		 */
		if (*tp == target) {
			*vlo = *vhi = tp - (const uint16_t *) lp;
			return;
		}
		/*
		 * Look for value being between current value and next value
		 * if so return these 2 values
		 */
		if (target < tp[1]) {
			*vlo = tp - (const uint16_t *) lp;
			*vhi = *vlo + 1;
			return;
		}
	}
}