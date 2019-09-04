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
struct repository {int dummy; } ;
struct diff_filespec {unsigned long size; int /*<<< orphan*/  cnt_data; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_SIZE_ONLY ; 
 int MAX_SCORE ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ diff_populate_filespec (struct repository*,struct diff_filespec*,int /*<<< orphan*/ ) ; 
 scalar_t__ diffcore_count_changes (struct repository*,struct diff_filespec*,struct diff_filespec*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long*,unsigned long*) ; 

__attribute__((used)) static int estimate_similarity(struct repository *r,
			       struct diff_filespec *src,
			       struct diff_filespec *dst,
			       int minimum_score)
{
	/* src points at a file that existed in the original tree (or
	 * optionally a file in the destination tree) and dst points
	 * at a newly created file.  They may be quite similar, in which
	 * case we want to say src is renamed to dst or src is copied into
	 * dst, and then some edit has been applied to dst.
	 *
	 * Compare them and return how similar they are, representing
	 * the score as an integer between 0 and MAX_SCORE.
	 *
	 * When there is an exact match, it is considered a better
	 * match than anything else; the destination does not even
	 * call into this function in that case.
	 */
	unsigned long max_size, delta_size, base_size, src_copied, literal_added;
	int score;

	/* We deal only with regular files.  Symlink renames are handled
	 * only when they are exact matches --- in other words, no edits
	 * after renaming.
	 */
	if (!S_ISREG(src->mode) || !S_ISREG(dst->mode))
		return 0;

	/*
	 * Need to check that source and destination sizes are
	 * filled in before comparing them.
	 *
	 * If we already have "cnt_data" filled in, we know it's
	 * all good (avoid checking the size for zero, as that
	 * is a possible size - we really should have a flag to
	 * say whether the size is valid or not!)
	 */
	if (!src->cnt_data &&
	    diff_populate_filespec(r, src, CHECK_SIZE_ONLY))
		return 0;
	if (!dst->cnt_data &&
	    diff_populate_filespec(r, dst, CHECK_SIZE_ONLY))
		return 0;

	max_size = ((src->size > dst->size) ? src->size : dst->size);
	base_size = ((src->size < dst->size) ? src->size : dst->size);
	delta_size = max_size - base_size;

	/* We would not consider edits that change the file size so
	 * drastically.  delta_size must be smaller than
	 * (MAX_SCORE-minimum_score)/MAX_SCORE * min(src->size, dst->size).
	 *
	 * Note that base_size == 0 case is handled here already
	 * and the final score computation below would not have a
	 * divide-by-zero issue.
	 */
	if (max_size * (MAX_SCORE-minimum_score) < delta_size * MAX_SCORE)
		return 0;

	if (!src->cnt_data && diff_populate_filespec(r, src, 0))
		return 0;
	if (!dst->cnt_data && diff_populate_filespec(r, dst, 0))
		return 0;

	if (diffcore_count_changes(r, src, dst,
				   &src->cnt_data, &dst->cnt_data,
				   &src_copied, &literal_added))
		return 0;

	/* How similar are they?
	 * what percentage of material in dst are from source?
	 */
	if (!dst->size)
		score = 0; /* should not happen */
	else
		score = (int)(src_copied * MAX_SCORE / max_size);
	return score;
}