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
struct notes_merge_options {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REF_NO_DEREF ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ delete_ref (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ error (int /*<<< orphan*/ ) ; 
 scalar_t__ notes_merge_abort (struct notes_merge_options*) ; 

__attribute__((used)) static int merge_abort(struct notes_merge_options *o)
{
	int ret = 0;

	/*
	 * Remove .git/NOTES_MERGE_PARTIAL and .git/NOTES_MERGE_REF, and call
	 * notes_merge_abort() to remove .git/NOTES_MERGE_WORKTREE.
	 */

	if (delete_ref(NULL, "NOTES_MERGE_PARTIAL", NULL, 0))
		ret += error(_("failed to delete ref NOTES_MERGE_PARTIAL"));
	if (delete_ref(NULL, "NOTES_MERGE_REF", NULL, REF_NO_DEREF))
		ret += error(_("failed to delete ref NOTES_MERGE_REF"));
	if (notes_merge_abort(o))
		ret += error(_("failed to remove 'git notes merge' worktree"));
	return ret;
}