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
struct netmap_mem_d {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NM_MTX_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NM_MTX_UNLOCK (int /*<<< orphan*/ ) ; 
 int nm_mem_assign_id_locked (struct netmap_mem_d*) ; 
 int /*<<< orphan*/  nm_mem_list_lock ; 

__attribute__((used)) static int
nm_mem_assign_id(struct netmap_mem_d *nmd)
{
	int ret;

	NM_MTX_LOCK(nm_mem_list_lock);
	ret = nm_mem_assign_id_locked(nmd);
	NM_MTX_UNLOCK(nm_mem_list_lock);

	return ret;
}