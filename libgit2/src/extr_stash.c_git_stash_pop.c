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
typedef  int /*<<< orphan*/  git_stash_apply_options ;
typedef  int /*<<< orphan*/  git_repository ;

/* Variables and functions */
 int git_stash_apply (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/  const*) ; 
 int git_stash_drop (int /*<<< orphan*/ *,size_t) ; 

int git_stash_pop(
	git_repository *repo,
	size_t index,
	const git_stash_apply_options *options)
{
	int error;

	if ((error = git_stash_apply(repo, index, options)) < 0)
		return error;

	return git_stash_drop(repo, index);
}