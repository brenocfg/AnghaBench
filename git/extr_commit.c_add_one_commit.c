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
struct rev_collect {scalar_t__ nr; struct commit** commit; int /*<<< orphan*/  alloc; } ;
struct object_id {int dummy; } ;
struct TYPE_2__ {int flags; } ;
struct commit {TYPE_1__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (struct commit**,scalar_t__,int /*<<< orphan*/ ) ; 
 int TMP_MARK ; 
 scalar_t__ is_null_oid (struct object_id*) ; 
 struct commit* lookup_commit (int /*<<< orphan*/ ,struct object_id*) ; 
 scalar_t__ parse_commit (struct commit*) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static void add_one_commit(struct object_id *oid, struct rev_collect *revs)
{
	struct commit *commit;

	if (is_null_oid(oid))
		return;

	commit = lookup_commit(the_repository, oid);
	if (!commit ||
	    (commit->object.flags & TMP_MARK) ||
	    parse_commit(commit))
		return;

	ALLOC_GROW(revs->commit, revs->nr + 1, revs->alloc);
	revs->commit[revs->nr++] = commit;
	commit->object.flags |= TMP_MARK;
}