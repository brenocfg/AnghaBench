#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct stash_update_rules {int /*<<< orphan*/  include_changed; int /*<<< orphan*/  include_untracked; int /*<<< orphan*/  include_ignored; } ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_index ;
struct TYPE_6__ {int /*<<< orphan*/  path; } ;
struct TYPE_5__ {char* path; int /*<<< orphan*/  mode; } ;
struct TYPE_7__ {int status; TYPE_2__ old_file; TYPE_1__ new_file; } ;
typedef  TYPE_3__ git_diff_delta ;
typedef  int /*<<< orphan*/  git_diff ;

/* Variables and functions */
#define  GIT_DELTA_ADDED 132 
#define  GIT_DELTA_DELETED 131 
#define  GIT_DELTA_IGNORED 130 
#define  GIT_DELTA_MODIFIED 129 
#define  GIT_DELTA_UNTRACKED 128 
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 int /*<<< orphan*/  GIT_FILEMODE_TREE ; 
 TYPE_3__* git_diff_get_delta (int /*<<< orphan*/  const*,size_t) ; 
 size_t git_diff_num_deltas (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  git_index_find (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int git_index_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stash_to_index (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int stash_update_index_from_diff(
	git_repository *repo,
	git_index *index,
	const git_diff *diff,
	struct stash_update_rules *data)
{
	int error = 0;
	size_t d, max_d = git_diff_num_deltas(diff);

	for (d = 0; !error && d < max_d; ++d) {
		const char *add_path = NULL;
		const git_diff_delta *delta = git_diff_get_delta(diff, d);

		switch (delta->status) {
		case GIT_DELTA_IGNORED:
			if (data->include_ignored)
				add_path = delta->new_file.path;
			break;

		case GIT_DELTA_UNTRACKED:
			if (data->include_untracked &&
				delta->new_file.mode != GIT_FILEMODE_TREE)
				add_path = delta->new_file.path;
			break;

		case GIT_DELTA_ADDED:
		case GIT_DELTA_MODIFIED:
			if (data->include_changed)
				add_path = delta->new_file.path;
			break;

		case GIT_DELTA_DELETED:
			if (data->include_changed &&
				!git_index_find(NULL, index, delta->old_file.path))
				error = git_index_remove(index, delta->old_file.path, 0);
			break;

		default:
			/* Unimplemented */
			git_error_set(
				GIT_ERROR_INVALID,
				"cannot update index. Unimplemented status (%d)",
				delta->status);
			return -1;
		}

		if (add_path != NULL)
			error = stash_to_index(repo, index, add_path);
	}

	return error;
}