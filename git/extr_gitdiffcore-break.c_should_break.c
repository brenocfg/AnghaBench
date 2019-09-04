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
struct diff_filespec {unsigned long size; int /*<<< orphan*/  cnt_data; int /*<<< orphan*/  oid; scalar_t__ oid_valid; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 unsigned long MAX_SCORE ; 
 unsigned long MINIMUM_BREAK_SIZE ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ diff_populate_filespec (struct repository*,struct diff_filespec*,int /*<<< orphan*/ ) ; 
 scalar_t__ diffcore_count_changes (struct repository*,struct diff_filespec*,struct diff_filespec*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long*,unsigned long*) ; 
 scalar_t__ oideq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int should_break(struct repository *r,
			struct diff_filespec *src,
			struct diff_filespec *dst,
			int break_score,
			int *merge_score_p)
{
	/* dst is recorded as a modification of src.  Are they so
	 * different that we are better off recording this as a pair
	 * of delete and create?
	 *
	 * There are two criteria used in this algorithm.  For the
	 * purposes of helping later rename/copy, we take both delete
	 * and insert into account and estimate the amount of "edit".
	 * If the edit is very large, we break this pair so that
	 * rename/copy can pick the pieces up to match with other
	 * files.
	 *
	 * On the other hand, we would want to ignore inserts for the
	 * pure "complete rewrite" detection.  As long as most of the
	 * existing contents were removed from the file, it is a
	 * complete rewrite, and if sizable chunk from the original
	 * still remains in the result, it is not a rewrite.  It does
	 * not matter how much or how little new material is added to
	 * the file.
	 *
	 * The score we leave for such a broken filepair uses the
	 * latter definition so that later clean-up stage can find the
	 * pieces that should not have been broken according to the
	 * latter definition after rename/copy runs, and merge the
	 * broken pair that have a score lower than given criteria
	 * back together.  The break operation itself happens
	 * according to the former definition.
	 *
	 * The minimum_edit parameter tells us when to break (the
	 * amount of "edit" required for us to consider breaking the
	 * pair).  We leave the amount of deletion in *merge_score_p
	 * when we return.
	 *
	 * The value we return is 1 if we want the pair to be broken,
	 * or 0 if we do not.
	 */
	unsigned long delta_size, max_size;
	unsigned long src_copied, literal_added, src_removed;

	*merge_score_p = 0; /* assume no deletion --- "do not break"
			     * is the default.
			     */

	if (S_ISREG(src->mode) != S_ISREG(dst->mode)) {
		*merge_score_p = (int)MAX_SCORE;
		return 1; /* even their types are different */
	}

	if (src->oid_valid && dst->oid_valid &&
	    oideq(&src->oid, &dst->oid))
		return 0; /* they are the same */

	if (diff_populate_filespec(r, src, 0) ||
	    diff_populate_filespec(r, dst, 0))
		return 0; /* error but caught downstream */

	max_size = ((src->size > dst->size) ? src->size : dst->size);
	if (max_size < MINIMUM_BREAK_SIZE)
		return 0; /* we do not break too small filepair */

	if (!src->size)
		return 0; /* we do not let empty files get renamed */

	if (diffcore_count_changes(r, src, dst,
				   &src->cnt_data, &dst->cnt_data,
				   &src_copied, &literal_added))
		return 0;

	/* sanity */
	if (src->size < src_copied)
		src_copied = src->size;
	if (dst->size < literal_added + src_copied) {
		if (src_copied < dst->size)
			literal_added = dst->size - src_copied;
		else
			literal_added = 0;
	}
	src_removed = src->size - src_copied;

	/* Compute merge-score, which is "how much is removed
	 * from the source material".  The clean-up stage will
	 * merge the surviving pair together if the score is
	 * less than the minimum, after rename/copy runs.
	 */
	*merge_score_p = (int)(src_removed * MAX_SCORE / src->size);
	if (*merge_score_p > break_score)
		return 1;

	/* Extent of damage, which counts both inserts and
	 * deletes.
	 */
	delta_size = src_removed + literal_added;
	if (delta_size * MAX_SCORE / max_size < break_score)
		return 0;

	/* If you removed a lot without adding new material, that is
	 * not really a rewrite.
	 */
	if ((src->size * break_score < src_removed * MAX_SCORE) &&
	    (literal_added * 20 < src_removed) &&
	    (literal_added * 20 < src_copied))
		return 0;

	return 1;
}