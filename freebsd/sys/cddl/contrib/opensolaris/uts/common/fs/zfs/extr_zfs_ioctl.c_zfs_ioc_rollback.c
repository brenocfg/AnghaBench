#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  z_vfs; int /*<<< orphan*/  z_os; } ;
typedef  TYPE_1__ zfsvfs_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VFS_RELE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dmu_objset_ds (int /*<<< orphan*/ ) ; 
 int dsl_dataset_rollback (char const*,char*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ getzfsvfs (char const*,TYPE_1__**) ; 
 int /*<<< orphan*/  nvlist_lookup_string (int /*<<< orphan*/ *,char*,char**) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  vfs_unbusy (int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_component_namecheck (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int zfs_resume_fs (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int zfs_suspend_fs (TYPE_1__*) ; 

__attribute__((used)) static int
zfs_ioc_rollback(const char *fsname, nvlist_t *innvl, nvlist_t *outnvl)
{
	zfsvfs_t *zfsvfs;
	char *target = NULL;
	int error;

	(void) nvlist_lookup_string(innvl, "target", &target);
	if (target != NULL) {
		const char *cp = strchr(target, '@');

		/*
		 * The snap name must contain an @, and the part after it must
		 * contain only valid characters.
		 */
		if (cp == NULL ||
		    zfs_component_namecheck(cp + 1, NULL, NULL) != 0)
			return (SET_ERROR(EINVAL));
	}

	if (getzfsvfs(fsname, &zfsvfs) == 0) {
		dsl_dataset_t *ds;

		ds = dmu_objset_ds(zfsvfs->z_os);
		error = zfs_suspend_fs(zfsvfs);
		if (error == 0) {
			int resume_err;

			error = dsl_dataset_rollback(fsname, target, zfsvfs,
			    outnvl);
			resume_err = zfs_resume_fs(zfsvfs, ds);
			error = error ? error : resume_err;
		}
#ifdef illumos
		VFS_RELE(zfsvfs->z_vfs);
#else
		vfs_unbusy(zfsvfs->z_vfs);
#endif
	} else {
		error = dsl_dataset_rollback(fsname, target, NULL, outnvl);
	}
	return (error);
}