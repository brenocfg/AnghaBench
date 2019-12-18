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
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_reference ;
struct TYPE_3__ {int /*<<< orphan*/  description; int /*<<< orphan*/  commit; } ;
typedef  TYPE_1__ git_annotated_commit ;

/* Variables and functions */
 int create_branch (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int git_branch_create_from_annotated(
	git_reference **ref_out,
	git_repository *repository,
	const char *branch_name,
	const git_annotated_commit *commit,
	int force)
{
	return create_branch(ref_out,
		repository, branch_name, commit->commit, commit->description, force);
}