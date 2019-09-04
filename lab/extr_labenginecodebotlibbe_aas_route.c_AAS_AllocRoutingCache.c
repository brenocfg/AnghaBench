#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned char* reachabilities; int size; } ;
typedef  TYPE_1__ aas_routingcache_t ;

/* Variables and functions */
 scalar_t__ GetClearedMemory (int) ; 
 int routingcachesize ; 

aas_routingcache_t *AAS_AllocRoutingCache(int numtraveltimes)
{
	aas_routingcache_t *cache;
	int size;

	//
	size = sizeof(aas_routingcache_t)
						+ numtraveltimes * sizeof(unsigned short int)
						+ numtraveltimes * sizeof(unsigned char);
	//
	routingcachesize += size;
	//
	cache = (aas_routingcache_t *) GetClearedMemory(size);
	cache->reachabilities = (unsigned char *) cache + sizeof(aas_routingcache_t)
								+ numtraveltimes * sizeof(unsigned short int);
	cache->size = size;
	return cache;
}