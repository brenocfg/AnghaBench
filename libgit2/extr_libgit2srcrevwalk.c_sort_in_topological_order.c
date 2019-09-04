#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * git_vector_cmp ;
struct TYPE_12__ {int sorting; } ;
typedef  TYPE_1__ git_revwalk ;
typedef  int /*<<< orphan*/  git_pqueue ;
struct TYPE_13__ {int in_degree; unsigned short out_degree; struct TYPE_13__** parents; } ;
typedef  TYPE_2__ git_commit_list_node ;
struct TYPE_14__ {TYPE_2__* item; struct TYPE_14__* next; } ;
typedef  TYPE_3__ git_commit_list ;
struct TYPE_15__ {TYPE_3__* next; } ;

/* Variables and functions */
 int GIT_SORT_TIME ; 
 TYPE_9__* git_commit_list_insert (TYPE_2__*,TYPE_3__**) ; 
 int /*<<< orphan*/ * git_commit_list_time_cmp ; 
 int /*<<< orphan*/  git_pqueue_free (int /*<<< orphan*/ *) ; 
 int git_pqueue_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int git_pqueue_insert (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_2__* git_pqueue_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_pqueue_reverse (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sort_in_topological_order(git_commit_list **out, git_revwalk *walk, git_commit_list *list)
{
	git_commit_list *ll = NULL, *newlist, **pptr;
	git_commit_list_node *next;
	git_pqueue queue;
	git_vector_cmp queue_cmp = NULL;
	unsigned short i;
	int error;

	if (walk->sorting & GIT_SORT_TIME)
		queue_cmp = git_commit_list_time_cmp;

	if ((error = git_pqueue_init(&queue, 0, 8, queue_cmp)))
		return error;

	/*
	 * Start by resetting the in-degree to 1 for the commits in
	 * our list. We want to go through this list again, so we
	 * store it in the commit list as we extract it from the lower
	 * machinery.
	 */
	for (ll = list; ll; ll = ll->next) {
		ll->item->in_degree = 1;
	}

	/*
	 * Count up how many children each commit has. We limit
	 * ourselves to those commits in the original list (in-degree
	 * of 1) avoiding setting it for any parent that was hidden.
	 */
	for(ll = list; ll; ll = ll->next) {
		for (i = 0; i < ll->item->out_degree; ++i) {
			git_commit_list_node *parent = ll->item->parents[i];
			if (parent->in_degree)
				parent->in_degree++;
		}
	}

	/*
	 * Now we find the tips i.e. those not reachable from any other node
	 * i.e. those which still have an in-degree of 1.
	 */
	for(ll = list; ll; ll = ll->next) {
		if (ll->item->in_degree == 1) {
			if ((error = git_pqueue_insert(&queue, ll->item)))
				goto cleanup;
		}
	}

	/*
	 * We need to output the tips in the order that they came out of the
	 * traversal, so if we're not doing time-sorting, we need to reverse the
	 * pqueue in order to get them to come out as we inserted them.
	 */
	if ((walk->sorting & GIT_SORT_TIME) == 0)
		git_pqueue_reverse(&queue);


	pptr = &newlist;
	newlist = NULL;
	while ((next = git_pqueue_pop(&queue)) != NULL) {
		for (i = 0; i < next->out_degree; ++i) {
			git_commit_list_node *parent = next->parents[i];
			if (parent->in_degree == 0)
				continue;

			if (--parent->in_degree == 1) {
				if ((error = git_pqueue_insert(&queue, parent)))
					goto cleanup;
			}
		}

		/* All the children of 'item' have been emitted (since we got to it via the priority queue) */
		next->in_degree = 0;

		pptr = &git_commit_list_insert(next, pptr)->next;
	}

	*out = newlist;
	error = 0;

cleanup:
	git_pqueue_free(&queue);
	return error;
}