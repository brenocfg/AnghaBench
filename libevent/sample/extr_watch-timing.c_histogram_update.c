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
struct histogram {double min; double max; int gap; int num_bins; int max_bins; TYPE_1__* bins; int /*<<< orphan*/  count; } ;
struct TYPE_2__ {double centroid; int count; } ;

/* Variables and functions */
 double INFINITY ; 
 scalar_t__ eq (double,double) ; 

__attribute__((used)) static void
histogram_update(struct histogram *h, double observation)
{
	unsigned bin;
	double delta;
	double min_delta = INFINITY;

	/* Update population count, min and max */
	++(h->count);
	if (observation < h->min)
		h->min = observation;
	if (observation > h->max)
		h->max = observation;

	/* Shift the insertion gap to the left or right so that the new bin
	 * containing the given observation as its centroid will be in the right
	 * order with respect to the other bins. */
	while (1) {
		/* Look at the bin to the left of the gap... */
		if (h->gap != 0) {
			/* If its centroid is greater than the observation, move
			 * the gap to the left and try again... */
			if (h->bins[h->gap - 1].centroid > observation) {
				h->bins[h->gap] = h->bins[h->gap - 1];
				--(h->gap);
				continue;
			}
			/* If its centroid is equal to the observation, just
			 * update its count in place. */
			if (eq(h->bins[h->gap - 1].centroid, observation)) {
				++(h->bins[h->gap - 1].count);
				return;
			}
		}

		/* Look at the bin to the right of the gap... */
		if (h->gap != h->num_bins) {
			/* If its centroid is less than the observation, move
			 * the gap to the right and try again... */
			if (h->bins[h->gap + 1].centroid < observation) {
				h->bins[h->gap] = h->bins[h->gap + 1];
				++(h->gap);
				continue;
			}
			/* If its centroid is equal to the observation, just
			 * update its count in place. */
			if (eq(h->bins[h->gap + 1].centroid, observation)) {
				++(h->bins[h->gap + 1].count);
				return;
			}
		}

		/* If the gap is in the right place, we're ready to insert. */
		break;
	}

	/* Insert the observation into a new bin at the gap. */
	h->bins[h->gap].centroid = observation;
	h->bins[h->gap].count = 1;

	/* If the histogram isn't full yet, don't bother merging bins, just
	 * stick the gap back at the end. */
	if (h->num_bins != h->max_bins) {
		h->gap = ++(h->num_bins);
		return;
	}

	/* Find the two adjacent bins with the closest centroids and merge them.
	 * The choice whether to leave the gap on the left or right is
	 * arbitrary (we choose the left). */
	for (bin = 0; bin < h->num_bins; ++bin) {
		delta = h->bins[bin + 1].centroid - h->bins[bin].centroid;
		if (delta < min_delta) {
			min_delta = delta;
			h->gap = bin;
		}
	}
	/* The merged centroid is the weighted average of the two, and the
	 * merged count is the sum of the two. */
	h->bins[h->gap + 1].centroid =
		(h->bins[h->gap].centroid * h->bins[h->gap].count +
		 h->bins[h->gap + 1].centroid * h->bins[h->gap + 1].count) /
		(h->bins[h->gap].count + h->bins[h->gap + 1].count);
	h->bins[h->gap + 1].count += h->bins[h->gap].count;
}