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
struct ck_rhs_map {unsigned long offset_mask; unsigned long mask; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned long
ck_rhs_map_probe_prev(struct ck_rhs_map *map, unsigned long offset,
    unsigned long probes)
{

	if (probes & map->offset_mask) {
		offset = (offset &~ map->offset_mask) + ((offset - 1) &
		    map->offset_mask);
		return offset;
	} else
		return ((offset - probes) & map->mask);
}