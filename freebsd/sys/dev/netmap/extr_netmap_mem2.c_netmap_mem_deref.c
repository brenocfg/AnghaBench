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
struct netmap_mem_d {int active; int nm_grp; scalar_t__ lasterr; TYPE_1__* ops; int /*<<< orphan*/ * pools; } ;
struct netmap_adapter {scalar_t__ active_fds; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* nmd_deref ) (struct netmap_mem_d*) ;} ;

/* Variables and functions */
 size_t NETMAP_BUF_POOL ; 
 int /*<<< orphan*/  NMA_LOCK (struct netmap_mem_d*) ; 
 int /*<<< orphan*/  NMA_UNLOCK (struct netmap_mem_d*) ; 
 int /*<<< orphan*/  netmap_mem_init_bitmaps (struct netmap_mem_d*) ; 
 int /*<<< orphan*/  netmap_mem_unmap (int /*<<< orphan*/ *,struct netmap_adapter*) ; 
 int /*<<< orphan*/  stub1 (struct netmap_mem_d*) ; 

int
netmap_mem_deref(struct netmap_mem_d *nmd, struct netmap_adapter *na)
{
	int last_user = 0;
	NMA_LOCK(nmd);
	if (na->active_fds <= 0)
		netmap_mem_unmap(&nmd->pools[NETMAP_BUF_POOL], na);
	if (nmd->active == 1) {
		last_user = 1;
		/*
		 * Reset the allocator when it falls out of use so that any
		 * pool resources leaked by unclean application exits are
		 * reclaimed.
		 */
		netmap_mem_init_bitmaps(nmd);
	}
	nmd->ops->nmd_deref(nmd);

	nmd->active--;
	if (last_user) {
		nmd->nm_grp = -1;
		nmd->lasterr = 0;
	}

	NMA_UNLOCK(nmd);
	return last_user;
}