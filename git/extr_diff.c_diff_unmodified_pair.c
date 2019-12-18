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
struct diff_filespec {scalar_t__ oid_valid; int /*<<< orphan*/  dirty_submodule; int /*<<< orphan*/  oid; int /*<<< orphan*/  path; } ;
struct diff_filepair {struct diff_filespec* two; struct diff_filespec* one; } ;

/* Variables and functions */
 scalar_t__ DIFF_FILE_VALID (struct diff_filespec*) ; 
 scalar_t__ DIFF_PAIR_MODE_CHANGED (struct diff_filepair*) ; 
 scalar_t__ DIFF_PAIR_UNMERGED (struct diff_filepair*) ; 
 scalar_t__ oideq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int diff_unmodified_pair(struct diff_filepair *p)
{
	/* This function is written stricter than necessary to support
	 * the currently implemented transformers, but the idea is to
	 * let transformers to produce diff_filepairs any way they want,
	 * and filter and clean them up here before producing the output.
	 */
	struct diff_filespec *one = p->one, *two = p->two;

	if (DIFF_PAIR_UNMERGED(p))
		return 0; /* unmerged is interesting */

	/* deletion, addition, mode or type change
	 * and rename are all interesting.
	 */
	if (DIFF_FILE_VALID(one) != DIFF_FILE_VALID(two) ||
	    DIFF_PAIR_MODE_CHANGED(p) ||
	    strcmp(one->path, two->path))
		return 0;

	/* both are valid and point at the same path.  that is, we are
	 * dealing with a change.
	 */
	if (one->oid_valid && two->oid_valid &&
	    oideq(&one->oid, &two->oid) &&
	    !one->dirty_submodule && !two->dirty_submodule)
		return 1; /* no change */
	if (!one->oid_valid && !two->oid_valid)
		return 1; /* both look at the same file on the filesystem. */
	return 0;
}