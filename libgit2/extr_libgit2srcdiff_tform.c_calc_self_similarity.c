#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  git_diff_find_options ;
struct TYPE_6__ {int flags; scalar_t__ similarity; } ;
typedef  TYPE_1__ git_diff_delta ;
struct TYPE_7__ {int /*<<< orphan*/  deltas; } ;
typedef  TYPE_2__ git_diff ;

/* Variables and functions */
 int GIT_DIFF_FLAG__HAS_SELF_SIMILARITY ; 
 TYPE_1__* GIT_VECTOR_GET (int /*<<< orphan*/ *,size_t) ; 
 int similarity_measure (int*,TYPE_2__*,int /*<<< orphan*/  const*,void**,int,int) ; 

__attribute__((used)) static int calc_self_similarity(
	git_diff *diff,
	const git_diff_find_options *opts,
	size_t delta_idx,
	void **cache)
{
	int error, similarity = -1;
	git_diff_delta *delta = GIT_VECTOR_GET(&diff->deltas, delta_idx);

	if ((delta->flags & GIT_DIFF_FLAG__HAS_SELF_SIMILARITY) != 0)
		return 0;

	error = similarity_measure(
		&similarity, diff, opts, cache, 2 * delta_idx, 2 * delta_idx + 1);
	if (error < 0)
		return error;

	if (similarity >= 0) {
		delta->similarity = (uint16_t)similarity;
		delta->flags |= GIT_DIFF_FLAG__HAS_SELF_SIMILARITY;
	}

	return 0;
}