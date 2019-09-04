#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* time_next; struct TYPE_4__* time_prev; } ;
typedef  TYPE_1__ aas_routingcache_t ;
struct TYPE_5__ {TYPE_1__* newestcache; TYPE_1__* oldestcache; } ;

/* Variables and functions */
 TYPE_2__ aasworld ; 

void AAS_LinkCache(aas_routingcache_t *cache)
{
	if (aasworld.newestcache)
	{
		aasworld.newestcache->time_next = cache;
		cache->time_prev = aasworld.newestcache;
	} //end if
	else
	{
		aasworld.oldestcache = cache;
		cache->time_prev = NULL;
	} //end else
	cache->time_next = NULL;
	aasworld.newestcache = cache;
}