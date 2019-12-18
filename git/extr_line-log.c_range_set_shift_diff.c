#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct range_set {unsigned int nr; struct range* ranges; } ;
struct range {scalar_t__ start; scalar_t__ end; } ;
struct TYPE_4__ {unsigned int nr; struct range* ranges; } ;
struct TYPE_3__ {struct range* ranges; } ;
struct diff_ranges {TYPE_2__ target; TYPE_1__ parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  range_set_append (struct range_set*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void range_set_shift_diff(struct range_set *out,
				 struct range_set *rs,
				 struct diff_ranges *diff)
{
	unsigned int i, j = 0;
	long offset = 0;
	struct range *src = rs->ranges;
	struct range *target = diff->target.ranges;
	struct range *parent = diff->parent.ranges;

	for (i = 0; i < rs->nr; i++) {
		while (j < diff->target.nr && src[i].start >= target[j].start) {
			offset += (parent[j].end-parent[j].start)
				- (target[j].end-target[j].start);
			j++;
		}
		range_set_append(out, src[i].start+offset, src[i].end+offset);
	}
}