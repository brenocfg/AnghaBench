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
typedef  scalar_t__ timestamp_t ;
struct object_id {int dummy; } ;
struct TYPE_2__ {scalar_t__ expire_total; scalar_t__ expire_unreachable; scalar_t__ recno; scalar_t__ stalefix; } ;
struct expire_reflog_policy_cb {scalar_t__ unreachable_expire_kind; TYPE_1__ cmd; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 scalar_t__ UE_ALWAYS ; 
 int /*<<< orphan*/  keep_entry (struct commit**,struct object_id*) ; 
 scalar_t__ unreachable (struct expire_reflog_policy_cb*,struct commit*,struct object_id*) ; 

__attribute__((used)) static int should_expire_reflog_ent(struct object_id *ooid, struct object_id *noid,
				    const char *email, timestamp_t timestamp, int tz,
				    const char *message, void *cb_data)
{
	struct expire_reflog_policy_cb *cb = cb_data;
	struct commit *old_commit, *new_commit;

	if (timestamp < cb->cmd.expire_total)
		return 1;

	old_commit = new_commit = NULL;
	if (cb->cmd.stalefix &&
	    (!keep_entry(&old_commit, ooid) || !keep_entry(&new_commit, noid)))
		return 1;

	if (timestamp < cb->cmd.expire_unreachable) {
		if (cb->unreachable_expire_kind == UE_ALWAYS)
			return 1;
		if (unreachable(cb, old_commit, ooid) || unreachable(cb, new_commit, noid))
			return 1;
	}

	if (cb->cmd.recno && --(cb->cmd.recno) == 0)
		return 1;

	return 0;
}