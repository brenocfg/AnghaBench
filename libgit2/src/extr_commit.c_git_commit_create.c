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
struct TYPE_3__ {size_t member_0; int /*<<< orphan*/ * member_2; int /*<<< orphan*/  const** member_1; } ;
typedef  TYPE_1__ commit_parent_data ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  commit_parent_from_array ; 
 int git_commit__create_internal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  git_tree_id (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * git_tree_owner (int /*<<< orphan*/  const*) ; 

int git_commit_create(
	git_oid *id,
	git_repository *repo,
	const char *update_ref,
	const git_signature *author,
	const git_signature *committer,
	const char *message_encoding,
	const char *message,
	const git_tree *tree,
	size_t parent_count,
	const git_commit *parents[])
{
	commit_parent_data data = { parent_count, parents, repo };

	assert(tree && git_tree_owner(tree) == repo);

	return git_commit__create_internal(
		id, repo, update_ref, author, committer,
		message_encoding, message, git_tree_id(tree),
		commit_parent_from_array, &data, false);
}