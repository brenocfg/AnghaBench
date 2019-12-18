#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  aas_routingcache_t ;
struct TYPE_4__ {int numclusters; TYPE_1__* clusters; int /*<<< orphan*/ *** clusterareacache; } ;
struct TYPE_3__ {int numareas; } ;

/* Variables and functions */
 scalar_t__ GetClearedMemory (int) ; 
 TYPE_2__ aasworld ; 

void AAS_InitClusterAreaCache(void)
{
	int i, size;
	char *ptr;

	//
	for (size = 0, i = 0; i < aasworld.numclusters; i++)
	{
		size += aasworld.clusters[i].numareas;
	} //end for
	//two dimensional array with pointers for every cluster to routing cache
	//for every area in that cluster
	ptr = (char *) GetClearedMemory(
				aasworld.numclusters * sizeof(aas_routingcache_t **) +
				size * sizeof(aas_routingcache_t *));
	aasworld.clusterareacache = (aas_routingcache_t ***) ptr;
	ptr += aasworld.numclusters * sizeof(aas_routingcache_t **);
	for (i = 0; i < aasworld.numclusters; i++)
	{
		aasworld.clusterareacache[i] = (aas_routingcache_t **) ptr;
		ptr += aasworld.clusters[i].numareas * sizeof(aas_routingcache_t *);
	} //end for
}