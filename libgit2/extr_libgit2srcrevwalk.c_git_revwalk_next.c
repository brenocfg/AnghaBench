#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int (* get_next ) (TYPE_2__**,TYPE_1__*) ;int /*<<< orphan*/  walking; } ;
typedef  TYPE_1__ git_revwalk ;
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_9__ {int /*<<< orphan*/  oid; } ;
typedef  TYPE_2__ git_commit_list_node ;

/* Variables and functions */
 int GIT_ITEROVER ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revwalk_reset (TYPE_1__*) ; 
 int prepare_walk (TYPE_1__*) ; 
 int stub1 (TYPE_2__**,TYPE_1__*) ; 

int git_revwalk_next(git_oid *oid, git_revwalk *walk)
{
	int error;
	git_commit_list_node *next;

	assert(walk && oid);

	if (!walk->walking) {
		if ((error = prepare_walk(walk)) < 0)
			return error;
	}

	error = walk->get_next(&next, walk);

	if (error == GIT_ITEROVER) {
		git_revwalk_reset(walk);
		git_error_clear();
		return GIT_ITEROVER;
	}

	if (!error)
		git_oid_cpy(oid, &next->oid);

	return error;
}