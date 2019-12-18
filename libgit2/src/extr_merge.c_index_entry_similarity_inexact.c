#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_10__ {TYPE_1__* metric; } ;
typedef  TYPE_2__ git_merge_options ;
struct TYPE_11__ {int /*<<< orphan*/  mode; } ;
typedef  TYPE_3__ git_index_entry ;
struct TYPE_9__ {scalar_t__ (* similarity ) (int*,void*,void*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  payload; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_MODE_ISBLOB (int /*<<< orphan*/ ) ; 
 int index_entry_similarity_calc (void**,int /*<<< orphan*/ *,TYPE_3__*,TYPE_2__ const*) ; 
 scalar_t__ stub1 (int*,void*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int index_entry_similarity_inexact(
	git_repository *repo,
	git_index_entry *a,
	size_t a_idx,
	git_index_entry *b,
	size_t b_idx,
	void **cache,
	const git_merge_options *opts)
{
	int score = 0;
	int error = 0;

	if (!GIT_MODE_ISBLOB(a->mode) || !GIT_MODE_ISBLOB(b->mode))
		return 0;

	/* update signature cache if needed */
	if (!cache[a_idx] && (error = index_entry_similarity_calc(&cache[a_idx], repo, a, opts)) < 0)
		return error;
	if (!cache[b_idx] && (error = index_entry_similarity_calc(&cache[b_idx], repo, b, opts)) < 0)
		return error;

	/* some metrics may not wish to process this file (too big / too small) */
	if (!cache[a_idx] || !cache[b_idx])
		return 0;

	/* compare signatures */
	if (opts->metric->similarity(
		&score, cache[a_idx], cache[b_idx], opts->metric->payload) < 0)
		return -1;

	/* clip score */
	if (score < 0)
		score = 0;
	else if (score > 100)
		score = 100;

	return score;
}