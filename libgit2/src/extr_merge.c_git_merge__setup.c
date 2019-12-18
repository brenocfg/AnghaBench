#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_annotated_commit ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_annotated_commit_id (int /*<<< orphan*/  const*) ; 
 int git_repository__set_orig_head (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int write_merge_head (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,size_t) ; 
 int write_merge_mode (int /*<<< orphan*/ *) ; 
 int write_merge_msg (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,size_t) ; 

int git_merge__setup(
	git_repository *repo,
	const git_annotated_commit *our_head,
	const git_annotated_commit *heads[],
	size_t heads_len)
{
	int error = 0;

	assert (repo && our_head && heads);

	if ((error = git_repository__set_orig_head(repo, git_annotated_commit_id(our_head))) == 0 &&
		(error = write_merge_head(repo, heads, heads_len)) == 0 &&
		(error = write_merge_mode(repo)) == 0) {
		error = write_merge_msg(repo, heads, heads_len);
	}

	return error;
}