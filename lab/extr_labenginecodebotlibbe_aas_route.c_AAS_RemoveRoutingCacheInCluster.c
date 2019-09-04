#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* next; } ;
typedef  TYPE_1__ aas_routingcache_t ;
struct TYPE_6__ {int numareas; } ;
typedef  TYPE_2__ aas_cluster_t ;
struct TYPE_7__ {TYPE_1__*** clusterareacache; TYPE_2__* clusters; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_FreeRoutingCache (TYPE_1__*) ; 
 TYPE_3__ aasworld ; 

void AAS_RemoveRoutingCacheInCluster( int clusternum )
{
	int i;
	aas_routingcache_t *cache, *nextcache;
	aas_cluster_t *cluster;

	if (!aasworld.clusterareacache)
		return;
	cluster = &aasworld.clusters[clusternum];
	for (i = 0; i < cluster->numareas; i++)
	{
		for (cache = aasworld.clusterareacache[clusternum][i]; cache; cache = nextcache)
		{
			nextcache = cache->next;
			AAS_FreeRoutingCache(cache);
		} //end for
		aasworld.clusterareacache[clusternum][i] = NULL;
	} //end for
}