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
struct netmap_mem_d {int flags; int lasterr; int nm_totalsize; TYPE_1__* pools; } ;
struct TYPE_2__ {int memtotal; int /*<<< orphan*/  objfree; } ;

/* Variables and functions */
 size_t NETMAP_BUF_POOL ; 
 size_t NETMAP_IF_POOL ; 
 int NETMAP_MEM_FINALIZED ; 
 int NETMAP_POOLS_NR ; 
 size_t NETMAP_RING_POOL ; 
 int netmap_finalize_obj_allocator (TYPE_1__*) ; 
 int netmap_mem_init_bitmaps (struct netmap_mem_d*) ; 
 int /*<<< orphan*/  netmap_mem_reset_all (struct netmap_mem_d*) ; 
 scalar_t__ netmap_verbose ; 
 int /*<<< orphan*/  nm_prinf (char*,int,...) ; 

__attribute__((used)) static int
netmap_mem_finalize_all(struct netmap_mem_d *nmd)
{
	int i;
	if (nmd->flags & NETMAP_MEM_FINALIZED)
		return 0;
	nmd->lasterr = 0;
	nmd->nm_totalsize = 0;
	for (i = 0; i < NETMAP_POOLS_NR; i++) {
		nmd->lasterr = netmap_finalize_obj_allocator(&nmd->pools[i]);
		if (nmd->lasterr)
			goto error;
		nmd->nm_totalsize += nmd->pools[i].memtotal;
	}
	nmd->lasterr = netmap_mem_init_bitmaps(nmd);
	if (nmd->lasterr)
		goto error;

	nmd->flags |= NETMAP_MEM_FINALIZED;

	if (netmap_verbose)
		nm_prinf("interfaces %zd KB, rings %zd KB, buffers %zd MB",
		    nmd->pools[NETMAP_IF_POOL].memtotal >> 10,
		    nmd->pools[NETMAP_RING_POOL].memtotal >> 10,
		    nmd->pools[NETMAP_BUF_POOL].memtotal >> 20);

	if (netmap_verbose)
		nm_prinf("Free buffers: %d", nmd->pools[NETMAP_BUF_POOL].objfree);


	return 0;
error:
	netmap_mem_reset_all(nmd);
	return nmd->lasterr;
}