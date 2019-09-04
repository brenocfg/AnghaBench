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
struct walk_object {scalar_t__ uninteresting; scalar_t__ seen; } ;
struct TYPE_4__ {int /*<<< orphan*/  user_input; } ;
typedef  TYPE_1__ git_revwalk ;
typedef  int /*<<< orphan*/  git_packbuilder ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int GIT_ITEROVER ; 
 int /*<<< orphan*/  assert (int) ; 
 int git_revwalk_next (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int insert_commit (int /*<<< orphan*/ *,struct walk_object*) ; 
 int mark_edges_uninteresting (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int retrieve_object (struct walk_object**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int git_packbuilder_insert_walk(git_packbuilder *pb, git_revwalk *walk)
{
	int error;
	git_oid id;
	struct walk_object *obj;

	assert(pb && walk);

	if ((error = mark_edges_uninteresting(pb, walk->user_input)) < 0)
		return error;

	/*
	 * TODO: git marks the parents of the edges
	 * uninteresting. This may provide a speed advantage, but does
	 * seem to assume the remote does not have a single-commit
	 * history on the other end.
	 */

	/* walk down each tree up to the blobs and insert them, stopping when uninteresting */
	while ((error = git_revwalk_next(&id, walk)) == 0) {
		if ((error = retrieve_object(&obj, pb, &id)) < 0)
			return error;

		if (obj->seen || obj->uninteresting)
			continue;

		if ((error = insert_commit(pb, obj)) < 0)
			return error;
	}

	if (error == GIT_ITEROVER)
		error = 0;

	return error;
}