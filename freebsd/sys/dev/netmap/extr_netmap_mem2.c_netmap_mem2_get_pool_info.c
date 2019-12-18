#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct netmap_mem_d {int flags; TYPE_1__* pools; } ;
struct TYPE_2__ {size_t _clustsize; size_t numclusters; } ;

/* Variables and functions */
 int NETMAP_MEM_FINALIZED ; 
 size_t NETMAP_POOLS_NR ; 

int
netmap_mem2_get_pool_info(struct netmap_mem_d* nmd, u_int pool, u_int *clustsize, u_int *numclusters)
{
	if (!nmd || !clustsize || !numclusters || pool >= NETMAP_POOLS_NR)
		return 1; /* invalid arguments */
	// NMA_LOCK_ASSERT(nmd);
	if (!(nmd->flags & NETMAP_MEM_FINALIZED)) {
		*clustsize = *numclusters = 0;
		return 1; /* not ready yet */
	}
	*clustsize = nmd->pools[pool]._clustsize;
	*numclusters = nmd->pools[pool].numclusters;
	return 0; /* success */
}