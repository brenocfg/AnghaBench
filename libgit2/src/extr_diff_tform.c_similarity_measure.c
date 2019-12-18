#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  similarity_info ;
struct TYPE_14__ {TYPE_1__* metric; } ;
typedef  TYPE_2__ git_diff_find_options ;
struct TYPE_15__ {int size; int /*<<< orphan*/  id; int /*<<< orphan*/  flags; int /*<<< orphan*/  mode; int /*<<< orphan*/  path; } ;
typedef  TYPE_3__ git_diff_file ;
struct TYPE_16__ {scalar_t__ old_src; scalar_t__ new_src; } ;
typedef  TYPE_4__ git_diff ;
typedef  int /*<<< orphan*/  b_info ;
typedef  int /*<<< orphan*/  a_info ;
struct TYPE_13__ {int (* similarity ) (int*,void*,void*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  payload; } ;

/* Variables and functions */
 int FLAG_SET (TYPE_2__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GIT_DIFF_FIND_EXACT_MATCH_ONLY ; 
 int /*<<< orphan*/  GIT_DIFF_FLAG_VALID_ID ; 
 scalar_t__ GIT_ITERATOR_TYPE_WORKDIR ; 
 int /*<<< orphan*/  GIT_MODE_ISBLOB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_diff__oid_for_file (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ git_oid__cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ git_oid_is_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* similarity_get_file (TYPE_4__*,size_t) ; 
 int similarity_init (int /*<<< orphan*/ *,TYPE_4__*,size_t) ; 
 int similarity_sig (int /*<<< orphan*/ *,TYPE_2__ const*,void**) ; 
 int /*<<< orphan*/  similarity_unload (int /*<<< orphan*/ *) ; 
 int stub1 (int*,void*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int similarity_measure(
	int *score,
	git_diff *diff,
	const git_diff_find_options *opts,
	void **cache,
	size_t a_idx,
	size_t b_idx)
{
	git_diff_file *a_file = similarity_get_file(diff, a_idx);
	git_diff_file *b_file = similarity_get_file(diff, b_idx);
	bool exact_match = FLAG_SET(opts, GIT_DIFF_FIND_EXACT_MATCH_ONLY);
	int error = 0;
	similarity_info a_info, b_info;

	*score = -1;

	/* don't try to compare things that aren't files */
	if (!GIT_MODE_ISBLOB(a_file->mode) || !GIT_MODE_ISBLOB(b_file->mode))
		return 0;

	/* if exact match is requested, force calculation of missing OIDs now */
	if (exact_match) {
		if (git_oid_is_zero(&a_file->id) &&
			diff->old_src == GIT_ITERATOR_TYPE_WORKDIR &&
			!git_diff__oid_for_file(&a_file->id,
				diff, a_file->path, a_file->mode, a_file->size))
			a_file->flags |= GIT_DIFF_FLAG_VALID_ID;

		if (git_oid_is_zero(&b_file->id) &&
			diff->new_src == GIT_ITERATOR_TYPE_WORKDIR &&
			!git_diff__oid_for_file(&b_file->id,
				diff, b_file->path, b_file->mode, b_file->size))
			b_file->flags |= GIT_DIFF_FLAG_VALID_ID;
	}

	/* check OID match as a quick test */
	if (git_oid__cmp(&a_file->id, &b_file->id) == 0) {
		*score = 100;
		return 0;
	}

	/* don't calculate signatures if we are doing exact match */
	if (exact_match) {
		*score = 0;
		return 0;
	}

	memset(&a_info, 0, sizeof(a_info));
	memset(&b_info, 0, sizeof(b_info));

	/* set up similarity data (will try to update missing file sizes) */
	if (!cache[a_idx] && (error = similarity_init(&a_info, diff, a_idx)) < 0)
		return error;
	if (!cache[b_idx] && (error = similarity_init(&b_info, diff, b_idx)) < 0)
		goto cleanup;

	/* check if file sizes are nowhere near each other */
	if (a_file->size > 127 &&
		b_file->size > 127 &&
		(a_file->size > (b_file->size << 3) ||
		 b_file->size > (a_file->size << 3)))
		goto cleanup;

	/* update signature cache if needed */
	if (!cache[a_idx]) {
		if ((error = similarity_sig(&a_info, opts, cache)) < 0)
			goto cleanup;
	}
	if (!cache[b_idx]) {
		if ((error = similarity_sig(&b_info, opts, cache)) < 0)
			goto cleanup;
	}

	/* calculate similarity provided that the metric choose to process
	 * both the a and b files (some may not if file is too big, etc).
	 */
	if (cache[a_idx] && cache[b_idx])
		error = opts->metric->similarity(
			score, cache[a_idx], cache[b_idx], opts->metric->payload);

cleanup:
	similarity_unload(&a_info);
	similarity_unload(&b_info);

	return error;
}