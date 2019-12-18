#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ to; scalar_t__ from; } ;
struct diff {TYPE_1__ new; TYPE_1__ old; } ;

/* Variables and functions */
 int /*<<< orphan*/  change (int,TYPE_1__*,int) ; 
 struct diff* d13 ; 
 struct diff* d23 ; 
 int duplicate (TYPE_1__*,TYPE_1__*) ; 
 int edit (struct diff*,int,int) ; 
 int /*<<< orphan*/  edscript (int) ; 
 scalar_t__ eflag ; 
 int /*<<< orphan*/  keep (int,TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
merge(int m1, int m2)
{
	struct diff *d1, *d2, *d3;
	int j, t1, t2;
	bool dup = false;

	d1 = d13;
	d2 = d23;
	j = 0;

	while ((t1 = d1 < d13 + m1) | (t2 = d2 < d23 + m2)) {
		/* first file is different from the others */
		if (!t2 || (t1 && d1->new.to < d2->new.from)) {
			/* stuff peculiar to 1st file */
			if (eflag == 0) {
				printf("====1\n");
				change(1, &d1->old, false);
				keep(2, &d1->new);
				change(3, &d1->new, false);
			}
			d1++;
			continue;
		}
		/* second file is different from others */
		if (!t1 || (t2 && d2->new.to < d1->new.from)) {
			if (eflag == 0) {
				printf("====2\n");
				keep(1, &d2->new);
				change(3, &d2->new, false);
				change(2, &d2->old, false);
			}
			d2++;
			continue;
		}
		/*
		 * Merge overlapping changes in first file
		 * this happens after extension (see below).
		 */
		if (d1 + 1 < d13 + m1 && d1->new.to >= d1[1].new.from) {
			d1[1].old.from = d1->old.from;
			d1[1].new.from = d1->new.from;
			d1++;
			continue;
		}

		/* merge overlapping changes in second */
		if (d2 + 1 < d23 + m2 && d2->new.to >= d2[1].new.from) {
			d2[1].old.from = d2->old.from;
			d2[1].new.from = d2->new.from;
			d2++;
			continue;
		}
		/* stuff peculiar to third file or different in all */
		if (d1->new.from == d2->new.from && d1->new.to == d2->new.to) {
			dup = duplicate(&d1->old, &d2->old);
			/*
			 * dup = 0 means all files differ
			 * dup = 1 means files 1 and 2 identical
			 */
			if (eflag == 0) {
				printf("====%s\n", dup ? "3" : "");
				change(1, &d1->old, dup);
				change(2, &d2->old, false);
				d3 = d1->old.to > d1->old.from ? d1 : d2;
				change(3, &d3->new, false);
			} else
				j = edit(d1, dup, j);
			d1++;
			d2++;
			continue;
		}
		/*
		 * Overlapping changes from file 1 and 2; extend changes
		 * appropriately to make them coincide.
		 */
		if (d1->new.from < d2->new.from) {
			d2->old.from -= d2->new.from - d1->new.from;
			d2->new.from = d1->new.from;
		} else if (d2->new.from < d1->new.from) {
			d1->old.from -= d1->new.from - d2->new.from;
			d1->new.from = d2->new.from;
		}
		if (d1->new.to > d2->new.to) {
			d2->old.to += d1->new.to - d2->new.to;
			d2->new.to = d1->new.to;
		} else if (d2->new.to > d1->new.to) {
			d1->old.to += d2->new.to - d1->new.to;
			d1->new.to = d2->new.to;
		}
	}
	if (eflag)
		edscript(j);
}