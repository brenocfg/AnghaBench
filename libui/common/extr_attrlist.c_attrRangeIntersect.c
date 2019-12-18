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
struct attr {size_t end; size_t start; } ;

/* Variables and functions */

__attribute__((used)) static int attrRangeIntersect(struct attr *a, size_t *start, size_t *end)
{
	// is the range outside a entirely?
	if (*start >= a->end)
		return 0;
	if (*end < a->start)
		return 0;

	// okay, so there is an overlap
	// compute the intersection
	if (*start < a->start)
		*start = a->start;
	if (*end > a->end)
		*end = a->end;
	return 1;
}