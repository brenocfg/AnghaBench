#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct object_id {int dummy; } ;
struct entry {int /*<<< orphan*/  ttl; struct commit* commit; } ;
struct TYPE_4__ {scalar_t__ nr; } ;
struct data {scalar_t__ non_common_revs; TYPE_2__ rev_list; } ;
struct commit_list {int /*<<< orphan*/  item; struct commit_list* next; } ;
struct TYPE_3__ {int flags; struct object_id const oid; } ;
struct commit {TYPE_1__ object; struct commit_list* parents; } ;

/* Variables and functions */
 int COMMON ; 
 int POPPED ; 
 int /*<<< orphan*/  free (struct entry*) ; 
 int /*<<< orphan*/  parse_commit (struct commit*) ; 
 struct entry* prio_queue_get (TYPE_2__*) ; 
 int push_parent (struct data*,struct entry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct object_id *get_rev(struct data *data)
{
	struct commit *to_send = NULL;

	while (to_send == NULL) {
		struct entry *entry;
		struct commit *commit;
		struct commit_list *p;
		int parent_pushed = 0;

		if (data->rev_list.nr == 0 || data->non_common_revs == 0)
			return NULL;

		entry = prio_queue_get(&data->rev_list);
		commit = entry->commit;
		commit->object.flags |= POPPED;
		if (!(commit->object.flags & COMMON))
			data->non_common_revs--;

		if (!(commit->object.flags & COMMON) && !entry->ttl)
			to_send = commit;

		parse_commit(commit);
		for (p = commit->parents; p; p = p->next)
			parent_pushed |= push_parent(data, entry, p->item);

		if (!(commit->object.flags & COMMON) && !parent_pushed)
			/*
			 * This commit has no parents, or all of its parents
			 * have already been popped (due to clock skew), so send
			 * it anyway.
			 */
			to_send = commit;

		free(entry);
	}

	return &to_send->object.oid;
}