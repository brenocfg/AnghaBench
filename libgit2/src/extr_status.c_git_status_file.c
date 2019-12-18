#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct status_file_info {char const* expected; unsigned int status; int /*<<< orphan*/  count; scalar_t__ ambiguous; int /*<<< orphan*/  wildmatch_flags; int /*<<< orphan*/  member_0; } ;
struct TYPE_7__ {int count; char const** strings; } ;
struct TYPE_8__ {int flags; TYPE_1__ pathspec; int /*<<< orphan*/  show; } ;
typedef  TYPE_2__ git_status_options ;
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_9__ {scalar_t__ ignore_case; } ;
typedef  TYPE_3__ git_index ;

/* Variables and functions */
 int GIT_EAMBIGUOUS ; 
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 TYPE_2__ GIT_STATUS_OPTIONS_INIT ; 
 int GIT_STATUS_OPT_DISABLE_PATHSPEC_MATCH ; 
 int GIT_STATUS_OPT_INCLUDE_IGNORED ; 
 int GIT_STATUS_OPT_INCLUDE_UNMODIFIED ; 
 int GIT_STATUS_OPT_INCLUDE_UNTRACKED ; 
 int GIT_STATUS_OPT_RECURSE_IGNORED_DIRS ; 
 int GIT_STATUS_OPT_RECURSE_UNTRACKED_DIRS ; 
 int /*<<< orphan*/  GIT_STATUS_SHOW_INDEX_AND_WORKDIR ; 
 int /*<<< orphan*/  WM_CASEFOLD ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_one_status ; 
 int /*<<< orphan*/  git__free (char const*) ; 
 char const* git__strdup (char const*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char const*) ; 
 int git_repository_index__weakptr (TYPE_3__**,int /*<<< orphan*/ *) ; 
 int git_status_foreach_ext (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,struct status_file_info*) ; 

int git_status_file(
	unsigned int *status_flags,
	git_repository *repo,
	const char *path)
{
	int error;
	git_status_options opts = GIT_STATUS_OPTIONS_INIT;
	struct status_file_info sfi = {0};
	git_index *index;

	assert(status_flags && repo && path);

	if ((error = git_repository_index__weakptr(&index, repo)) < 0)
		return error;

	if ((sfi.expected = git__strdup(path)) == NULL)
		return -1;
	if (index->ignore_case)
		sfi.wildmatch_flags = WM_CASEFOLD;

	opts.show = GIT_STATUS_SHOW_INDEX_AND_WORKDIR;
	opts.flags = GIT_STATUS_OPT_INCLUDE_IGNORED |
		GIT_STATUS_OPT_RECURSE_IGNORED_DIRS |
		GIT_STATUS_OPT_INCLUDE_UNTRACKED |
		GIT_STATUS_OPT_RECURSE_UNTRACKED_DIRS |
		GIT_STATUS_OPT_INCLUDE_UNMODIFIED |
		GIT_STATUS_OPT_DISABLE_PATHSPEC_MATCH;
	opts.pathspec.count = 1;
	opts.pathspec.strings = &sfi.expected;

	error = git_status_foreach_ext(repo, &opts, get_one_status, &sfi);

	if (error < 0 && sfi.ambiguous) {
		git_error_set(GIT_ERROR_INVALID,
			"ambiguous path '%s' given to git_status_file", sfi.expected);
		error = GIT_EAMBIGUOUS;
	}

	if (!error && !sfi.count) {
		git_error_set(GIT_ERROR_INVALID,
			"attempt to get status of nonexistent file '%s'", path);
		error = GIT_ENOTFOUND;
	}

	*status_flags = sfi.status;

	git__free(sfi.expected);

	return error;
}