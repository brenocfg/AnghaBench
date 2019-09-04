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
struct string_list {int nr; TYPE_1__* items; } ;
struct rerere_id {int dummy; } ;
struct repository {int dummy; } ;
struct TYPE_2__ {struct rerere_id* util; } ;

/* Variables and functions */
 int /*<<< orphan*/  git_path_merge_rr (struct repository*) ; 
 int /*<<< orphan*/  has_rerere_resolution (struct rerere_id*) ; 
 int /*<<< orphan*/  rerere_path (struct rerere_id*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rmdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rollback_lock_file (int /*<<< orphan*/ *) ; 
 scalar_t__ setup_rerere (struct repository*,struct string_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink_or_warn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink_rr_item (struct rerere_id*) ; 
 int /*<<< orphan*/  write_lock ; 

void rerere_clear(struct repository *r, struct string_list *merge_rr)
{
	int i;

	if (setup_rerere(r, merge_rr, 0) < 0)
		return;

	for (i = 0; i < merge_rr->nr; i++) {
		struct rerere_id *id = merge_rr->items[i].util;
		if (!has_rerere_resolution(id)) {
			unlink_rr_item(id);
			rmdir(rerere_path(id, NULL));
		}
	}
	unlink_or_warn(git_path_merge_rr(r));
	rollback_lock_file(&write_lock);
}