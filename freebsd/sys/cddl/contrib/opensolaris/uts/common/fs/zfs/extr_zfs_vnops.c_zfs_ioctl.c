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
struct TYPE_9__ {int /*<<< orphan*/  z_id; TYPE_2__* z_zfsvfs; } ;
typedef  TYPE_1__ znode_t ;
struct TYPE_10__ {int /*<<< orphan*/  z_os; } ;
typedef  TYPE_2__ zfsvfs_t ;
typedef  int /*<<< orphan*/  vnode_t ;
typedef  int u_long ;
typedef  int /*<<< orphan*/  offset_t ;
typedef  int /*<<< orphan*/  off ;
typedef  int /*<<< orphan*/  ndata ;
struct TYPE_11__ {int /*<<< orphan*/  doi_fill_count; } ;
typedef  TYPE_3__ dmu_object_info_t ;
typedef  int /*<<< orphan*/  cred_t ;
typedef  int /*<<< orphan*/  caller_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFAULT ; 
 int /*<<< orphan*/  ENOTTY ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 TYPE_1__* VTOZ (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZFS_ENTER (TYPE_2__*) ; 
 int /*<<< orphan*/  ZFS_EXIT (TYPE_2__*) ; 
 int /*<<< orphan*/  ZFS_VERIFY_ZP (TYPE_1__*) ; 
#define  _FIOFFS 133 
#define  _FIOGDIO 132 
#define  _FIOSDIO 131 
#define  _FIO_COUNT_FILLED 130 
#define  _FIO_SEEK_DATA 129 
#define  _FIO_SEEK_HOLE 128 
 int /*<<< orphan*/  ddi_copyin (void*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ddi_copyout (int /*<<< orphan*/ *,void*,int,int) ; 
 int dmu_object_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int dmu_object_wait_synced (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int zfs_holey (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zfs_ioctl(vnode_t *vp, u_long com, intptr_t data, int flag, cred_t *cred,
    int *rvalp, caller_context_t *ct)
{
	offset_t off;
	offset_t ndata;
	dmu_object_info_t doi;
	int error;
	zfsvfs_t *zfsvfs;
	znode_t *zp;

	switch (com) {
	case _FIOFFS:
	{
		return (0);

		/*
		 * The following two ioctls are used by bfu.  Faking out,
		 * necessary to avoid bfu errors.
		 */
	}
	case _FIOGDIO:
	case _FIOSDIO:
	{
		return (0);
	}

	case _FIO_SEEK_DATA:
	case _FIO_SEEK_HOLE:
	{
#ifdef illumos
		if (ddi_copyin((void *)data, &off, sizeof (off), flag))
			return (SET_ERROR(EFAULT));
#else
		off = *(offset_t *)data;
#endif
		zp = VTOZ(vp);
		zfsvfs = zp->z_zfsvfs;
		ZFS_ENTER(zfsvfs);
		ZFS_VERIFY_ZP(zp);

		/* offset parameter is in/out */
		error = zfs_holey(vp, com, &off);
		ZFS_EXIT(zfsvfs);
		if (error)
			return (error);
#ifdef illumos
		if (ddi_copyout(&off, (void *)data, sizeof (off), flag))
			return (SET_ERROR(EFAULT));
#else
		*(offset_t *)data = off;
#endif
		return (0);
	}
#ifdef illumos
	case _FIO_COUNT_FILLED:
	{
		/*
		 * _FIO_COUNT_FILLED adds a new ioctl command which
		 * exposes the number of filled blocks in a
		 * ZFS object.
		 */
		zp = VTOZ(vp);
		zfsvfs = zp->z_zfsvfs;
		ZFS_ENTER(zfsvfs);
		ZFS_VERIFY_ZP(zp);

		/*
		 * Wait for all dirty blocks for this object
		 * to get synced out to disk, and the DMU info
		 * updated.
		 */
		error = dmu_object_wait_synced(zfsvfs->z_os, zp->z_id);
		if (error) {
			ZFS_EXIT(zfsvfs);
			return (error);
		}

		/*
		 * Retrieve fill count from DMU object.
		 */
		error = dmu_object_info(zfsvfs->z_os, zp->z_id, &doi);
		if (error) {
			ZFS_EXIT(zfsvfs);
			return (error);
		}

		ndata = doi.doi_fill_count;

		ZFS_EXIT(zfsvfs);
		if (ddi_copyout(&ndata, (void *)data, sizeof (ndata), flag))
			return (SET_ERROR(EFAULT));
		return (0);
	}
#endif
	}
	return (SET_ERROR(ENOTTY));
}