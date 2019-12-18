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
typedef  int /*<<< orphan*/  zfsvfs_t ;
typedef  int /*<<< orphan*/  objset_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  DMU_OST_ZFS ; 
 int /*<<< orphan*/  ENAMETOOLONG ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 scalar_t__ MNAMELEN ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_objset_disown (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dmu_objset_own (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char const*) ; 
 int zfsvfs_create_impl (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
zfsvfs_create(const char *osname, zfsvfs_t **zfvp)
{
	objset_t *os;
	zfsvfs_t *zfsvfs;
	int error;

	/*
	 * XXX: Fix struct statfs so this isn't necessary!
	 *
	 * The 'osname' is used as the filesystem's special node, which means
	 * it must fit in statfs.f_mntfromname, or else it can't be
	 * enumerated, so libzfs_mnttab_find() returns NULL, which causes
	 * 'zfs unmount' to think it's not mounted when it is.
	 */
	if (strlen(osname) >= MNAMELEN)
		return (SET_ERROR(ENAMETOOLONG));

	zfsvfs = kmem_zalloc(sizeof (zfsvfs_t), KM_SLEEP);

	/*
	 * We claim to always be readonly so we can open snapshots;
	 * other ZPL code will prevent us from writing to snapshots.
	 */

	error = dmu_objset_own(osname, DMU_OST_ZFS, B_TRUE, zfsvfs, &os);
	if (error != 0) {
		kmem_free(zfsvfs, sizeof (zfsvfs_t));
		return (error);
	}

	error = zfsvfs_create_impl(zfvp, zfsvfs, os);
	if (error != 0) {
		dmu_objset_disown(os, zfsvfs);
	}
	return (error);
}