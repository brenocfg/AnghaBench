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
struct object {int /*<<< orphan*/  flags; } ;
struct all_refs_cb {int warned_bad_reflog; int /*<<< orphan*/  name_for_errormsg; TYPE_1__* all_revs; int /*<<< orphan*/  all_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  repo; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_pending_object (TYPE_1__*,struct object*,char*) ; 
 int /*<<< orphan*/  is_null_oid (struct object_id*) ; 
 struct object* parse_object (int /*<<< orphan*/ ,struct object_id*) ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_one_reflog_commit(struct object_id *oid, void *cb_data)
{
	struct all_refs_cb *cb = cb_data;
	if (!is_null_oid(oid)) {
		struct object *o = parse_object(cb->all_revs->repo, oid);
		if (o) {
			o->flags |= cb->all_flags;
			/* ??? CMDLINEFLAGS ??? */
			add_pending_object(cb->all_revs, o, "");
		}
		else if (!cb->warned_bad_reflog) {
			warning("reflog of '%s' references pruned commits",
				cb->name_for_errormsg);
			cb->warned_bad_reflog = 1;
		}
	}
}