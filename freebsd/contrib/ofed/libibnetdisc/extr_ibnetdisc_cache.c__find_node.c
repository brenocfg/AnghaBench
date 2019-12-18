#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_7__ {TYPE_1__* node; struct TYPE_7__* htnext; } ;
typedef  TYPE_2__ ibnd_node_cache_t ;
struct TYPE_8__ {TYPE_2__** nodescachetbl; } ;
typedef  TYPE_3__ ibnd_fabric_cache_t ;
struct TYPE_6__ {scalar_t__ guid; } ;

/* Variables and functions */
 int HASHGUID (scalar_t__) ; 
 int HTSZ ; 

__attribute__((used)) static ibnd_node_cache_t *_find_node(ibnd_fabric_cache_t * fabric_cache,
				     uint64_t guid)
{
	int hash_indx = HASHGUID(guid) % HTSZ;
	ibnd_node_cache_t *node_cache;

	for (node_cache = fabric_cache->nodescachetbl[hash_indx];
	     node_cache; node_cache = node_cache->htnext) {
		if (node_cache->node->guid == guid)
			return node_cache;
	}

	return NULL;
}