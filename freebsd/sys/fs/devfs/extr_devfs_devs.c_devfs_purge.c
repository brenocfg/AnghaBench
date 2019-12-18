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
struct devfs_mount {int /*<<< orphan*/  dm_lock; } ;
struct devfs_dirent {int de_flags; TYPE_1__* de_dirent; int /*<<< orphan*/  de_dlist; } ;
struct TYPE_2__ {scalar_t__ d_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVFS_DEL_NORECURSE ; 
 scalar_t__ DEVFS_DE_DROP (struct devfs_dirent*) ; 
 int /*<<< orphan*/  DEVFS_DE_HOLD (struct devfs_dirent*) ; 
 int DE_DOOMED ; 
 int DE_DOT ; 
 int DE_DOTDOT ; 
 int DE_USER ; 
 scalar_t__ DT_DIR ; 
 int /*<<< orphan*/  SX_XLOCKED ; 
 struct devfs_dirent* TAILQ_LAST (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct devfs_dirent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  de_list ; 
 int /*<<< orphan*/  devfs_delete (struct devfs_mount*,struct devfs_dirent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devfs_dir_unref_de (struct devfs_mount*,struct devfs_dirent*) ; 
 int /*<<< orphan*/  devfs_dirent_free (struct devfs_dirent*) ; 
 int /*<<< orphan*/  devfs_dlist_head ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
devfs_purge(struct devfs_mount *dm, struct devfs_dirent *dd)
{
	struct devfs_dirent *de;

	sx_assert(&dm->dm_lock, SX_XLOCKED);

	DEVFS_DE_HOLD(dd);
	for (;;) {
		/*
		 * Use TAILQ_LAST() to remove "." and ".." last.
		 * We might need ".." to resolve a path in
		 * devfs_dir_unref_de().
		 */
		de = TAILQ_LAST(&dd->de_dlist, devfs_dlist_head);
		if (de == NULL)
			break;
		TAILQ_REMOVE(&dd->de_dlist, de, de_list);
		if (de->de_flags & DE_USER)
			devfs_dir_unref_de(dm, dd);
		if (de->de_flags & (DE_DOT | DE_DOTDOT))
			devfs_delete(dm, de, DEVFS_DEL_NORECURSE);
		else if (de->de_dirent->d_type == DT_DIR)
			devfs_purge(dm, de);
		else
			devfs_delete(dm, de, DEVFS_DEL_NORECURSE);
	}
	if (DEVFS_DE_DROP(dd))
		devfs_dirent_free(dd);
	else if ((dd->de_flags & DE_DOOMED) == 0)
		devfs_delete(dm, dd, DEVFS_DEL_NORECURSE);
}