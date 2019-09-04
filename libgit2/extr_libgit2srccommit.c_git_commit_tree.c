#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_tree ;
struct TYPE_5__ {int /*<<< orphan*/  repo; } ;
struct TYPE_6__ {int /*<<< orphan*/  tree_id; TYPE_1__ object; } ;
typedef  TYPE_2__ git_commit ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_2__ const*) ; 
 int git_tree_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int git_commit_tree(git_tree **tree_out, const git_commit *commit)
{
	assert(commit);
	return git_tree_lookup(tree_out, commit->object.repo, &commit->tree_id);
}