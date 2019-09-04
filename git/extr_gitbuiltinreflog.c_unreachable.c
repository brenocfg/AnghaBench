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
struct object_id {int dummy; } ;
struct expire_reflog_policy_cb {scalar_t__ mark_limit; scalar_t__ mark_list; } ;
struct TYPE_2__ {int flags; } ;
struct commit {TYPE_1__ object; } ;

/* Variables and functions */
 int REACHABLE ; 
 scalar_t__ is_null_oid (struct object_id*) ; 
 struct commit* lookup_commit_reference_gently (int /*<<< orphan*/ ,struct object_id*,int) ; 
 int /*<<< orphan*/  mark_reachable (struct expire_reflog_policy_cb*) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static int unreachable(struct expire_reflog_policy_cb *cb, struct commit *commit, struct object_id *oid)
{
	/*
	 * We may or may not have the commit yet - if not, look it
	 * up using the supplied sha1.
	 */
	if (!commit) {
		if (is_null_oid(oid))
			return 0;

		commit = lookup_commit_reference_gently(the_repository, oid,
							1);

		/* Not a commit -- keep it */
		if (!commit)
			return 0;
	}

	/* Reachable from the current ref?  Don't prune. */
	if (commit->object.flags & REACHABLE)
		return 0;

	if (cb->mark_list && cb->mark_limit) {
		cb->mark_limit = 0; /* dig down to the root */
		mark_reachable(cb);
	}

	return !(commit->object.flags & REACHABLE);
}