#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {TYPE_6__* delta; } ;
typedef  TYPE_4__ git_patch ;
struct TYPE_18__ {size_t max_name; size_t max_filestat; size_t files_changed; size_t insertions; size_t deletions; int /*<<< orphan*/  max_digits; TYPE_3__* filestats; int /*<<< orphan*/  renames; int /*<<< orphan*/ * diff; } ;
typedef  TYPE_5__ git_diff_stats ;
struct TYPE_15__ {int /*<<< orphan*/  path; } ;
struct TYPE_14__ {int /*<<< orphan*/  path; } ;
struct TYPE_19__ {TYPE_2__ old_file; TYPE_1__ new_file; } ;
typedef  TYPE_6__ git_diff_delta ;
typedef  int /*<<< orphan*/  git_diff ;
typedef  int /*<<< orphan*/  diff_file_stats ;
struct TYPE_16__ {size_t insertions; size_t deletions; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_5__*) ; 
 int /*<<< orphan*/  GIT_REFCOUNT_INC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  digits_for_value (size_t) ; 
 void* git__calloc (size_t,int) ; 
 int /*<<< orphan*/  git__free (TYPE_5__*) ; 
 size_t git_diff_num_deltas (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_stats_free (TYPE_5__*) ; 
 int /*<<< orphan*/  git_patch_free (TYPE_4__*) ; 
 int git_patch_from_diff (TYPE_4__**,int /*<<< orphan*/ *,size_t) ; 
 int git_patch_line_stats (int /*<<< orphan*/ *,size_t*,size_t*,TYPE_4__*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 

int git_diff_get_stats(
	git_diff_stats **out,
	git_diff *diff)
{
	size_t i, deltas;
	size_t total_insertions = 0, total_deletions = 0;
	git_diff_stats *stats = NULL;
	int error = 0;

	assert(out && diff);

	stats = git__calloc(1, sizeof(git_diff_stats));
	GIT_ERROR_CHECK_ALLOC(stats);

	deltas = git_diff_num_deltas(diff);

	stats->filestats = git__calloc(deltas, sizeof(diff_file_stats));
	if (!stats->filestats) {
		git__free(stats);
		return -1;
	}

	stats->diff = diff;
	GIT_REFCOUNT_INC(diff);

	for (i = 0; i < deltas && !error; ++i) {
		git_patch *patch = NULL;
		size_t add = 0, remove = 0, namelen;
		const git_diff_delta *delta;

		if ((error = git_patch_from_diff(&patch, diff, i)) < 0)
			break;

		/* keep a count of renames because it will affect formatting */
		delta = patch->delta;

		/* TODO ugh */
		namelen = strlen(delta->new_file.path);
		if (strcmp(delta->old_file.path, delta->new_file.path) != 0) {
			namelen += strlen(delta->old_file.path);
			stats->renames++;
		}

		/* and, of course, count the line stats */
		error = git_patch_line_stats(NULL, &add, &remove, patch);

		git_patch_free(patch);

		stats->filestats[i].insertions = add;
		stats->filestats[i].deletions = remove;

		total_insertions += add;
		total_deletions += remove;

		if (stats->max_name < namelen)
			stats->max_name = namelen;
		if (stats->max_filestat < add + remove)
			stats->max_filestat = add + remove;
	}

	stats->files_changed = deltas;
	stats->insertions = total_insertions;
	stats->deletions = total_deletions;
	stats->max_digits = digits_for_value(stats->max_filestat + 1);

	if (error < 0) {
		git_diff_stats_free(stats);
		stats = NULL;
	}

	*out = stats;
	return error;
}