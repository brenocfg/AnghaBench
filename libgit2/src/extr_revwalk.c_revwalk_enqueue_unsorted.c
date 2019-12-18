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
struct TYPE_3__ {int /*<<< orphan*/  iterator_rand; } ;
typedef  TYPE_1__ git_revwalk ;
typedef  int /*<<< orphan*/  git_commit_list_node ;

/* Variables and functions */
 scalar_t__ git_commit_list_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int revwalk_enqueue_unsorted(git_revwalk *walk, git_commit_list_node *commit)
{
	return git_commit_list_insert(commit, &walk->iterator_rand) ? 0 : -1;
}