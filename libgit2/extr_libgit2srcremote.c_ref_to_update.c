#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_remote ;
typedef  int /*<<< orphan*/  git_refspec ;
struct TYPE_9__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int GIT_ENOTFOUND ; 
 scalar_t__ git__strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int git_branch_upstream_name (TYPE_1__*,int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ git_branch_upstream_remote (TYPE_1__*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_buf_cstr (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int /*<<< orphan*/  git_reference__is_branch (char const*) ; 
 int /*<<< orphan*/  git_refspec_dst_matches (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int git_refspec_rtransform (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_remote_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_remote_owner (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ref_to_update(int *update, git_buf *remote_name, git_remote *remote, git_refspec *spec, const char *ref_name)
{
	int error = 0;
	git_repository *repo;
	git_buf upstream_remote = GIT_BUF_INIT;
	git_buf upstream_name = GIT_BUF_INIT;

	repo = git_remote_owner(remote);

	if ((!git_reference__is_branch(ref_name)) ||
	    !git_remote_name(remote) ||
	    (error = git_branch_upstream_remote(&upstream_remote, repo, ref_name) < 0) ||
	    git__strcmp(git_remote_name(remote), git_buf_cstr(&upstream_remote)) ||
	    (error = git_branch_upstream_name(&upstream_name, repo, ref_name)) < 0 ||
	    !git_refspec_dst_matches(spec, git_buf_cstr(&upstream_name)) ||
	    (error = git_refspec_rtransform(remote_name, spec, upstream_name.ptr)) < 0) {
		/* Not an error if there is no upstream */
		if (error == GIT_ENOTFOUND) {
			git_error_clear();
			error = 0;
		}

		*update = 0;
	} else {
		*update = 1;
	}

	git_buf_dispose(&upstream_remote);
	git_buf_dispose(&upstream_name);
	return error;
}