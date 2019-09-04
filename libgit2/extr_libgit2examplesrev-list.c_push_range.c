#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_revwalk ;
struct TYPE_3__ {int flags; int /*<<< orphan*/  to; int /*<<< orphan*/  from; } ;
typedef  TYPE_1__ git_revspec ;
typedef  int /*<<< orphan*/  git_repository ;

/* Variables and functions */
 int GIT_EINVALIDSPEC ; 
 int GIT_REVPARSE_MERGE_BASE ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_object_id (int /*<<< orphan*/ ) ; 
 int git_revparse (TYPE_1__*,int /*<<< orphan*/ *,char const*) ; 
 int push_commit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int push_range(git_repository *repo, git_revwalk *walk, const char *range, int hide)
{
	git_revspec revspec;
	int error = 0;

	if ((error = git_revparse(&revspec, repo, range)))
		return error;

	if (revspec.flags & GIT_REVPARSE_MERGE_BASE) {
		/* TODO: support "<commit>...<commit>" */
		return GIT_EINVALIDSPEC;
	}

	if ((error = push_commit(walk, git_object_id(revspec.from), !hide)))
		goto out;

	error = push_commit(walk, git_object_id(revspec.to), hide);

out:
	git_object_free(revspec.from);
	git_object_free(revspec.to);
	return error;
}