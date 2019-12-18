#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ mode; } ;
typedef  TYPE_2__ git_index_entry ;
struct TYPE_11__ {scalar_t__ mode; } ;
struct TYPE_13__ {TYPE_1__ new_file; } ;
typedef  TYPE_3__ git_diff_delta ;
typedef  int /*<<< orphan*/  git_checkout_notify_t ;
struct TYPE_14__ {int strategy; } ;
typedef  TYPE_4__ checkout_data ;

/* Variables and functions */
 int CHECKOUT_ACTION__CONFLICT ; 
 int CHECKOUT_ACTION__REMOVE ; 
 int CHECKOUT_ACTION__UPDATE_BLOB ; 
 int CHECKOUT_ACTION__UPDATE_SUBMODULE ; 
 int /*<<< orphan*/  GIT_CHECKOUT_NOTIFY_CONFLICT ; 
 int /*<<< orphan*/  GIT_CHECKOUT_NOTIFY_NONE ; 
 int /*<<< orphan*/  GIT_CHECKOUT_NOTIFY_UPDATED ; 
 int GIT_CHECKOUT_UPDATE_ONLY ; 
 scalar_t__ GIT_FILEMODE_LINK ; 
 scalar_t__ GIT_PERMS_IS_EXEC (scalar_t__) ; 
 scalar_t__ S_ISGITLINK (scalar_t__) ; 
 int checkout_notify (TYPE_4__*,int /*<<< orphan*/ ,TYPE_3__ const*,TYPE_2__ const*) ; 

__attribute__((used)) static int checkout_action_common(
	int *action,
	checkout_data *data,
	const git_diff_delta *delta,
	const git_index_entry *wd)
{
	git_checkout_notify_t notify = GIT_CHECKOUT_NOTIFY_NONE;

	if ((data->strategy & GIT_CHECKOUT_UPDATE_ONLY) != 0)
		*action = (*action & ~CHECKOUT_ACTION__REMOVE);

	if ((*action & CHECKOUT_ACTION__UPDATE_BLOB) != 0) {
		if (S_ISGITLINK(delta->new_file.mode))
			*action = (*action & ~CHECKOUT_ACTION__UPDATE_BLOB) |
				CHECKOUT_ACTION__UPDATE_SUBMODULE;

		/* to "update" a symlink, we must remove the old one first */
		if (delta->new_file.mode == GIT_FILEMODE_LINK && wd != NULL)
			*action |= CHECKOUT_ACTION__REMOVE;

		/* if the file is on disk and doesn't match our mode, force update */
		if (wd &&
			GIT_PERMS_IS_EXEC(wd->mode) !=
			GIT_PERMS_IS_EXEC(delta->new_file.mode))
				*action |= CHECKOUT_ACTION__REMOVE;

		notify = GIT_CHECKOUT_NOTIFY_UPDATED;
	}

	if ((*action & CHECKOUT_ACTION__CONFLICT) != 0)
		notify = GIT_CHECKOUT_NOTIFY_CONFLICT;

	return checkout_notify(data, notify, delta, wd);
}