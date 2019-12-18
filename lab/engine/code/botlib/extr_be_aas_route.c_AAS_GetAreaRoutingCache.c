#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int travelflags; int cluster; int areanum; int starttraveltime; int /*<<< orphan*/  type; int /*<<< orphan*/  time; struct TYPE_12__* prev; struct TYPE_12__* next; int /*<<< orphan*/  origin; } ;
typedef  TYPE_3__ aas_routingcache_t ;
struct TYPE_13__ {TYPE_3__*** clusterareacache; TYPE_2__* areas; TYPE_1__* clusters; } ;
struct TYPE_11__ {int /*<<< orphan*/  center; } ;
struct TYPE_10__ {int /*<<< orphan*/  numreachabilityareas; } ;

/* Variables and functions */
 TYPE_3__* AAS_AllocRoutingCache (int /*<<< orphan*/ ) ; 
 int AAS_ClusterAreaNum (int,int) ; 
 int /*<<< orphan*/  AAS_LinkCache (TYPE_3__*) ; 
 int /*<<< orphan*/  AAS_RoutingTime () ; 
 int /*<<< orphan*/  AAS_UnlinkCache (TYPE_3__*) ; 
 int /*<<< orphan*/  AAS_UpdateAreaRoutingCache (TYPE_3__*) ; 
 int /*<<< orphan*/  CACHETYPE_AREA ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__ aasworld ; 

aas_routingcache_t *AAS_GetAreaRoutingCache(int clusternum, int areanum, int travelflags)
{
	int clusterareanum;
	aas_routingcache_t *cache, *clustercache;

	//number of the area in the cluster
	clusterareanum = AAS_ClusterAreaNum(clusternum, areanum);
	//pointer to the cache for the area in the cluster
	clustercache = aasworld.clusterareacache[clusternum][clusterareanum];
	//find the cache without undesired travel flags
	for (cache = clustercache; cache; cache = cache->next)
	{
		//if there aren't used any undesired travel types for the cache
		if (cache->travelflags == travelflags) break;
	} //end for
	//if there was no cache
	if (!cache)
	{
		cache = AAS_AllocRoutingCache(aasworld.clusters[clusternum].numreachabilityareas);
		cache->cluster = clusternum;
		cache->areanum = areanum;
		VectorCopy(aasworld.areas[areanum].center, cache->origin);
		cache->starttraveltime = 1;
		cache->travelflags = travelflags;
		cache->prev = NULL;
		cache->next = clustercache;
		if (clustercache) clustercache->prev = cache;
		aasworld.clusterareacache[clusternum][clusterareanum] = cache;
		AAS_UpdateAreaRoutingCache(cache);
	} //end if
	else
	{
		AAS_UnlinkCache(cache);
	} //end else
	//the cache has been accessed
	cache->time = AAS_RoutingTime();
	cache->type = CACHETYPE_AREA;
	AAS_LinkCache(cache);
	return cache;
}