#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct possible_tag {int flag_within; int /*<<< orphan*/  depth; } ;
typedef  int /*<<< orphan*/  git_revwalk ;
typedef  int /*<<< orphan*/  git_pqueue ;
struct TYPE_6__ {int flags; int out_degree; struct TYPE_6__** parents; } ;
typedef  TYPE_1__ git_commit_list_node ;

/* Variables and functions */
 int SEEN ; 
 int git_commit_list_parse (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* git_pqueue_get (int /*<<< orphan*/ *,size_t) ; 
 int git_pqueue_insert (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* git_pqueue_pop (int /*<<< orphan*/ *) ; 
 size_t git_pqueue_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned long finish_depth_computation(
	git_pqueue *list,
	git_revwalk *walk,
	struct possible_tag *best)
{
	unsigned long seen_commits = 0;
	int error, i;

	while (git_pqueue_size(list) > 0) {
		git_commit_list_node *c = git_pqueue_pop(list);
		seen_commits++;
		if (c->flags & best->flag_within) {
			size_t index = 0;
			while (git_pqueue_size(list) > index) {
				git_commit_list_node *i = git_pqueue_get(list, index);
				if (!(i->flags & best->flag_within))
					break;
				index++;
			}
			if (index > git_pqueue_size(list))
				break;
		} else
			best->depth++;
		for (i = 0; i < c->out_degree; i++) {
			git_commit_list_node *p = c->parents[i];
			if ((error = git_commit_list_parse(walk, p)) < 0)
				return error;
			if (!(p->flags & SEEN))
				if ((error = git_pqueue_insert(list, p)) < 0)
					return error;
			p->flags |= c->flags;
		}
	}
	return seen_commits;
}