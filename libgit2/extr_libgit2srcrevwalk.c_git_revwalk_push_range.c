#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  repo; } ;
typedef  TYPE_1__ git_revwalk ;
struct TYPE_7__ {int flags; int /*<<< orphan*/  to; int /*<<< orphan*/  from; } ;
typedef  TYPE_2__ git_revspec ;

/* Variables and functions */
 int GIT_EINVALIDSPEC ; 
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 int GIT_REVPARSE_MERGE_BASE ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_object_id (int /*<<< orphan*/ ) ; 
 int git_revparse (TYPE_2__*,int /*<<< orphan*/ ,char const*) ; 
 int push_commit (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 

int git_revwalk_push_range(git_revwalk *walk, const char *range)
{
	git_revspec revspec;
	int error = 0;

	if ((error = git_revparse(&revspec, walk->repo, range)))
		return error;

	if (revspec.flags & GIT_REVPARSE_MERGE_BASE) {
		/* TODO: support "<commit>...<commit>" */
		git_error_set(GIT_ERROR_INVALID, "symmetric differences not implemented in revwalk");
		return GIT_EINVALIDSPEC;
	}

	if ((error = push_commit(walk, git_object_id(revspec.from), 1, false)))
		goto out;

	error = push_commit(walk, git_object_id(revspec.to), 0, false);

out:
	git_object_free(revspec.from);
	git_object_free(revspec.to);
	return error;
}