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
struct TYPE_3__ {int /*<<< orphan*/  iterator_reverse; } ;
typedef  TYPE_1__ git_revwalk ;
typedef  int /*<<< orphan*/  git_commit_list_node ;

/* Variables and functions */
 int GIT_ITEROVER ; 
 int /*<<< orphan*/ * git_commit_list_pop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int revwalk_next_reverse(git_commit_list_node **object_out, git_revwalk *walk)
{
	*object_out = git_commit_list_pop(&walk->iterator_reverse);
	return *object_out ? 0 : GIT_ITEROVER;
}