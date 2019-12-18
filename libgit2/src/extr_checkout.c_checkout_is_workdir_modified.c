#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_submodule ;
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_12__ {scalar_t__ file_size; int /*<<< orphan*/  mode; int /*<<< orphan*/  id; int /*<<< orphan*/  mtime; int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ git_index_entry ;
struct TYPE_13__ {scalar_t__ size; int /*<<< orphan*/  mode; int /*<<< orphan*/  id; } ;
typedef  TYPE_2__ git_diff_file ;
struct TYPE_14__ {int /*<<< orphan*/  diff; int /*<<< orphan*/  respect_filemode; int /*<<< orphan*/  index; int /*<<< orphan*/  repo; } ;
typedef  TYPE_3__ checkout_data ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_FILEMODE_COMMIT ; 
 int /*<<< orphan*/  GIT_SUBMODULE_IGNORE_UNSPECIFIED ; 
 scalar_t__ GIT_SUBMODULE_STATUS_IS_WD_DIRTY (unsigned int) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ git_diff__oid_for_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 TYPE_1__* git_index_get_bypath (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ git_index_time_eq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ git_oid__cmp (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_submodule_free (int /*<<< orphan*/ *) ; 
 scalar_t__ git_submodule_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ git_submodule_status (unsigned int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * git_submodule_wd_id (int /*<<< orphan*/ *) ; 
 scalar_t__ is_filemode_changed (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_workdir_base_or_new (int /*<<< orphan*/ *,TYPE_2__ const*,TYPE_2__ const*) ; 

__attribute__((used)) static bool checkout_is_workdir_modified(
	checkout_data *data,
	const git_diff_file *baseitem,
	const git_diff_file *newitem,
	const git_index_entry *wditem)
{
	git_oid oid;
	const git_index_entry *ie;

	/* handle "modified" submodule */
	if (wditem->mode == GIT_FILEMODE_COMMIT) {
		git_submodule *sm;
		unsigned int sm_status = 0;
		const git_oid *sm_oid = NULL;
		bool rval = false;

		if (git_submodule_lookup(&sm, data->repo, wditem->path) < 0) {
			git_error_clear();
			return true;
		}

		if (git_submodule_status(&sm_status, data->repo, wditem->path, GIT_SUBMODULE_IGNORE_UNSPECIFIED) < 0 ||
			GIT_SUBMODULE_STATUS_IS_WD_DIRTY(sm_status))
			rval = true;
		else if ((sm_oid = git_submodule_wd_id(sm)) == NULL)
			rval = false;
		else
			rval = (git_oid__cmp(&baseitem->id, sm_oid) != 0);

		git_submodule_free(sm);
		return rval;
	}

	/*
	 * Look at the cache to decide if the workdir is modified: if the
	 * cache contents match the workdir contents, then we do not need
	 * to examine the working directory directly, instead we can
	 * examine the cache to see if _it_ has been modified.  This allows
	 * us to avoid touching the disk.
	 */
	ie = git_index_get_bypath(data->index, wditem->path, 0);

	if (ie != NULL &&
		git_index_time_eq(&wditem->mtime, &ie->mtime) &&
		wditem->file_size == ie->file_size &&
		!is_filemode_changed(wditem->mode, ie->mode, data->respect_filemode)) {

		/* The workdir is modified iff the index entry is modified */
		return !is_workdir_base_or_new(&ie->id, baseitem, newitem) ||
			is_filemode_changed(baseitem->mode, ie->mode, data->respect_filemode);
	}

	/* depending on where base is coming from, we may or may not know
	 * the actual size of the data, so we can't rely on this shortcut.
	 */
	if (baseitem->size && wditem->file_size != baseitem->size)
		return true;

	/* if the workdir item is a directory, it cannot be a modified file */
	if (S_ISDIR(wditem->mode))
		return false;

	if (is_filemode_changed(baseitem->mode, wditem->mode, data->respect_filemode))
		return true;

	if (git_diff__oid_for_entry(&oid, data->diff, wditem, wditem->mode, NULL) < 0)
		return false;

	/* Allow the checkout if the workdir is not modified *or* if the checkout
	 * target's contents are already in the working directory.
	 */
	return !is_workdir_base_or_new(&oid, baseitem, newitem);
}