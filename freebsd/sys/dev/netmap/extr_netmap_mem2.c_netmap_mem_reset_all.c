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
struct netmap_mem_d {int /*<<< orphan*/  flags; int /*<<< orphan*/ * pools; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETMAP_MEM_FINALIZED ; 
 int NETMAP_POOLS_NR ; 
 int NM_DEBUG_MEM ; 
 int netmap_debug ; 
 int /*<<< orphan*/  netmap_reset_obj_allocator (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nm_prinf (char*,struct netmap_mem_d*) ; 

__attribute__((used)) static void
netmap_mem_reset_all(struct netmap_mem_d *nmd)
{
	int i;

	if (netmap_debug & NM_DEBUG_MEM)
		nm_prinf("resetting %p", nmd);
	for (i = 0; i < NETMAP_POOLS_NR; i++) {
		netmap_reset_obj_allocator(&nmd->pools[i]);
	}
	nmd->flags  &= ~NETMAP_MEM_FINALIZED;
}