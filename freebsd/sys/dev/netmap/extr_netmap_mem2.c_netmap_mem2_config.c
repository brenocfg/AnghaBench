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
struct netmap_mem_d {int flags; int lasterr; TYPE_1__* params; int /*<<< orphan*/ * pools; } ;
struct TYPE_2__ {int /*<<< orphan*/  size; int /*<<< orphan*/  num; } ;

/* Variables and functions */
 int NETMAP_MEM_FINALIZED ; 
 int NETMAP_POOLS_NR ; 
 int netmap_config_obj_allocator (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netmap_mem_params_changed (TYPE_1__*) ; 
 int /*<<< orphan*/  netmap_reset_obj_allocator (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nm_prdis (char*) ; 

__attribute__((used)) static int
netmap_mem2_config(struct netmap_mem_d *nmd)
{
	int i;

	if (!netmap_mem_params_changed(nmd->params))
		goto out;

	nm_prdis("reconfiguring");

	if (nmd->flags & NETMAP_MEM_FINALIZED) {
		/* reset previous allocation */
		for (i = 0; i < NETMAP_POOLS_NR; i++) {
			netmap_reset_obj_allocator(&nmd->pools[i]);
		}
		nmd->flags &= ~NETMAP_MEM_FINALIZED;
	}

	for (i = 0; i < NETMAP_POOLS_NR; i++) {
		nmd->lasterr = netmap_config_obj_allocator(&nmd->pools[i],
				nmd->params[i].num, nmd->params[i].size);
		if (nmd->lasterr)
			goto out;
	}

out:

	return nmd->lasterr;
}