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
struct lock_file {int dummy; } ;
struct commit_list {struct commit* item; } ;
struct commit {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int COMMIT_LOCK ; 
 int /*<<< orphan*/  LOCK_DIE_ON_ERROR ; 
 struct lock_file LOCK_INIT ; 
 int /*<<< orphan*/  REFRESH_QUIET ; 
 int SKIP_IF_UNCHANGED ; 
 char* _ (char*) ; 
 struct commit_list** commit_list_append (struct commit*,struct commit_list**) ; 
 scalar_t__ commit_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct object_id*,struct commit_list*,struct object_id*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  drop_save () ; 
 int error (char*) ; 
 int /*<<< orphan*/  finish (struct commit*,struct commit_list*,struct object_id*,char*) ; 
 int /*<<< orphan*/  hold_locked_index (struct lock_file*,int /*<<< orphan*/ ) ; 
 TYPE_1__ merge_msg ; 
 int /*<<< orphan*/  prepare_to_commit (struct commit_list*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  refresh_cache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sign_commit ; 
 int /*<<< orphan*/  the_index ; 
 scalar_t__ write_locked_index (int /*<<< orphan*/ *,struct lock_file*,int) ; 
 int /*<<< orphan*/  write_tree_trivial (struct object_id*) ; 

__attribute__((used)) static int merge_trivial(struct commit *head, struct commit_list *remoteheads)
{
	struct object_id result_tree, result_commit;
	struct commit_list *parents, **pptr = &parents;
	struct lock_file lock = LOCK_INIT;

	hold_locked_index(&lock, LOCK_DIE_ON_ERROR);
	refresh_cache(REFRESH_QUIET);
	if (write_locked_index(&the_index, &lock,
			       COMMIT_LOCK | SKIP_IF_UNCHANGED))
		return error(_("Unable to write index."));

	write_tree_trivial(&result_tree);
	printf(_("Wonderful.\n"));
	pptr = commit_list_append(head, pptr);
	pptr = commit_list_append(remoteheads->item, pptr);
	prepare_to_commit(remoteheads);
	if (commit_tree(merge_msg.buf, merge_msg.len, &result_tree, parents,
			&result_commit, NULL, sign_commit))
		die(_("failed to write commit object"));
	finish(head, remoteheads, &result_commit, "In-index merge");
	drop_save();
	return 0;
}