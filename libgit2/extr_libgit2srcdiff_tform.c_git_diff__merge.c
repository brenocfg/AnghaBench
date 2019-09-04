#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_vector ;
typedef  int /*<<< orphan*/  git_pool ;
struct TYPE_21__ {int /*<<< orphan*/  path; } ;
struct TYPE_22__ {TYPE_1__ old_file; } ;
typedef  TYPE_2__ const git_diff_delta ;
typedef  TYPE_2__ const* (* git_diff__merge_cb ) (TYPE_2__ const*,TYPE_2__ const*,int /*<<< orphan*/ *) ;
struct TYPE_25__ {int flags; void* new_prefix; void* old_prefix; } ;
struct TYPE_24__ {unsigned int length; } ;
struct TYPE_23__ {TYPE_9__ opts; int /*<<< orphan*/  pool; int /*<<< orphan*/  new_src; int /*<<< orphan*/  old_src; TYPE_7__ deltas; } ;
typedef  TYPE_6__ git_diff ;

/* Variables and functions */
 int GIT_DIFF_IGNORE_CASE ; 
 int GIT_DIFF_REVERSE ; 
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 TYPE_2__ const* GIT_VECTOR_GET (TYPE_7__*,unsigned int) ; 
 int STRCMP_CASESELECT (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  git__free (TYPE_2__ const*) ; 
 TYPE_2__ const* git_diff__delta_dup (TYPE_2__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_delta__cmp ; 
 scalar_t__ git_diff_delta__should_skip (TYPE_9__*,TYPE_2__ const*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_pool_init (int /*<<< orphan*/ *,int) ; 
 void* git_pool_strdup_safe (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  git_pool_swap (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_vector_free_deep (int /*<<< orphan*/ *) ; 
 scalar_t__ git_vector_init (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int git_vector_insert (int /*<<< orphan*/ *,TYPE_2__ const*) ; 
 int /*<<< orphan*/  git_vector_swap (TYPE_7__*,int /*<<< orphan*/ *) ; 

int git_diff__merge(
	git_diff *onto, const git_diff *from, git_diff__merge_cb cb)
{
	int error = 0;
	git_pool onto_pool;
	git_vector onto_new;
	git_diff_delta *delta;
	bool ignore_case, reversed;
	unsigned int i, j;

	assert(onto && from);

	if (!from->deltas.length)
		return 0;

	ignore_case = ((onto->opts.flags & GIT_DIFF_IGNORE_CASE) != 0);
	reversed    = ((onto->opts.flags & GIT_DIFF_REVERSE) != 0);

	if (ignore_case != ((from->opts.flags & GIT_DIFF_IGNORE_CASE) != 0) ||
		reversed    != ((from->opts.flags & GIT_DIFF_REVERSE) != 0)) {
		git_error_set(GIT_ERROR_INVALID,
			"attempt to merge diffs created with conflicting options");
		return -1;
	}

	if (git_vector_init(&onto_new, onto->deltas.length, git_diff_delta__cmp) < 0)
		return -1;

	git_pool_init(&onto_pool, 1);

	for (i = 0, j = 0; i < onto->deltas.length || j < from->deltas.length; ) {
		git_diff_delta *o = GIT_VECTOR_GET(&onto->deltas, i);
		const git_diff_delta *f = GIT_VECTOR_GET(&from->deltas, j);
		int cmp = !f ? -1 : !o ? 1 :
			STRCMP_CASESELECT(ignore_case, o->old_file.path, f->old_file.path);

		if (cmp < 0) {
			delta = git_diff__delta_dup(o, &onto_pool);
			i++;
		} else if (cmp > 0) {
			delta = git_diff__delta_dup(f, &onto_pool);
			j++;
		} else {
			const git_diff_delta *left = reversed ? f : o;
			const git_diff_delta *right = reversed ? o : f;

			delta = cb(left, right, &onto_pool);
			i++;
			j++;
		}

		/* the ignore rules for the target may not match the source
		 * or the result of a merged delta could be skippable...
		 */
		if (delta && git_diff_delta__should_skip(&onto->opts, delta)) {
			git__free(delta);
			continue;
		}

		if ((error = !delta ? -1 : git_vector_insert(&onto_new, delta)) < 0)
			break;
	}

	if (!error) {
		git_vector_swap(&onto->deltas, &onto_new);
		git_pool_swap(&onto->pool, &onto_pool);

		if ((onto->opts.flags & GIT_DIFF_REVERSE) != 0)
			onto->old_src = from->old_src;
		else
			onto->new_src = from->new_src;

		/* prefix strings also come from old pool, so recreate those.*/
		onto->opts.old_prefix =
			git_pool_strdup_safe(&onto->pool, onto->opts.old_prefix);
		onto->opts.new_prefix =
			git_pool_strdup_safe(&onto->pool, onto->opts.new_prefix);
	}

	git_vector_free_deep(&onto_new);
	git_pool_clear(&onto_pool);

	return error;
}