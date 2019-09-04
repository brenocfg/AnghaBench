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
struct TYPE_8__ {struct TYPE_8__* next; } ;
typedef  TYPE_3__ aas_routingcache_t ;
struct TYPE_9__ {int numareas; TYPE_3__** portalcache; TYPE_1__* portals; TYPE_2__* areasettings; } ;
struct TYPE_7__ {int cluster; } ;
struct TYPE_6__ {int frontcluster; int backcluster; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_FreeRoutingCache (TYPE_3__*) ; 
 int /*<<< orphan*/  AAS_RemoveRoutingCacheInCluster (int) ; 
 TYPE_4__ aasworld ; 

void AAS_RemoveRoutingCacheUsingArea( int areanum )
{
	int i, clusternum;
	aas_routingcache_t *cache, *nextcache;

	clusternum = aasworld.areasettings[areanum].cluster;
	if (clusternum > 0)
	{
		//remove all the cache in the cluster the area is in
		AAS_RemoveRoutingCacheInCluster( clusternum );
	} //end if
	else
	{
		// if this is a portal remove all cache in both the front and back cluster
		AAS_RemoveRoutingCacheInCluster( aasworld.portals[-clusternum].frontcluster );
		AAS_RemoveRoutingCacheInCluster( aasworld.portals[-clusternum].backcluster );
	} //end else
	// remove all portal cache
	for (i = 0; i < aasworld.numareas; i++)
	{
		//refresh portal cache
		for (cache = aasworld.portalcache[i]; cache; cache = nextcache)
		{
			nextcache = cache->next;
			AAS_FreeRoutingCache(cache);
		} //end for
		aasworld.portalcache[i] = NULL;
	} //end for
}