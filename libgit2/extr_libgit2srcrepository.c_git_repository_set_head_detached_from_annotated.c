#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_4__ {int /*<<< orphan*/  description; } ;
typedef  TYPE_1__ git_annotated_commit ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int detach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_annotated_commit_id (TYPE_1__ const*) ; 

int git_repository_set_head_detached_from_annotated(
	git_repository *repo,
	const git_annotated_commit *commitish)
{
	assert(repo && commitish);

	return detach(repo, git_annotated_commit_id(commitish), commitish->description);
}