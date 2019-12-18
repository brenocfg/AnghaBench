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
struct devfs_mount {int /*<<< orphan*/  dm_lock; } ;
struct devfs_dirent {int de_flags; } ;

/* Variables and functions */
 scalar_t__ DEVFS_DE_DROP (struct devfs_dirent*) ; 
 scalar_t__ DEVFS_DMP_DROP (struct devfs_mount*) ; 
 int DE_DOOMED ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  devfs_dirent_free (struct devfs_dirent*) ; 
 int /*<<< orphan*/  devfs_unmount_final (struct devfs_mount*) ; 
 int /*<<< orphan*/  sx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
devfs_allocv_drop_refs(int drop_dm_lock, struct devfs_mount *dmp,
	struct devfs_dirent *de)
{
	int not_found;

	not_found = 0;
	if (de->de_flags & DE_DOOMED)
		not_found = 1;
	if (DEVFS_DE_DROP(de)) {
		KASSERT(not_found == 1, ("DEVFS de dropped but not doomed"));
		devfs_dirent_free(de);
	}
	if (DEVFS_DMP_DROP(dmp)) {
		KASSERT(not_found == 1,
			("DEVFS mount struct freed before dirent"));
		not_found = 2;
		sx_xunlock(&dmp->dm_lock);
		devfs_unmount_final(dmp);
	}
	if (not_found == 1 || (drop_dm_lock && not_found != 2))
		sx_unlock(&dmp->dm_lock);
	return (not_found);
}