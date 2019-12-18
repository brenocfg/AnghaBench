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
struct TYPE_5__ {int uz_max_items; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZONE_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  ZONE_UNLOCK (TYPE_1__*) ; 

int
uma_zone_get_max(uma_zone_t zone)
{
	int nitems;

	ZONE_LOCK(zone);
	nitems = zone->uz_max_items;
	ZONE_UNLOCK(zone);

	return (nitems);
}