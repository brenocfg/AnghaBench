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
struct netmap_mem_d {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  NM_DBG_REFC (struct netmap_mem_d*,char const*,int) ; 
 int /*<<< orphan*/  NM_MTX_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NM_MTX_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nm_mem_list_lock ; 

struct netmap_mem_d *
__netmap_mem_get(struct netmap_mem_d *nmd, const char *func, int line)
{
	NM_MTX_LOCK(nm_mem_list_lock);
	nmd->refcount++;
	NM_DBG_REFC(nmd, func, line);
	NM_MTX_UNLOCK(nm_mem_list_lock);
	return nmd;
}