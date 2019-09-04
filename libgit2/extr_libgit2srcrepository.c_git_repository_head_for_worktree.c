#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_reference ;
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_HEAD_FILE ; 
 scalar_t__ GIT_REFERENCE_DIRECT ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int get_worktree_file_path (TYPE_1__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int git_reference__read_head (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int git_reference_lookup_resolved (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  git_reference_symbolic_target (int /*<<< orphan*/ *) ; 
 scalar_t__ git_reference_type (int /*<<< orphan*/ *) ; 

int git_repository_head_for_worktree(git_reference **out, git_repository *repo, const char *name)
{
	git_buf path = GIT_BUF_INIT;
	git_reference *head = NULL;
	int error;

	assert(out && repo && name);

	*out = NULL;

	if ((error = get_worktree_file_path(&path, repo, name, GIT_HEAD_FILE)) < 0 ||
	    (error = git_reference__read_head(&head, repo, path.ptr)) < 0)
		goto out;

	if (git_reference_type(head) != GIT_REFERENCE_DIRECT) {
		git_reference *resolved;

		error = git_reference_lookup_resolved(&resolved, repo, git_reference_symbolic_target(head), -1);
		git_reference_free(head);
		head = resolved;
	}

	*out = head;

out:
	if (error)
		git_reference_free(head);

	git_buf_dispose(&path);

	return error;
}