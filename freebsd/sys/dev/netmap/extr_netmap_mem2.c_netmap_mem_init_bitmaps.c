#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct netmap_obj_pool {int objfree; unsigned int* bitmap; int /*<<< orphan*/  name; } ;
struct netmap_mem_d {struct netmap_obj_pool* pools; } ;

/* Variables and functions */
 int ENOMEM ; 
 size_t NETMAP_BUF_POOL ; 
 int NETMAP_POOLS_NR ; 
 int netmap_init_obj_allocator_bitmap (struct netmap_obj_pool*) ; 
 int /*<<< orphan*/  nm_prerr (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
netmap_mem_init_bitmaps(struct netmap_mem_d *nmd)
{
	int i, error = 0;

	for (i = 0; i < NETMAP_POOLS_NR; i++) {
		struct netmap_obj_pool *p = &nmd->pools[i];

		error = netmap_init_obj_allocator_bitmap(p);
		if (error)
			return error;
	}

	/*
	 * buffers 0 and 1 are reserved
	 */
	if (nmd->pools[NETMAP_BUF_POOL].objfree < 2) {
		nm_prerr("%s: not enough buffers", nmd->pools[NETMAP_BUF_POOL].name);
		return ENOMEM;
	}

	nmd->pools[NETMAP_BUF_POOL].objfree -= 2;
	if (nmd->pools[NETMAP_BUF_POOL].bitmap) {
		/* XXX This check is a workaround that prevents a
		 * NULL pointer crash which currently happens only
		 * with ptnetmap guests.
		 * Removed shared-info --> is the bug still there? */
		nmd->pools[NETMAP_BUF_POOL].bitmap[0] = ~3U;
	}
	return 0;
}