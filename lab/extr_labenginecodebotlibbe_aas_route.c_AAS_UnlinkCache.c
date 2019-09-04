#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* time_prev; TYPE_2__* time_next; } ;
typedef  TYPE_3__ aas_routingcache_t ;
struct TYPE_9__ {TYPE_2__* oldestcache; TYPE_1__* newestcache; } ;
struct TYPE_7__ {TYPE_1__* time_prev; } ;
struct TYPE_6__ {TYPE_2__* time_next; } ;

/* Variables and functions */
 TYPE_4__ aasworld ; 

void AAS_UnlinkCache(aas_routingcache_t *cache)
{
	if (cache->time_next) cache->time_next->time_prev = cache->time_prev;
	else aasworld.newestcache = cache->time_prev;
	if (cache->time_prev) cache->time_prev->time_next = cache->time_next;
	else aasworld.oldestcache = cache->time_next;
	cache->time_next = NULL;
	cache->time_prev = NULL;
}