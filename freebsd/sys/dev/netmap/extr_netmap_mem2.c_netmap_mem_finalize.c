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
struct netmap_mem_d {int lasterr; int /*<<< orphan*/ * pools; TYPE_1__* ops; int /*<<< orphan*/  active; } ;
struct netmap_adapter {scalar_t__ pdev; } ;
struct TYPE_2__ {int (* nmd_finalize ) (struct netmap_mem_d*) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 size_t NETMAP_BUF_POOL ; 
 int /*<<< orphan*/  NMA_LOCK (struct netmap_mem_d*) ; 
 int /*<<< orphan*/  NMA_UNLOCK (struct netmap_mem_d*) ; 
 scalar_t__ netmap_mem_config (struct netmap_mem_d*) ; 
 int /*<<< orphan*/  netmap_mem_deref (struct netmap_mem_d*,struct netmap_adapter*) ; 
 int netmap_mem_map (int /*<<< orphan*/ *,struct netmap_adapter*) ; 
 scalar_t__ nm_mem_assign_group (struct netmap_mem_d*,scalar_t__) ; 
 int stub1 (struct netmap_mem_d*) ; 

int
netmap_mem_finalize(struct netmap_mem_d *nmd, struct netmap_adapter *na)
{
	int lasterr = 0;
	if (nm_mem_assign_group(nmd, na->pdev) < 0) {
		return ENOMEM;
	}

	NMA_LOCK(nmd);

	if (netmap_mem_config(nmd))
		goto out;

	nmd->active++;

	nmd->lasterr = nmd->ops->nmd_finalize(nmd);

	if (!nmd->lasterr && na->pdev) {
		nmd->lasterr = netmap_mem_map(&nmd->pools[NETMAP_BUF_POOL], na);
	}

out:
	lasterr = nmd->lasterr;
	NMA_UNLOCK(nmd);

	if (lasterr)
		netmap_mem_deref(nmd, na);

	return lasterr;
}