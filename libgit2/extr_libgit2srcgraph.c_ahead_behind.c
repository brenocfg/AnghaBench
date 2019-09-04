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
typedef  int /*<<< orphan*/  git_pqueue ;
struct TYPE_6__ {int flags; int out_degree; struct TYPE_6__** parents; } ;
typedef  TYPE_1__ git_commit_list_node ;

/* Variables and functions */
 int PARENT1 ; 
 int PARENT2 ; 
 int RESULT ; 
 int /*<<< orphan*/  git_commit_list_time_cmp ; 
 int /*<<< orphan*/  git_pqueue_free (int /*<<< orphan*/ *) ; 
 scalar_t__ git_pqueue_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int git_pqueue_insert (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* git_pqueue_pop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ahead_behind(git_commit_list_node *one, git_commit_list_node *two,
	size_t *ahead, size_t *behind)
{
	git_commit_list_node *commit;
	git_pqueue pq;
	int error = 0, i;
	*ahead = 0;
	*behind = 0;

	if (git_pqueue_init(&pq, 0, 2, git_commit_list_time_cmp) < 0)
		return -1;

	if ((error = git_pqueue_insert(&pq, one)) < 0 ||
		(error = git_pqueue_insert(&pq, two)) < 0)
		goto done;

	while ((commit = git_pqueue_pop(&pq)) != NULL) {
		if (commit->flags & RESULT ||
			(commit->flags & (PARENT1 | PARENT2)) == (PARENT1 | PARENT2))
			continue;
		else if (commit->flags & PARENT1)
			(*ahead)++;
		else if (commit->flags & PARENT2)
			(*behind)++;

		for (i = 0; i < commit->out_degree; i++) {
			git_commit_list_node *p = commit->parents[i];
			if ((error = git_pqueue_insert(&pq, p)) < 0)
				goto done;
		}
		commit->flags |= RESULT;
	}

done:
	git_pqueue_free(&pq);
	return error;
}