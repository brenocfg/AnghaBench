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
struct netmap_mem_d {int /*<<< orphan*/ * pools; } ;

/* Variables and functions */
 int NETMAP_POOLS_NR ; 
 int /*<<< orphan*/  NMA_LOCK_DESTROY (struct netmap_mem_d*) ; 
 int /*<<< orphan*/  netmap_destroy_obj_allocator (int /*<<< orphan*/ *) ; 
 struct netmap_mem_d nm_mem ; 
 int /*<<< orphan*/  nm_os_free (struct netmap_mem_d*) ; 

__attribute__((used)) static void
netmap_mem2_delete(struct netmap_mem_d *nmd)
{
	int i;

	for (i = 0; i < NETMAP_POOLS_NR; i++) {
	    netmap_destroy_obj_allocator(&nmd->pools[i]);
	}

	NMA_LOCK_DESTROY(nmd);
	if (nmd != &nm_mem)
		nm_os_free(nmd);
}