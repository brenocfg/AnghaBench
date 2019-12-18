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
struct histogram {double count; double min; double max; unsigned int num_bins; unsigned int gap; struct bin* bins; } ;
struct bin {double centroid; double count; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 scalar_t__ eq (double,int /*<<< orphan*/ ) ; 
 double sqrt (double) ; 

__attribute__((used)) static double
histogram_query(const struct histogram *h, double quantile)
{
	unsigned lhs = 0, rhs = 0;
	struct bin lhs_bin = { 0, 0 }, rhs_bin = { 0, 0 };
	double lhs_total = 0, rhs_total = 0;
	double a = 0, b = 0, c = 0, z = 0;

	/* The "needle" is the n'th value represented by the histogram. For
	 * example, if the histogram summarizes 100 entries and we're querying
	 * for the 50th percentile, the needle is 50. */
	double needle = h->count * quantile;
	if (quantile <= 0)
		return h->min;
	if (quantile >= 1)
		return h->max;

	/* Divide the histogram into slices: the first slice starts at h->min
	 * and ends at h->bins[0].centroid, the last slice starts at
	 * h->bins[h->num_bins].centroid and ends at h->max, and the slices
	 * in the middle are between adjacent centroids (minding the gap). The
	 * "count" in each slice is the average of the count in the two bins
	 * that define it. Find the slice containing the needle by keeping a
	 * running total of the slice counts. */
	while (rhs_total < needle) {
		/* Determine the left-hand side bin of the current slice. Note
		 * that the first slice has bin 0 on its right-hand side! */
		if (rhs == 0) {
			lhs_bin.centroid = h->min;
			lhs_bin.count = 0;
		} else {
			lhs_bin = h->bins[lhs];
		}

		/* Determine the right-hand side bin of the current slice... */
		if (rhs > h->num_bins) {
			lhs_bin.centroid = h->max;
			rhs_bin.count = 0;
		} else {
			rhs_bin = h->bins[rhs];
		}

		/* Update the running totals: the lhs total is whatever the rhs
		 * total was previously, and the new rhs total includes the
		 * count for this slice. */
		lhs_total = rhs_total;
		rhs_total += 0.5 * (lhs_bin.count + rhs_bin.count);

		/* Next iteration's left-hand side is the current iteration's
		 * right-hand side, and next iteration's right-hand side is one
		 * bin further right (minding the gap). */
		lhs = rhs++;
		if (rhs == h->gap)
			rhs++;
	}

	/* Approximate the value at the requested quantile... */
	a = rhs_bin.count - lhs_bin.count;
	if (eq(a, 0)) {
		b = rhs_total - lhs_total;
		z = eq(b, 0) ? 0 : (needle - lhs_total) / b;
	} else {
		b = 2 * lhs_bin.count;
		c = 2 * (lhs_total - needle);
		z = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
	}
	return lhs_bin.centroid + (rhs_bin.centroid - lhs_bin.centroid) * z;
}