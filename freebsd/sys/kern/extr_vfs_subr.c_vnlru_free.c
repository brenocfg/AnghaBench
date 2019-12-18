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
struct vfsops {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnlru_free_locked (int,struct vfsops*) ; 
 int /*<<< orphan*/  vnode_free_list_mtx ; 

void
vnlru_free(int count, struct vfsops *mnt_op)
{

	mtx_lock(&vnode_free_list_mtx);
	vnlru_free_locked(count, mnt_op);
	mtx_unlock(&vnode_free_list_mtx);
}