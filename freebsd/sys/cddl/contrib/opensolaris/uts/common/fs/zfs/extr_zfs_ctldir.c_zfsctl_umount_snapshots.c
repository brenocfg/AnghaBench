#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  z_os; int /*<<< orphan*/ * z_ctldir; } ;
typedef  TYPE_1__ zfsvfs_t ;
struct TYPE_10__ {struct mount* v_mountedhere; } ;
typedef  TYPE_2__ vnode_t ;
struct TYPE_11__ {TYPE_1__* vfs_data; } ;
typedef  TYPE_3__ vfs_t ;
typedef  scalar_t__ uint64_t ;
struct mount {int dummy; } ;
typedef  int /*<<< orphan*/  snapname ;
typedef  int /*<<< orphan*/  sfs_node_t ;
typedef  int /*<<< orphan*/  cred_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int ENOENT ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  KASSERT_IMPLY (int,int,char*) ; 
 int /*<<< orphan*/  LK_EXCLUSIVE ; 
 int MS_FORCE ; 
 int /*<<< orphan*/  ZFSCTL_INO_SNAPDIR ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  dmu_objset_pool (int /*<<< orphan*/ ) ; 
 int dmu_snapshot_list_next (int /*<<< orphan*/ ,int,char*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int dounmount (struct mount*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_pool_config_enter (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_pool_config_exit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sfs_vnode_get (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,TYPE_2__**) ; 
 int /*<<< orphan*/  vfs_ref (struct mount*) ; 
 int /*<<< orphan*/  vput (TYPE_2__*) ; 
 int vrefcnt (TYPE_2__*) ; 

int
zfsctl_umount_snapshots(vfs_t *vfsp, int fflags, cred_t *cr)
{
	char snapname[ZFS_MAX_DATASET_NAME_LEN];
	zfsvfs_t *zfsvfs = vfsp->vfs_data;
	struct mount *mp;
	vnode_t *dvp;
	vnode_t *vp;
	sfs_node_t *node;
	sfs_node_t *snap;
	uint64_t cookie;
	int error;

	ASSERT(zfsvfs->z_ctldir != NULL);

	cookie = 0;
	for (;;) {
		uint64_t id;

		dsl_pool_config_enter(dmu_objset_pool(zfsvfs->z_os), FTAG);
		error = dmu_snapshot_list_next(zfsvfs->z_os, sizeof(snapname),
		    snapname, &id, &cookie, NULL);
		dsl_pool_config_exit(dmu_objset_pool(zfsvfs->z_os), FTAG);
		if (error != 0) {
			if (error == ENOENT)
				error = 0;
			break;
		}

		for (;;) {
			error = sfs_vnode_get(vfsp, LK_EXCLUSIVE,
			    ZFSCTL_INO_SNAPDIR, id, &vp);
			if (error != 0 || vp == NULL)
				break;

			mp = vp->v_mountedhere;

			/*
			 * v_mountedhere being NULL means that the
			 * (uncovered) vnode is in a transient state
			 * (mounting or unmounting), so loop until it
			 * settles down.
			 */
			if (mp != NULL)
				break;
			vput(vp);
		}
		if (error != 0)
			break;
		if (vp == NULL)
			continue;	/* no mountpoint, nothing to do */

		/*
		 * The mount-point vnode is kept locked to avoid spurious EBUSY
		 * from a concurrent umount.
		 * The vnode lock must have recursive locking enabled.
		 */
		vfs_ref(mp);
		error = dounmount(mp, fflags, curthread);
		KASSERT_IMPLY(error == 0, vrefcnt(vp) == 1,
		    ("extra references after unmount"));
		vput(vp);
		if (error != 0)
			break;
	}
	KASSERT_IMPLY((fflags & MS_FORCE) != 0, error == 0,
	    ("force unmounting failed"));
	return (error);
}