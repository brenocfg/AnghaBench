#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int flags; int /*<<< orphan*/  wd_oid; int /*<<< orphan*/  path; int /*<<< orphan*/  repo; } ;
typedef  TYPE_1__ git_submodule ;
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_9__ {char const* ptr; } ;
typedef  TYPE_2__ git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  DOT_GIT ; 
 TYPE_2__ GIT_BUF_INIT ; 
 int GIT_EBAREREPO ; 
 int /*<<< orphan*/  GIT_HEAD_FILE ; 
 unsigned int GIT_REPOSITORY_OPEN_BARE ; 
 unsigned int GIT_REPOSITORY_OPEN_NO_SEARCH ; 
 int GIT_SUBMODULE_STATUS_IN_WD ; 
 int GIT_SUBMODULE_STATUS__WD_OID_VALID ; 
 int GIT_SUBMODULE_STATUS__WD_SCANNED ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_2__*) ; 
 scalar_t__ git_buf_joinpath (TYPE_2__*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_rtruncate_at_char (TYPE_2__*,char) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 scalar_t__ git_path_exists (char const*) ; 
 scalar_t__ git_path_isdir (char const*) ; 
 int /*<<< orphan*/  git_reference_name_to_id (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ git_repository__ensure_not_bare (int /*<<< orphan*/ ,char*) ; 
 int git_repository_open_ext (int /*<<< orphan*/ **,char const*,unsigned int,char const*) ; 
 char* git_repository_workdir (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int git_submodule__open(
	git_repository **subrepo, git_submodule *sm, bool bare)
{
	int error;
	git_buf path = GIT_BUF_INIT;
	unsigned int flags = GIT_REPOSITORY_OPEN_NO_SEARCH;
	const char *wd;

	assert(sm && subrepo);

	if (git_repository__ensure_not_bare(
			sm->repo, "open submodule repository") < 0)
		return GIT_EBAREREPO;

	wd = git_repository_workdir(sm->repo);

	if (git_buf_joinpath(&path, wd, sm->path) < 0 ||
		git_buf_joinpath(&path, path.ptr, DOT_GIT) < 0)
		return -1;

	sm->flags = sm->flags &
		~(GIT_SUBMODULE_STATUS_IN_WD |
		  GIT_SUBMODULE_STATUS__WD_OID_VALID |
		  GIT_SUBMODULE_STATUS__WD_SCANNED);

	if (bare)
		flags |= GIT_REPOSITORY_OPEN_BARE;

	error = git_repository_open_ext(subrepo, path.ptr, flags, wd);

	/* if we opened the submodule successfully, grab HEAD OID, etc. */
	if (!error) {
		sm->flags |= GIT_SUBMODULE_STATUS_IN_WD |
			GIT_SUBMODULE_STATUS__WD_SCANNED;

		if (!git_reference_name_to_id(&sm->wd_oid, *subrepo, GIT_HEAD_FILE))
			sm->flags |= GIT_SUBMODULE_STATUS__WD_OID_VALID;
		else
			git_error_clear();
	} else if (git_path_exists(path.ptr)) {
		sm->flags |= GIT_SUBMODULE_STATUS__WD_SCANNED |
			GIT_SUBMODULE_STATUS_IN_WD;
	} else {
		git_buf_rtruncate_at_char(&path, '/'); /* remove "/.git" */

		if (git_path_isdir(path.ptr))
			sm->flags |= GIT_SUBMODULE_STATUS__WD_SCANNED;
	}

	git_buf_dispose(&path);

	return error;
}