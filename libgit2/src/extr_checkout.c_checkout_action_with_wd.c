#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_iterator ;
struct TYPE_12__ {int /*<<< orphan*/  path; int /*<<< orphan*/  mode; } ;
typedef  TYPE_1__ git_index_entry ;
struct TYPE_15__ {int /*<<< orphan*/  mode; } ;
struct TYPE_14__ {int /*<<< orphan*/  mode; } ;
struct TYPE_13__ {int status; TYPE_6__ new_file; TYPE_5__ old_file; } ;
typedef  TYPE_2__ git_diff_delta ;
typedef  int /*<<< orphan*/  checkout_data ;

/* Variables and functions */
 int CHECKOUT_ACTION_IF (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CHECKOUT_ACTION__NONE ; 
 int CHECKOUT_ACTION__UPDATE_BLOB ; 
 int /*<<< orphan*/  CONFLICT ; 
 int /*<<< orphan*/  DONT_OVERWRITE_IGNORED ; 
 int /*<<< orphan*/  FORCE ; 
 int /*<<< orphan*/  GIT_CHECKOUT_NOTIFY_DIRTY ; 
#define  GIT_DELTA_ADDED 132 
#define  GIT_DELTA_DELETED 131 
#define  GIT_DELTA_MODIFIED 130 
#define  GIT_DELTA_TYPECHANGE 129 
#define  GIT_DELTA_UNMODIFIED 128 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GIT_FILEMODE_COMMIT ; 
 int /*<<< orphan*/  GIT_FILEMODE_TREE ; 
 int /*<<< orphan*/  NONE ; 
 int /*<<< orphan*/  REMOVE ; 
 int /*<<< orphan*/  REMOVE_AND_UPDATE ; 
 int /*<<< orphan*/  SAFE ; 
 int /*<<< orphan*/  UPDATE_BLOB ; 
 int checkout_action_common (int*,int /*<<< orphan*/ *,TYPE_2__ const*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  checkout_is_workdir_modified (int /*<<< orphan*/ *,TYPE_5__*,TYPE_6__*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  checkout_notify (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__ const*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  git_iterator_current_is_ignored (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  submodule_is_config_only (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int checkout_action_with_wd(
	int *action,
	checkout_data *data,
	const git_diff_delta *delta,
	git_iterator *workdir,
	const git_index_entry *wd)
{
	*action = CHECKOUT_ACTION__NONE;

	switch (delta->status) {
	case GIT_DELTA_UNMODIFIED: /* case 14/15 or 33 */
		if (checkout_is_workdir_modified(data, &delta->old_file, &delta->new_file, wd)) {
			GIT_ERROR_CHECK_ERROR(
				checkout_notify(data, GIT_CHECKOUT_NOTIFY_DIRTY, delta, wd) );
			*action = CHECKOUT_ACTION_IF(FORCE, UPDATE_BLOB, NONE);
		}
		break;
	case GIT_DELTA_ADDED: /* case 3, 4 or 6 */
		if (git_iterator_current_is_ignored(workdir))
			*action = CHECKOUT_ACTION_IF(DONT_OVERWRITE_IGNORED, CONFLICT, UPDATE_BLOB);
		else
			*action = CHECKOUT_ACTION_IF(FORCE, UPDATE_BLOB, CONFLICT);
		break;
	case GIT_DELTA_DELETED: /* case 9 or 10 (or 26 but not really) */
		if (checkout_is_workdir_modified(data, &delta->old_file, &delta->new_file, wd))
			*action = CHECKOUT_ACTION_IF(FORCE, REMOVE, CONFLICT);
		else
			*action = CHECKOUT_ACTION_IF(SAFE, REMOVE, NONE);
		break;
	case GIT_DELTA_MODIFIED: /* case 16, 17, 18 (or 36 but not really) */
		if (wd->mode != GIT_FILEMODE_COMMIT &&
			checkout_is_workdir_modified(data, &delta->old_file, &delta->new_file, wd))
			*action = CHECKOUT_ACTION_IF(FORCE, UPDATE_BLOB, CONFLICT);
		else
			*action = CHECKOUT_ACTION_IF(SAFE, UPDATE_BLOB, NONE);
		break;
	case GIT_DELTA_TYPECHANGE: /* case 22, 23, 29, 30 */
		if (delta->old_file.mode == GIT_FILEMODE_TREE) {
			if (wd->mode == GIT_FILEMODE_TREE)
				/* either deleting items in old tree will delete the wd dir,
				 * or we'll get a conflict when we attempt blob update...
				 */
				*action = CHECKOUT_ACTION_IF(SAFE, UPDATE_BLOB, NONE);
			else if (wd->mode == GIT_FILEMODE_COMMIT) {
				/* workdir is possibly a "phantom" submodule - treat as a
				 * tree if the only submodule info came from the config
				 */
				if (submodule_is_config_only(data, wd->path))
					*action = CHECKOUT_ACTION_IF(SAFE, UPDATE_BLOB, NONE);
				else
					*action = CHECKOUT_ACTION_IF(FORCE, REMOVE_AND_UPDATE, CONFLICT);
			} else
				*action = CHECKOUT_ACTION_IF(FORCE, REMOVE, CONFLICT);
		}
		else if (checkout_is_workdir_modified(data, &delta->old_file, &delta->new_file, wd))
			*action = CHECKOUT_ACTION_IF(FORCE, REMOVE_AND_UPDATE, CONFLICT);
		else
			*action = CHECKOUT_ACTION_IF(SAFE, REMOVE_AND_UPDATE, NONE);

		/* don't update if the typechange is to a tree */
		if (delta->new_file.mode == GIT_FILEMODE_TREE)
			*action = (*action & ~CHECKOUT_ACTION__UPDATE_BLOB);
		break;
	default: /* impossible */
		break;
	}

	return checkout_action_common(action, data, delta, wd);
}