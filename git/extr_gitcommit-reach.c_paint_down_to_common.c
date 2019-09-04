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
typedef  int uint32_t ;
struct repository {int dummy; } ;
struct prio_queue {int /*<<< orphan*/  compare; int /*<<< orphan*/  member_0; } ;
struct commit_list {struct commit_list* next; struct commit* item; } ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  oid; } ;
struct commit {int generation; TYPE_1__ object; struct commit_list* parents; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*,int,int,int /*<<< orphan*/ ) ; 
 int GENERATION_NUMBER_INFINITY ; 
 int PARENT1 ; 
 int PARENT2 ; 
 int RESULT ; 
 int STALE ; 
 int /*<<< orphan*/  clear_prio_queue (struct prio_queue*) ; 
 int /*<<< orphan*/  commit_list_append (struct commit*,struct commit_list**) ; 
 int /*<<< orphan*/  commit_list_insert_by_date (struct commit*,struct commit_list**) ; 
 int /*<<< orphan*/  compare_commits_by_commit_date ; 
 int /*<<< orphan*/  compare_commits_by_gen_then_commit_date ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 struct commit* prio_queue_get (struct prio_queue*) ; 
 int /*<<< orphan*/  prio_queue_put (struct prio_queue*,struct commit*) ; 
 scalar_t__ queue_has_nonstale (struct prio_queue*) ; 
 scalar_t__ repo_parse_commit (struct repository*,struct commit*) ; 

__attribute__((used)) static struct commit_list *paint_down_to_common(struct repository *r,
						struct commit *one, int n,
						struct commit **twos,
						int min_generation)
{
	struct prio_queue queue = { compare_commits_by_gen_then_commit_date };
	struct commit_list *result = NULL;
	int i;
	uint32_t last_gen = GENERATION_NUMBER_INFINITY;

	if (!min_generation)
		queue.compare = compare_commits_by_commit_date;

	one->object.flags |= PARENT1;
	if (!n) {
		commit_list_append(one, &result);
		return result;
	}
	prio_queue_put(&queue, one);

	for (i = 0; i < n; i++) {
		twos[i]->object.flags |= PARENT2;
		prio_queue_put(&queue, twos[i]);
	}

	while (queue_has_nonstale(&queue)) {
		struct commit *commit = prio_queue_get(&queue);
		struct commit_list *parents;
		int flags;

		if (min_generation && commit->generation > last_gen)
			BUG("bad generation skip %8x > %8x at %s",
			    commit->generation, last_gen,
			    oid_to_hex(&commit->object.oid));
		last_gen = commit->generation;

		if (commit->generation < min_generation)
			break;

		flags = commit->object.flags & (PARENT1 | PARENT2 | STALE);
		if (flags == (PARENT1 | PARENT2)) {
			if (!(commit->object.flags & RESULT)) {
				commit->object.flags |= RESULT;
				commit_list_insert_by_date(commit, &result);
			}
			/* Mark parents of a found merge stale */
			flags |= STALE;
		}
		parents = commit->parents;
		while (parents) {
			struct commit *p = parents->item;
			parents = parents->next;
			if ((p->object.flags & flags) == flags)
				continue;
			if (repo_parse_commit(r, p))
				return NULL;
			p->object.flags |= flags;
			prio_queue_put(&queue, p);
		}
	}

	clear_prio_queue(&queue);
	return result;
}