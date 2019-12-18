#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_37__   TYPE_7__ ;
typedef  struct TYPE_36__   TYPE_6__ ;
typedef  struct TYPE_35__   TYPE_5__ ;
typedef  struct TYPE_34__   TYPE_4__ ;
typedef  struct TYPE_33__   TYPE_3__ ;
typedef  struct TYPE_32__   TYPE_2__ ;
typedef  struct TYPE_31__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_32__ {scalar_t__ stat_calls; } ;
typedef  TYPE_2__ git_iterator ;
struct TYPE_33__ {int (* progress_cb ) (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  payload; } ;
typedef  TYPE_3__ git_diff_options ;
struct TYPE_31__ {int /*<<< orphan*/  stat_calls; } ;
struct TYPE_35__ {int (* entrycomp ) (TYPE_7__*,TYPE_7__*) ;TYPE_1__ perf; } ;
struct TYPE_34__ {TYPE_5__ base; } ;
typedef  TYPE_4__ git_diff_generated ;
typedef  TYPE_5__ git_diff ;
struct TYPE_36__ {TYPE_7__* nitem; TYPE_7__* oitem; TYPE_2__* new_iter; TYPE_2__* old_iter; int /*<<< orphan*/ * repo; } ;
typedef  TYPE_6__ diff_in_progress ;
struct TYPE_37__ {int /*<<< orphan*/ * path; } ;

/* Variables and functions */
 scalar_t__ DIFF_FLAG_IS_SET (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GIT_DIFF_IGNORE_CASE ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_4__*) ; 
 TYPE_4__* diff_generated_alloc (int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*) ; 
 int diff_generated_apply_options (TYPE_4__*,TYPE_3__ const*) ; 
 int /*<<< orphan*/  git_diff_free (TYPE_5__*) ; 
 int /*<<< orphan*/  git_iterator_set_ignore_case (TYPE_2__*,int) ; 
 int handle_matched_item (TYPE_4__*,TYPE_6__*) ; 
 int handle_unmatched_new_item (TYPE_4__*,TYPE_6__*) ; 
 int handle_unmatched_old_item (TYPE_4__*,TYPE_6__*) ; 
 int iterator_current (TYPE_7__**,TYPE_2__*) ; 
 int stub1 (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int stub2 (TYPE_7__*,TYPE_7__*) ; 

int git_diff__from_iterators(
	git_diff **out,
	git_repository *repo,
	git_iterator *old_iter,
	git_iterator *new_iter,
	const git_diff_options *opts)
{
	git_diff_generated *diff;
	diff_in_progress info;
	int error = 0;

	*out = NULL;

	diff = diff_generated_alloc(repo, old_iter, new_iter);
	GIT_ERROR_CHECK_ALLOC(diff);

	info.repo = repo;
	info.old_iter = old_iter;
	info.new_iter = new_iter;

	/* make iterators have matching icase behavior */
	if (DIFF_FLAG_IS_SET(diff, GIT_DIFF_IGNORE_CASE)) {
		git_iterator_set_ignore_case(old_iter, true);
		git_iterator_set_ignore_case(new_iter, true);
	}

	/* finish initialization */
	if ((error = diff_generated_apply_options(diff, opts)) < 0)
		goto cleanup;

	if ((error = iterator_current(&info.oitem, old_iter)) < 0 ||
		(error = iterator_current(&info.nitem, new_iter)) < 0)
		goto cleanup;

	/* run iterators building diffs */
	while (!error && (info.oitem || info.nitem)) {
		int cmp;

		/* report progress */
		if (opts && opts->progress_cb) {
			if ((error = opts->progress_cb(&diff->base,
					info.oitem ? info.oitem->path : NULL,
					info.nitem ? info.nitem->path : NULL,
					opts->payload)))
				break;
		}

		cmp = info.oitem ?
			(info.nitem ? diff->base.entrycomp(info.oitem, info.nitem) : -1) : 1;

		/* create DELETED records for old items not matched in new */
		if (cmp < 0)
			error = handle_unmatched_old_item(diff, &info);

		/* create ADDED, TRACKED, or IGNORED records for new items not
		 * matched in old (and/or descend into directories as needed)
		 */
		else if (cmp > 0)
			error = handle_unmatched_new_item(diff, &info);

		/* otherwise item paths match, so create MODIFIED record
		 * (or ADDED and DELETED pair if type changed)
		 */
		else
			error = handle_matched_item(diff, &info);
	}

	diff->base.perf.stat_calls +=
		old_iter->stat_calls + new_iter->stat_calls;

cleanup:
	if (!error)
		*out = &diff->base;
	else
		git_diff_free(&diff->base);

	return error;
}