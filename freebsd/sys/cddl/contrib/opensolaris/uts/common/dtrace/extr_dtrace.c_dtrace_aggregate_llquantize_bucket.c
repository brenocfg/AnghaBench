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
typedef  int uint16_t ;
typedef  int int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 

__attribute__((used)) static int
dtrace_aggregate_llquantize_bucket(uint16_t factor, uint16_t low,
    uint16_t high, uint16_t nsteps, int64_t value)
{
	int64_t this = 1, last, next;
	int base = 1, order;

	ASSERT(factor <= nsteps);
	ASSERT(nsteps % factor == 0);

	for (order = 0; order < low; order++)
		this *= factor;

	/*
	 * If our value is less than our factor taken to the power of the
	 * low order of magnitude, it goes into the zeroth bucket.
	 */
	if (value < (last = this))
		return (0);

	for (this *= factor; order <= high; order++) {
		int nbuckets = this > nsteps ? nsteps : this;

		if ((next = this * factor) < this) {
			/*
			 * We should not generally get log/linear quantizations
			 * with a high magnitude that allows 64-bits to
			 * overflow, but we nonetheless protect against this
			 * by explicitly checking for overflow, and clamping
			 * our value accordingly.
			 */
			value = this - 1;
		}

		if (value < this) {
			/*
			 * If our value lies within this order of magnitude,
			 * determine its position by taking the offset within
			 * the order of magnitude, dividing by the bucket
			 * width, and adding to our (accumulated) base.
			 */
			return (base + (value - last) / (this / nbuckets));
		}

		base += nbuckets - (nbuckets / factor);
		last = this;
		this = next;
	}

	/*
	 * Our value is greater than or equal to our factor taken to the
	 * power of one plus the high magnitude -- return the top bucket.
	 */
	return (base);
}