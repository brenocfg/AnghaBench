#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_6__ {TYPE_1__* ranges; } ;
typedef  TYPE_2__ quicly_ranges_t ;
struct TYPE_5__ {scalar_t__ start; scalar_t__ end; } ;

/* Variables and functions */
 int /*<<< orphan*/  quicly_ranges_shrink (TYPE_2__*,size_t,size_t) ; 

__attribute__((used)) static inline int merge_update(quicly_ranges_t *ranges, uint64_t start, uint64_t end, size_t slot, size_t end_slot)
{
    if (start < ranges->ranges[slot].start)
        ranges->ranges[slot].start = start;
    ranges->ranges[slot].end = end < ranges->ranges[end_slot].end ? ranges->ranges[end_slot].end : end;

    if (slot != end_slot)
        quicly_ranges_shrink(ranges, slot + 1, end_slot + 1);

    return 0;
}