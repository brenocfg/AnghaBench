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
struct netmap_mem_d {scalar_t__ refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  NM_DBG_REFC (struct netmap_mem_d*,char const*,int) ; 
 int /*<<< orphan*/  NM_MTX_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NM_MTX_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netmap_mem_delete (struct netmap_mem_d*) ; 
 int /*<<< orphan*/  nm_mem_list_lock ; 
 int /*<<< orphan*/  nm_mem_release_id (struct netmap_mem_d*) ; 

void
__netmap_mem_put(struct netmap_mem_d *nmd, const char *func, int line)
{
	int last;
	NM_MTX_LOCK(nm_mem_list_lock);
	last = (--nmd->refcount == 0);
	if (last)
		nm_mem_release_id(nmd);
	NM_DBG_REFC(nmd, func, line);
	NM_MTX_UNLOCK(nm_mem_list_lock);
	if (last)
		netmap_mem_delete(nmd);
}