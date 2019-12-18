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
struct TYPE_2__ {scalar_t__ expire_unreachable; scalar_t__ expire_total; } ;
struct expire_reflog_policy_cb {scalar_t__ unreachable_expire_kind; scalar_t__ mark_limit; TYPE_1__ cmd; int /*<<< orphan*/ * mark_list; int /*<<< orphan*/ * tip_commit; struct commit_list* tips; } ;
struct commit_list {int /*<<< orphan*/ * item; struct commit_list* next; } ;

/* Variables and functions */
 scalar_t__ UE_ALWAYS ; 
 scalar_t__ UE_HEAD ; 
 scalar_t__ UE_NORMAL ; 
 int /*<<< orphan*/  commit_list_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  for_each_ref (int /*<<< orphan*/ ,struct commit_list**) ; 
 scalar_t__ is_head (char const*) ; 
 int /*<<< orphan*/ * lookup_commit_reference_gently (int /*<<< orphan*/ ,struct object_id const*,int) ; 
 int /*<<< orphan*/  mark_reachable (struct expire_reflog_policy_cb*) ; 
 int /*<<< orphan*/  push_tip_to_list ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static void reflog_expiry_prepare(const char *refname,
				  const struct object_id *oid,
				  void *cb_data)
{
	struct expire_reflog_policy_cb *cb = cb_data;

	if (!cb->cmd.expire_unreachable || is_head(refname)) {
		cb->tip_commit = NULL;
		cb->unreachable_expire_kind = UE_HEAD;
	} else {
		cb->tip_commit = lookup_commit_reference_gently(the_repository,
								oid, 1);
		if (!cb->tip_commit)
			cb->unreachable_expire_kind = UE_ALWAYS;
		else
			cb->unreachable_expire_kind = UE_NORMAL;
	}

	if (cb->cmd.expire_unreachable <= cb->cmd.expire_total)
		cb->unreachable_expire_kind = UE_ALWAYS;

	cb->mark_list = NULL;
	cb->tips = NULL;
	if (cb->unreachable_expire_kind != UE_ALWAYS) {
		if (cb->unreachable_expire_kind == UE_HEAD) {
			struct commit_list *elem;

			for_each_ref(push_tip_to_list, &cb->tips);
			for (elem = cb->tips; elem; elem = elem->next)
				commit_list_insert(elem->item, &cb->mark_list);
		} else {
			commit_list_insert(cb->tip_commit, &cb->mark_list);
		}
		cb->mark_limit = cb->cmd.expire_total;
		mark_reachable(cb);
	}
}