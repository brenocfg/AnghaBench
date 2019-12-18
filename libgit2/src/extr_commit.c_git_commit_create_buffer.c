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
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_signature ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_commit ;
typedef  int /*<<< orphan*/  git_buf ;
typedef  int /*<<< orphan*/  git_array_oid_t ;
struct TYPE_3__ {size_t member_0; int /*<<< orphan*/ * member_2; int /*<<< orphan*/  const** member_1; } ;
typedef  TYPE_1__ commit_parent_data ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ARRAY_INIT ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  commit_parent_from_array ; 
 int /*<<< orphan*/  git_array_clear (int /*<<< orphan*/ ) ; 
 int git_commit__create_buffer_internal (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,char const*,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_tree_id (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * git_tree_owner (int /*<<< orphan*/  const*) ; 
 int validate_tree_and_parents (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int) ; 

int git_commit_create_buffer(git_buf *out,
	git_repository *repo,
	const git_signature *author,
	const git_signature *committer,
	const char *message_encoding,
	const char *message,
	const git_tree *tree,
	size_t parent_count,
	const git_commit *parents[])
{
	int error;
	commit_parent_data data = { parent_count, parents, repo };
	git_array_oid_t parents_arr = GIT_ARRAY_INIT;
	const git_oid *tree_id;

	assert(tree && git_tree_owner(tree) == repo);

	tree_id = git_tree_id(tree);

	if ((error = validate_tree_and_parents(&parents_arr, repo, tree_id, commit_parent_from_array, &data, NULL, true)) < 0)
		return error;

	error = git_commit__create_buffer_internal(
		out, author, committer,
		message_encoding, message, tree_id,
		&parents_arr);

	git_array_clear(parents_arr);
	return error;
}