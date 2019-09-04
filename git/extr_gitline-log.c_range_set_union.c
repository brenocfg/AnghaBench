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
struct range_set {scalar_t__ nr; struct range* ranges; } ;
struct range {scalar_t__ start; scalar_t__ end; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  range_set_grow (struct range_set*,int) ; 

__attribute__((used)) static void range_set_union(struct range_set *out,
			     struct range_set *a, struct range_set *b)
{
	unsigned int i = 0, j = 0;
	struct range *ra = a->ranges;
	struct range *rb = b->ranges;
	/* cannot make an alias of out->ranges: it may change during grow */

	assert(out->nr == 0);
	while (i < a->nr || j < b->nr) {
		struct range *new_range;
		if (i < a->nr && j < b->nr) {
			if (ra[i].start < rb[j].start)
				new_range = &ra[i++];
			else if (ra[i].start > rb[j].start)
				new_range = &rb[j++];
			else if (ra[i].end < rb[j].end)
				new_range = &ra[i++];
			else
				new_range = &rb[j++];
		} else if (i < a->nr)      /* b exhausted */
			new_range = &ra[i++];
		else                       /* a exhausted */
			new_range = &rb[j++];
		if (new_range->start == new_range->end)
			; /* empty range */
		else if (!out->nr || out->ranges[out->nr-1].end < new_range->start) {
			range_set_grow(out, 1);
			out->ranges[out->nr].start = new_range->start;
			out->ranges[out->nr].end = new_range->end;
			out->nr++;
		} else if (out->ranges[out->nr-1].end < new_range->end) {
			out->ranges[out->nr-1].end = new_range->end;
		}
	}
}