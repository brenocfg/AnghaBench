#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int uninteresting; } ;
typedef  TYPE_1__ git_revwalk__push_options ;
struct TYPE_10__ {int /*<<< orphan*/  repo; } ;
typedef  TYPE_2__ git_revwalk ;
struct TYPE_11__ {int flags; int /*<<< orphan*/  to; int /*<<< orphan*/  from; } ;
typedef  TYPE_3__ git_revspec ;

/* Variables and functions */
 int GIT_EINVALIDSPEC ; 
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 int GIT_REVPARSE_MERGE_BASE ; 
 TYPE_1__ GIT_REVWALK__PUSH_OPTIONS_INIT ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_object_id (int /*<<< orphan*/ ) ; 
 int git_revparse (TYPE_3__*,int /*<<< orphan*/ ,char const*) ; 
 int git_revwalk__push_commit (TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*) ; 

int git_revwalk_push_range(git_revwalk *walk, const char *range)
{
	git_revwalk__push_options opts = GIT_REVWALK__PUSH_OPTIONS_INIT;
	git_revspec revspec;
	int error = 0;

	if ((error = git_revparse(&revspec, walk->repo, range)))
		return error;

	if (!revspec.to) {
		git_error_set(GIT_ERROR_INVALID, "invalid revspec: range not provided");
		error = GIT_EINVALIDSPEC;
		goto out;
	}

	if (revspec.flags & GIT_REVPARSE_MERGE_BASE) {
		/* TODO: support "<commit>...<commit>" */
		git_error_set(GIT_ERROR_INVALID, "symmetric differences not implemented in revwalk");
		error = GIT_EINVALIDSPEC;
		goto out;
	}

	opts.uninteresting = 1;
	if ((error = git_revwalk__push_commit(walk, git_object_id(revspec.from), &opts)))
		goto out;

	opts.uninteresting = 0;
	error = git_revwalk__push_commit(walk, git_object_id(revspec.to), &opts);

out:
	git_object_free(revspec.from);
	git_object_free(revspec.to);
	return error;
}