#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rev_info {int reverse_output_stage; int linear; int /*<<< orphan*/ * previous_parents; scalar_t__ graph; scalar_t__ track_linear; struct commit_list* commits; scalar_t__ reverse; } ;
struct commit_list {int dummy; } ;
struct TYPE_2__ {int flags; } ;
struct commit {TYPE_1__ object; } ;

/* Variables and functions */
 int TRACK_LINEAR ; 
 int /*<<< orphan*/  commit_list_insert (struct commit*,struct commit_list**) ; 
 int /*<<< orphan*/  free_commit_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_saved_parents (struct rev_info*) ; 
 struct commit* get_revision_internal (struct rev_info*) ; 
 int /*<<< orphan*/  graph_update (scalar_t__,struct commit*) ; 
 struct commit* pop_commit (struct commit_list**) ; 

struct commit *get_revision(struct rev_info *revs)
{
	struct commit *c;
	struct commit_list *reversed;

	if (revs->reverse) {
		reversed = NULL;
		while ((c = get_revision_internal(revs)))
			commit_list_insert(c, &reversed);
		revs->commits = reversed;
		revs->reverse = 0;
		revs->reverse_output_stage = 1;
	}

	if (revs->reverse_output_stage) {
		c = pop_commit(&revs->commits);
		if (revs->track_linear)
			revs->linear = !!(c && c->object.flags & TRACK_LINEAR);
		return c;
	}

	c = get_revision_internal(revs);
	if (c && revs->graph)
		graph_update(revs->graph, c);
	if (!c) {
		free_saved_parents(revs);
		if (revs->previous_parents) {
			free_commit_list(revs->previous_parents);
			revs->previous_parents = NULL;
		}
	}
	return c;
}