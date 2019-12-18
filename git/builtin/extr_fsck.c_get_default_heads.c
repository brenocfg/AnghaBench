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
struct worktree {int dummy; } ;
struct strbuf {int /*<<< orphan*/  buf; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  default_refs ; 
 int /*<<< orphan*/  for_each_rawref (int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,struct object_id*,int /*<<< orphan*/ ,int /*<<< orphan*/ *),int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf_ln (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_worktrees (struct worktree**) ; 
 int /*<<< orphan*/  fsck_handle_ref (int /*<<< orphan*/ ,struct object_id*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsck_handle_reflog ; 
 int /*<<< orphan*/  fsck_head_link (int /*<<< orphan*/ ,char const**,struct object_id*) ; 
 int /*<<< orphan*/  get_worktree_ref_store (struct worktree*) ; 
 struct worktree** get_worktrees (int /*<<< orphan*/ ) ; 
 scalar_t__ include_reflogs ; 
 int /*<<< orphan*/  is_null_oid (struct object_id*) ; 
 int /*<<< orphan*/  refs_for_each_reflog (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct worktree*) ; 
 scalar_t__ show_unreachable ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_worktree_ref (struct worktree*,struct strbuf*,char*) ; 

__attribute__((used)) static void get_default_heads(void)
{
	struct worktree **worktrees, **p;
	const char *head_points_at;
	struct object_id head_oid;

	for_each_rawref(fsck_handle_ref, NULL);

	worktrees = get_worktrees(0);
	for (p = worktrees; *p; p++) {
		struct worktree *wt = *p;
		struct strbuf ref = STRBUF_INIT;

		strbuf_worktree_ref(wt, &ref, "HEAD");
		fsck_head_link(ref.buf, &head_points_at, &head_oid);
		if (head_points_at && !is_null_oid(&head_oid))
			fsck_handle_ref(ref.buf, &head_oid, 0, NULL);
		strbuf_release(&ref);

		if (include_reflogs)
			refs_for_each_reflog(get_worktree_ref_store(wt),
					     fsck_handle_reflog, wt);
	}
	free_worktrees(worktrees);

	/*
	 * Not having any default heads isn't really fatal, but
	 * it does mean that "--unreachable" no longer makes any
	 * sense (since in this case everything will obviously
	 * be unreachable by definition.
	 *
	 * Showing dangling objects is valid, though (as those
	 * dangling objects are likely lost heads).
	 *
	 * So we just print a warning about it, and clear the
	 * "show_unreachable" flag.
	 */
	if (!default_refs) {
		fprintf_ln(stderr, _("notice: No default references"));
		show_unreachable = 0;
	}
}