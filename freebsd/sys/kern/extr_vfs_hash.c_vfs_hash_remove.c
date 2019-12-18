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
struct vnode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v_hashlist ; 
 int /*<<< orphan*/  vfs_hash_lock ; 

void
vfs_hash_remove(struct vnode *vp)
{

	rw_wlock(&vfs_hash_lock);
	LIST_REMOVE(vp, v_hashlist);
	rw_wunlock(&vfs_hash_lock);
}