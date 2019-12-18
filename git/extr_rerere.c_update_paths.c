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
struct string_list_item {int /*<<< orphan*/  string; } ;
struct string_list {int nr; struct string_list_item* items; } ;
struct repository {int /*<<< orphan*/  index; } ;
struct lock_file {int dummy; } ;

/* Variables and functions */
 int COMMIT_LOCK ; 
 int /*<<< orphan*/  LOCK_DIE_ON_ERROR ; 
 struct lock_file LOCK_INIT ; 
 int SKIP_IF_UNCHANGED ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ add_file_to_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf_ln (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repo_hold_locked_index (struct repository*,struct lock_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ write_locked_index (int /*<<< orphan*/ ,struct lock_file*,int) ; 

__attribute__((used)) static void update_paths(struct repository *r, struct string_list *update)
{
	struct lock_file index_lock = LOCK_INIT;
	int i;

	repo_hold_locked_index(r, &index_lock, LOCK_DIE_ON_ERROR);

	for (i = 0; i < update->nr; i++) {
		struct string_list_item *item = &update->items[i];
		if (add_file_to_index(r->index, item->string, 0))
			exit(128);
		fprintf_ln(stderr, _("Staged '%s' using previous resolution."),
			item->string);
	}

	if (write_locked_index(r->index, &index_lock,
			       COMMIT_LOCK | SKIP_IF_UNCHANGED))
		die(_("unable to write new index file"));
}