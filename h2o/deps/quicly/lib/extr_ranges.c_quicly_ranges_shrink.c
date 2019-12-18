#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t num_ranges; int capacity; int /*<<< orphan*/ * ranges; } ;
typedef  TYPE_1__ quicly_ranges_t ;
typedef  int /*<<< orphan*/  quicly_range_t ;

/* Variables and functions */
 int /*<<< orphan*/  MOVE (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * realloc (int /*<<< orphan*/ *,size_t) ; 

void quicly_ranges_shrink(quicly_ranges_t *ranges, size_t start, size_t end)
{
    assert(start < end);

    MOVE(ranges->ranges + start, ranges->ranges + end, ranges->num_ranges - end);
    ranges->num_ranges -= end - start;
    if (ranges->capacity > 4 && ranges->num_ranges * 3 <= ranges->capacity) {
        size_t new_capacity = ranges->capacity / 2;
        quicly_range_t *new_ranges = realloc(ranges->ranges, new_capacity * sizeof(*new_ranges));
        if (new_ranges != NULL) {
            ranges->ranges = new_ranges;
            ranges->capacity = new_capacity;
        }
    }
}