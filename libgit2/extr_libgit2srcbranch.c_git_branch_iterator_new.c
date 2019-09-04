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
typedef  int /*<<< orphan*/  git_branch_t ;
typedef  int /*<<< orphan*/  git_branch_iterator ;
struct TYPE_5__ {int /*<<< orphan*/  iter; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ branch_iter ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_1__*) ; 
 TYPE_1__* git__calloc (int,int) ; 
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 
 scalar_t__ git_reference_iterator_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int git_branch_iterator_new(
	git_branch_iterator **out,
	git_repository *repo,
	git_branch_t list_flags)
{
	branch_iter *iter;

	iter = git__calloc(1, sizeof(branch_iter));
	GIT_ERROR_CHECK_ALLOC(iter);

	iter->flags = list_flags;

	if (git_reference_iterator_new(&iter->iter, repo) < 0) {
		git__free(iter);
		return -1;
	}

	*out = (git_branch_iterator *) iter;

	return 0;
}