#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/ * z_ctldir; } ;
typedef  TYPE_2__ zfsvfs_t ;
struct TYPE_12__ {TYPE_1__* v_mountedhere; } ;
typedef  TYPE_3__ vnode_t ;
struct TYPE_13__ {TYPE_2__* vfs_data; } ;
typedef  TYPE_4__ vfs_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct mount {int dummy; } ;
struct TYPE_10__ {TYPE_2__* mnt_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  LK_EXCLUSIVE ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZFSCTL_INO_SNAPDIR ; 
 int sfs_vnode_get (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__**) ; 
 int /*<<< orphan*/  vput (TYPE_3__*) ; 

int
zfsctl_lookup_objset(vfs_t *vfsp, uint64_t objsetid, zfsvfs_t **zfsvfsp)
{
	struct mount *mp;
	zfsvfs_t *zfsvfs = vfsp->vfs_data;
	vnode_t *vp;
	int error;

	ASSERT(zfsvfs->z_ctldir != NULL);
	*zfsvfsp = NULL;
	error = sfs_vnode_get(vfsp, LK_EXCLUSIVE,
	    ZFSCTL_INO_SNAPDIR, objsetid, &vp);
	if (error == 0 && vp != NULL) {
		/*
		 * XXX Probably need to at least reference, if not busy, the mp.
		 */
		if (vp->v_mountedhere != NULL)
			*zfsvfsp = vp->v_mountedhere->mnt_data;
		vput(vp);
	}
	if (*zfsvfsp == NULL)
		return (SET_ERROR(EINVAL));
	return (0);
}