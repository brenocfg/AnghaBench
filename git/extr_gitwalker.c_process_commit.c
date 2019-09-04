#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct walker {int dummy; } ;
struct commit_list {TYPE_3__* item; struct commit_list* next; } ;
struct TYPE_8__ {int flags; int /*<<< orphan*/  oid; } ;
struct commit {scalar_t__ date; struct commit_list* parents; TYPE_2__ object; } ;
struct TYPE_11__ {int /*<<< orphan*/  object; } ;
struct TYPE_10__ {TYPE_1__* item; } ;
struct TYPE_9__ {int /*<<< orphan*/  object; } ;
struct TYPE_7__ {scalar_t__ date; } ;

/* Variables and functions */
 int COMPLETE ; 
 TYPE_4__* complete ; 
 int /*<<< orphan*/  current_commit_oid ; 
 TYPE_5__* get_commit_tree (struct commit*) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ parse_commit (struct commit*) ; 
 int /*<<< orphan*/  pop_most_recent_commit (TYPE_4__**,int) ; 
 scalar_t__ process (struct walker*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  walker_say (struct walker*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int process_commit(struct walker *walker, struct commit *commit)
{
	struct commit_list *parents;

	if (parse_commit(commit))
		return -1;

	while (complete && complete->item->date >= commit->date) {
		pop_most_recent_commit(&complete, COMPLETE);
	}

	if (commit->object.flags & COMPLETE)
		return 0;

	oidcpy(&current_commit_oid, &commit->object.oid);

	walker_say(walker, "walk %s\n", oid_to_hex(&commit->object.oid));

	if (process(walker, &get_commit_tree(commit)->object))
		return -1;

	for (parents = commit->parents; parents; parents = parents->next) {
		if (process(walker, &parents->item->object))
			return -1;
	}

	return 0;
}