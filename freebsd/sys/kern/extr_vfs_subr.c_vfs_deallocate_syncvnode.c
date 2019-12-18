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
struct mount {struct vnode* mnt_syncer; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sync_mtx ; 
 int /*<<< orphan*/  vrele (struct vnode*) ; 

void
vfs_deallocate_syncvnode(struct mount *mp)
{
	struct vnode *vp;

	mtx_lock(&sync_mtx);
	vp = mp->mnt_syncer;
	if (vp != NULL)
		mp->mnt_syncer = NULL;
	mtx_unlock(&sync_mtx);
	if (vp != NULL)
		vrele(vp);
}