#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct devfs_mount {struct devfs_dirent* dm_rootdir; int /*<<< orphan*/  dm_lock; } ;
struct devfs_dirent {int de_flags; int /*<<< orphan*/  de_dlist; TYPE_1__* de_dirent; } ;
struct TYPE_2__ {scalar_t__ d_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVFS_DEL_NORECURSE ; 
 scalar_t__ DEVFS_DE_DROP (struct devfs_dirent*) ; 
 int /*<<< orphan*/  DEVFS_DE_HOLD (struct devfs_dirent*) ; 
 int DE_DOOMED ; 
 scalar_t__ DT_DIR ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  SX_XLOCKED ; 
 struct devfs_dirent* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct devfs_dirent* TAILQ_NEXT (struct devfs_dirent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct devfs_dirent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  de_list ; 
 int /*<<< orphan*/  devfs_delete (struct devfs_mount*,struct devfs_dirent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devfs_dirent_free (struct devfs_dirent*) ; 
 struct devfs_dirent* devfs_parent_dirent (struct devfs_dirent*) ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
devfs_rmdir_empty(struct devfs_mount *dm, struct devfs_dirent *de)
{
	struct devfs_dirent *dd, *de_dot, *de_dotdot;

	sx_assert(&dm->dm_lock, SX_XLOCKED);

	for (;;) {
		KASSERT(de->de_dirent->d_type == DT_DIR,
		    ("devfs_rmdir_empty: de is not a directory"));

		if ((de->de_flags & DE_DOOMED) != 0 || de == dm->dm_rootdir)
			return;

		de_dot = TAILQ_FIRST(&de->de_dlist);
		KASSERT(de_dot != NULL, ("devfs_rmdir_empty: . missing"));
		de_dotdot = TAILQ_NEXT(de_dot, de_list);
		KASSERT(de_dotdot != NULL, ("devfs_rmdir_empty: .. missing"));
		/* Return if the directory is not empty. */
		if (TAILQ_NEXT(de_dotdot, de_list) != NULL)
			return;

		dd = devfs_parent_dirent(de);
		KASSERT(dd != NULL, ("devfs_rmdir_empty: NULL dd"));
		TAILQ_REMOVE(&de->de_dlist, de_dot, de_list);
		TAILQ_REMOVE(&de->de_dlist, de_dotdot, de_list);
		TAILQ_REMOVE(&dd->de_dlist, de, de_list);
		DEVFS_DE_HOLD(dd);
		devfs_delete(dm, de, DEVFS_DEL_NORECURSE);
		devfs_delete(dm, de_dot, DEVFS_DEL_NORECURSE);
		devfs_delete(dm, de_dotdot, DEVFS_DEL_NORECURSE);
		if (DEVFS_DE_DROP(dd)) {
			devfs_dirent_free(dd);
			return;
		}

		de = dd;
	}
}