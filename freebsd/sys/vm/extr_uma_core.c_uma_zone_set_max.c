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
typedef  TYPE_1__* uma_zone_t ;
struct uma_bucket_zone {int ubz_entries; } ;
struct TYPE_5__ {int uz_count_max; int uz_count; int uz_count_min; int uz_max_items; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZONE_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  ZONE_UNLOCK (TYPE_1__*) ; 
 struct uma_bucket_zone* bucket_zones ; 
 int mp_ncpus ; 

int
uma_zone_set_max(uma_zone_t zone, int nitems)
{
	struct uma_bucket_zone *ubz;

	/*
	 * If limit is very low we may need to limit how
	 * much items are allowed in CPU caches.
	 */
	ubz = &bucket_zones[0];
	for (; ubz->ubz_entries != 0; ubz++)
		if (ubz->ubz_entries * 2 * mp_ncpus > nitems)
			break;
	if (ubz == &bucket_zones[0])
		nitems = ubz->ubz_entries * 2 * mp_ncpus;
	else
		ubz--;

	ZONE_LOCK(zone);
	zone->uz_count_max = zone->uz_count = ubz->ubz_entries;
	if (zone->uz_count_min > zone->uz_count_max)
		zone->uz_count_min = zone->uz_count_max;
	zone->uz_max_items = nitems;
	ZONE_UNLOCK(zone);

	return (nitems);
}