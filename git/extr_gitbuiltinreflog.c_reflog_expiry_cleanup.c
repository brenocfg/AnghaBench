#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct expire_reflog_policy_cb {scalar_t__ unreachable_expire_kind; int /*<<< orphan*/  tip_commit; struct commit_list* tips; } ;
struct commit_list {int /*<<< orphan*/  item; struct commit_list* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  REACHABLE ; 
 scalar_t__ UE_ALWAYS ; 
 scalar_t__ UE_HEAD ; 
 int /*<<< orphan*/  clear_commit_marks (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_commit_list (struct commit_list*) ; 

__attribute__((used)) static void reflog_expiry_cleanup(void *cb_data)
{
	struct expire_reflog_policy_cb *cb = cb_data;

	if (cb->unreachable_expire_kind != UE_ALWAYS) {
		if (cb->unreachable_expire_kind == UE_HEAD) {
			struct commit_list *elem;
			for (elem = cb->tips; elem; elem = elem->next)
				clear_commit_marks(elem->item, REACHABLE);
			free_commit_list(cb->tips);
		} else {
			clear_commit_marks(cb->tip_commit, REACHABLE);
		}
	}
}