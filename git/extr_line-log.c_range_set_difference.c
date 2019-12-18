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
struct range_set {unsigned int nr; TYPE_1__* ranges; } ;
struct TYPE_2__ {long start; long end; } ;

/* Variables and functions */
 int /*<<< orphan*/  range_set_append (struct range_set*,long,long) ; 

__attribute__((used)) static void range_set_difference(struct range_set *out,
				  struct range_set *a, struct range_set *b)
{
	unsigned int i, j =  0;
	for (i = 0; i < a->nr; i++) {
		long start = a->ranges[i].start;
		long end = a->ranges[i].end;
		while (start < end) {
			while (j < b->nr && start >= b->ranges[j].end)
				/*
				 * a:         |-------
				 * b: ------|
				 */
				j++;
			if (j >= b->nr || end < b->ranges[j].start) {
				/*
				 * b exhausted, or
				 * a:  ----|
				 * b:         |----
				 */
				range_set_append(out, start, end);
				break;
			}
			if (start >= b->ranges[j].start) {
				/*
				 * a:     |--????
				 * b: |------|
				 */
				start = b->ranges[j].end;
			} else if (end > b->ranges[j].start) {
				/*
				 * a: |-----|
				 * b:    |--?????
				 */
				if (start < b->ranges[j].start)
					range_set_append(out, start, b->ranges[j].start);
				start = b->ranges[j].end;
			}
		}
	}
}