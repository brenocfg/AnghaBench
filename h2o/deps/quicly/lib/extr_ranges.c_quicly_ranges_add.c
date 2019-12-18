#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_7__ {int num_ranges; TYPE_1__* ranges; } ;
typedef  TYPE_2__ quicly_ranges_t ;
struct TYPE_6__ {scalar_t__ end; scalar_t__ start; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int insert_at (TYPE_2__*,scalar_t__,scalar_t__,size_t) ; 
 int merge_update (TYPE_2__*,scalar_t__,scalar_t__,size_t,size_t) ; 

int quicly_ranges_add(quicly_ranges_t *ranges, uint64_t start, uint64_t end)
{
    size_t slot, end_slot;

    assert(start <= end);

    if (start == end)
        return 0;

    if (ranges->num_ranges == 0) {
        return insert_at(ranges, start, end, 0);
    } else if (ranges->ranges[ranges->num_ranges - 1].end < start) {
        return insert_at(ranges, start, end, ranges->num_ranges);
    }

    /* find the slot that should contain `end` */
    for (slot = ranges->num_ranges - 1;; --slot) {
        if (ranges->ranges[slot].start <= end)
            break;
        if (slot == 0)
            return insert_at(ranges, start, end, 0);
    }
    end_slot = slot;

    /* find the slot that should contain `start` */
    do {
        if (ranges->ranges[slot].end == start) {
            return merge_update(ranges, start, end, slot, end_slot);
        } else if (ranges->ranges[slot].end < start) {
            if (slot++ == end_slot) {
                return insert_at(ranges, start, end, slot);
            } else {
                return merge_update(ranges, start, end, slot, end_slot);
            }
        }
    } while (slot-- != 0);

    return merge_update(ranges, start, end, 0, end_slot);
}