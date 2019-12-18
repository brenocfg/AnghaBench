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
typedef  int /*<<< orphan*/  u_int ;
struct vnode {int /*<<< orphan*/  v_hash; int /*<<< orphan*/  v_mount; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ ,struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v_hashlist ; 
 int /*<<< orphan*/  vfs_hash_bucket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_hash_lock ; 

void
vfs_hash_rehash(struct vnode *vp, u_int hash)
{

	rw_wlock(&vfs_hash_lock);
	LIST_REMOVE(vp, v_hashlist);
	LIST_INSERT_HEAD(vfs_hash_bucket(vp->v_mount, hash), vp, v_hashlist);
	vp->v_hash = hash;
	rw_wunlock(&vfs_hash_lock);
}