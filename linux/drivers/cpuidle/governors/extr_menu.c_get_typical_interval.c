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
typedef  unsigned int uint64_t ;
typedef  unsigned int u64 ;
struct menu_device {unsigned int* intervals; } ;
typedef  unsigned int int64_t ;

/* Variables and functions */
 int INTERVALS ; 
 unsigned int INTERVAL_SHIFT ; 
 unsigned int INT_MAX ; 
 int U64_MAX ; 
 unsigned int UINT_MAX ; 
 unsigned int div_u64 (unsigned int,int) ; 
 int /*<<< orphan*/  do_div (unsigned int,int) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static unsigned int get_typical_interval(struct menu_device *data,
					 unsigned int predicted_us)
{
	int i, divisor;
	unsigned int min, max, thresh, avg;
	uint64_t sum, variance;

	thresh = INT_MAX; /* Discard outliers above this value */

again:

	/* First calculate the average of past intervals */
	min = UINT_MAX;
	max = 0;
	sum = 0;
	divisor = 0;
	for (i = 0; i < INTERVALS; i++) {
		unsigned int value = data->intervals[i];
		if (value <= thresh) {
			sum += value;
			divisor++;
			if (value > max)
				max = value;

			if (value < min)
				min = value;
		}
	}

	/*
	 * If the result of the computation is going to be discarded anyway,
	 * avoid the computation altogether.
	 */
	if (min >= predicted_us)
		return UINT_MAX;

	if (divisor == INTERVALS)
		avg = sum >> INTERVAL_SHIFT;
	else
		avg = div_u64(sum, divisor);

	/* Then try to determine variance */
	variance = 0;
	for (i = 0; i < INTERVALS; i++) {
		unsigned int value = data->intervals[i];
		if (value <= thresh) {
			int64_t diff = (int64_t)value - avg;
			variance += diff * diff;
		}
	}
	if (divisor == INTERVALS)
		variance >>= INTERVAL_SHIFT;
	else
		do_div(variance, divisor);

	/*
	 * The typical interval is obtained when standard deviation is
	 * small (stddev <= 20 us, variance <= 400 us^2) or standard
	 * deviation is small compared to the average interval (avg >
	 * 6*stddev, avg^2 > 36*variance). The average is smaller than
	 * UINT_MAX aka U32_MAX, so computing its square does not
	 * overflow a u64. We simply reject this candidate average if
	 * the standard deviation is greater than 715 s (which is
	 * rather unlikely).
	 *
	 * Use this result only if there is no timer to wake us up sooner.
	 */
	if (likely(variance <= U64_MAX/36)) {
		if ((((u64)avg*avg > variance*36) && (divisor * 4 >= INTERVALS * 3))
							|| variance <= 400) {
			return avg;
		}
	}

	/*
	 * If we have outliers to the upside in our distribution, discard
	 * those by setting the threshold to exclude these outliers, then
	 * calculate the average and standard deviation again. Once we get
	 * down to the bottom 3/4 of our samples, stop excluding samples.
	 *
	 * This can deal with workloads that have long pauses interspersed
	 * with sporadic activity with a bunch of short pauses.
	 */
	if ((divisor * 4) <= INTERVALS * 3)
		return UINT_MAX;

	thresh = max - 1;
	goto again;
}