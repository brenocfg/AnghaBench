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
struct rev_collect {int initial; int nr; TYPE_2__** commit; } ;
struct object_id {int dummy; } ;
struct commit_list {struct commit* item; scalar_t__ next; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;
struct commit {TYPE_1__ object; } ;
typedef  int /*<<< orphan*/  revs ;
struct TYPE_4__ {TYPE_1__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  TMP_MARK ; 
 int /*<<< orphan*/  add_one_commit (struct object_id*,struct rev_collect*) ; 
 int /*<<< orphan*/  collect_one_reflog_ent ; 
 int /*<<< orphan*/  for_each_reflog_ent (char const*,int /*<<< orphan*/ ,struct rev_collect*) ; 
 int /*<<< orphan*/  free_commit_list (struct commit_list*) ; 
 struct commit_list* get_merge_bases_many (struct commit*,int,TYPE_2__**) ; 
 int /*<<< orphan*/  get_oid (char const*,struct object_id*) ; 
 int /*<<< orphan*/  memset (struct rev_collect*,int /*<<< orphan*/ ,int) ; 

struct commit *get_fork_point(const char *refname, struct commit *commit)
{
	struct object_id oid;
	struct rev_collect revs;
	struct commit_list *bases;
	int i;
	struct commit *ret = NULL;

	memset(&revs, 0, sizeof(revs));
	revs.initial = 1;
	for_each_reflog_ent(refname, collect_one_reflog_ent, &revs);

	if (!revs.nr && !get_oid(refname, &oid))
		add_one_commit(&oid, &revs);

	for (i = 0; i < revs.nr; i++)
		revs.commit[i]->object.flags &= ~TMP_MARK;

	bases = get_merge_bases_many(commit, revs.nr, revs.commit);

	/*
	 * There should be one and only one merge base, when we found
	 * a common ancestor among reflog entries.
	 */
	if (!bases || bases->next)
		goto cleanup_return;

	/* And the found one must be one of the reflog entries */
	for (i = 0; i < revs.nr; i++)
		if (&bases->item->object == &revs.commit[i]->object)
			break; /* found */
	if (revs.nr <= i)
		goto cleanup_return;

	ret = bases->item;

cleanup_return:
	free_commit_list(bases);
	return ret;
}