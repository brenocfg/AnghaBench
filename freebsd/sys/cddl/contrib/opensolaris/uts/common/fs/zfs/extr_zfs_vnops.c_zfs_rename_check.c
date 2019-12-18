#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ z_id; int /*<<< orphan*/  z_sa_hdl; int /*<<< orphan*/  z_unlinked; TYPE_2__* z_zfsvfs; } ;
typedef  TYPE_1__ znode_t ;
struct TYPE_11__ {scalar_t__ z_root; int /*<<< orphan*/  z_os; } ;
typedef  TYPE_2__ zfsvfs_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  parent ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  EINVAL ; 
 int ENOTDIR ; 
 int /*<<< orphan*/  SA_ZPL_PARENT (TYPE_2__*) ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VN_RELE_ASYNC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZTOV (TYPE_1__*) ; 
 int /*<<< orphan*/  dmu_objset_pool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_pool_vnrele_taskq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int sa_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int zfs_zget (TYPE_2__*,scalar_t__,TYPE_1__**) ; 

__attribute__((used)) static int
zfs_rename_check(znode_t *szp, znode_t *sdzp, znode_t *tdzp)
{
	zfsvfs_t	*zfsvfs;
	znode_t		*zp, *zp1;
	uint64_t	parent;
	int		error;

	zfsvfs = tdzp->z_zfsvfs;
	if (tdzp == szp)
		return (SET_ERROR(EINVAL));
	if (tdzp == sdzp)
		return (0);
	if (tdzp->z_id == zfsvfs->z_root)
		return (0);
	zp = tdzp;
	for (;;) {
		ASSERT(!zp->z_unlinked);
		if ((error = sa_lookup(zp->z_sa_hdl,
		    SA_ZPL_PARENT(zfsvfs), &parent, sizeof (parent))) != 0)
			break;

		if (parent == szp->z_id) {
			error = SET_ERROR(EINVAL);
			break;
		}
		if (parent == zfsvfs->z_root)
			break;
		if (parent == sdzp->z_id)
			break;

		error = zfs_zget(zfsvfs, parent, &zp1);
		if (error != 0)
			break;

		if (zp != tdzp)
			VN_RELE_ASYNC(ZTOV(zp),
			    dsl_pool_vnrele_taskq(dmu_objset_pool(zfsvfs->z_os)));
		zp = zp1;
	}

	if (error == ENOTDIR)
		panic("checkpath: .. not a directory\n");
	if (zp != tdzp)
		VN_RELE_ASYNC(ZTOV(zp),
		    dsl_pool_vnrele_taskq(dmu_objset_pool(zfsvfs->z_os)));
	return (error);
}