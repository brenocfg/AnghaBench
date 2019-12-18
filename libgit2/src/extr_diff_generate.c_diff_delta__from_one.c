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
struct TYPE_13__ {int flags; int /*<<< orphan*/  id; int /*<<< orphan*/  file_size; int /*<<< orphan*/  mode; int /*<<< orphan*/  path; } ;
typedef  TYPE_3__ git_index_entry ;
typedef  int /*<<< orphan*/  git_diff_generated ;
struct TYPE_12__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  id; void* id_abbrev; int /*<<< orphan*/  size; int /*<<< orphan*/  mode; } ;
struct TYPE_11__ {int /*<<< orphan*/  flags; void* id_abbrev; int /*<<< orphan*/  id; int /*<<< orphan*/  size; int /*<<< orphan*/  mode; } ;
struct TYPE_14__ {int nfiles; TYPE_2__ new_file; TYPE_1__ old_file; } ;
typedef  TYPE_4__ git_diff_delta ;
typedef  scalar_t__ git_delta_t ;

/* Variables and functions */
 scalar_t__ DIFF_FLAG_ISNT_SET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ DIFF_FLAG_IS_SET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ GIT_DELTA_IGNORED ; 
 scalar_t__ GIT_DELTA_MODIFIED ; 
 scalar_t__ GIT_DELTA_UNREADABLE ; 
 scalar_t__ GIT_DELTA_UNTRACKED ; 
 int /*<<< orphan*/  GIT_DIFF_FLAG_EXISTS ; 
 int /*<<< orphan*/  GIT_DIFF_FLAG_VALID_ID ; 
 int /*<<< orphan*/  GIT_DIFF_INCLUDE_IGNORED ; 
 int /*<<< orphan*/  GIT_DIFF_INCLUDE_UNREADABLE ; 
 int /*<<< orphan*/  GIT_DIFF_INCLUDE_UNTRACKED ; 
 int /*<<< orphan*/  GIT_DIFF_REVERSE ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_4__*) ; 
 int GIT_INDEX_ENTRY_VALID ; 
 void* GIT_OID_HEXSZ ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_4__* diff_delta__alloc (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int diff_insert_delta (int /*<<< orphan*/ *,TYPE_4__*,char const*) ; 
 int /*<<< orphan*/  diff_pathspec_match (char const**,int /*<<< orphan*/ *,TYPE_3__ const*) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_is_zero (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int diff_delta__from_one(
	git_diff_generated *diff,
	git_delta_t status,
	const git_index_entry *oitem,
	const git_index_entry *nitem)
{
	const git_index_entry *entry = nitem;
	bool has_old = false;
	git_diff_delta *delta;
	const char *matched_pathspec;

	assert((oitem != NULL) ^ (nitem != NULL));

	if (oitem) {
		entry = oitem;
		has_old = true;
	}

	if (DIFF_FLAG_IS_SET(diff, GIT_DIFF_REVERSE))
		has_old = !has_old;

	if ((entry->flags & GIT_INDEX_ENTRY_VALID) != 0)
		return 0;

	if (status == GIT_DELTA_IGNORED &&
		DIFF_FLAG_ISNT_SET(diff, GIT_DIFF_INCLUDE_IGNORED))
		return 0;

	if (status == GIT_DELTA_UNTRACKED &&
		DIFF_FLAG_ISNT_SET(diff, GIT_DIFF_INCLUDE_UNTRACKED))
		return 0;

	if (status == GIT_DELTA_UNREADABLE &&
		DIFF_FLAG_ISNT_SET(diff, GIT_DIFF_INCLUDE_UNREADABLE))
		return 0;

	if (!diff_pathspec_match(&matched_pathspec, diff, entry))
		return 0;

	delta = diff_delta__alloc(diff, status, entry->path);
	GIT_ERROR_CHECK_ALLOC(delta);

	/* This fn is just for single-sided diffs */
	assert(status != GIT_DELTA_MODIFIED);
	delta->nfiles = 1;

	if (has_old) {
		delta->old_file.mode = entry->mode;
		delta->old_file.size = entry->file_size;
		delta->old_file.flags |= GIT_DIFF_FLAG_EXISTS;
		git_oid_cpy(&delta->old_file.id, &entry->id);
		delta->old_file.id_abbrev = GIT_OID_HEXSZ;
	} else /* ADDED, IGNORED, UNTRACKED */ {
		delta->new_file.mode = entry->mode;
		delta->new_file.size = entry->file_size;
		delta->new_file.flags |= GIT_DIFF_FLAG_EXISTS;
		git_oid_cpy(&delta->new_file.id, &entry->id);
		delta->new_file.id_abbrev = GIT_OID_HEXSZ;
	}

	delta->old_file.flags |= GIT_DIFF_FLAG_VALID_ID;

	if (has_old || !git_oid_is_zero(&delta->new_file.id))
		delta->new_file.flags |= GIT_DIFF_FLAG_VALID_ID;

	return diff_insert_delta(diff, delta, matched_pathspec);
}