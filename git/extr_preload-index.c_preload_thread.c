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
struct thread_data {int offset; int nr; struct progress_data* progress; int /*<<< orphan*/  pathspec; struct index_state* index; } ;
struct stat {int dummy; } ;
struct progress_data {int n; int /*<<< orphan*/  mutex; int /*<<< orphan*/  progress; } ;
struct index_state {scalar_t__ cache_nr; struct cache_entry** cache; } ;
struct cache_entry {int ce_flags; int /*<<< orphan*/  name; int /*<<< orphan*/  ce_mode; } ;
struct cache_def {int dummy; } ;

/* Variables and functions */
 struct cache_def CACHE_DEF_INIT ; 
 int CE_FSMONITOR_VALID ; 
 int CE_MATCH_IGNORE_FSMONITOR ; 
 int CE_MATCH_RACY_IS_DIRTY ; 
 scalar_t__ S_ISGITLINK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cache_def_clear (struct cache_def*) ; 
 int /*<<< orphan*/  ce_mark_uptodate (struct cache_entry*) ; 
 int /*<<< orphan*/  ce_namelen (struct cache_entry*) ; 
 int /*<<< orphan*/  ce_path_match (struct index_state*,struct cache_entry*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ce_skip_worktree (struct cache_entry*) ; 
 scalar_t__ ce_stage (struct cache_entry*) ; 
 scalar_t__ ce_uptodate (struct cache_entry*) ; 
 int /*<<< orphan*/  display_progress (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ie_match_stat (struct index_state*,struct cache_entry*,struct stat*,int) ; 
 scalar_t__ lstat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  mark_fsmonitor_valid (struct index_state*,struct cache_entry*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ threaded_has_symlink_leading_path (struct cache_def*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *preload_thread(void *_data)
{
	int nr, last_nr;
	struct thread_data *p = _data;
	struct index_state *index = p->index;
	struct cache_entry **cep = index->cache + p->offset;
	struct cache_def cache = CACHE_DEF_INIT;

	nr = p->nr;
	if (nr + p->offset > index->cache_nr)
		nr = index->cache_nr - p->offset;
	last_nr = nr;

	do {
		struct cache_entry *ce = *cep++;
		struct stat st;

		if (ce_stage(ce))
			continue;
		if (S_ISGITLINK(ce->ce_mode))
			continue;
		if (ce_uptodate(ce))
			continue;
		if (ce_skip_worktree(ce))
			continue;
		if (ce->ce_flags & CE_FSMONITOR_VALID)
			continue;
		if (p->progress && !(nr & 31)) {
			struct progress_data *pd = p->progress;

			pthread_mutex_lock(&pd->mutex);
			pd->n += last_nr - nr;
			display_progress(pd->progress, pd->n);
			pthread_mutex_unlock(&pd->mutex);
			last_nr = nr;
		}
		if (!ce_path_match(index, ce, &p->pathspec, NULL))
			continue;
		if (threaded_has_symlink_leading_path(&cache, ce->name, ce_namelen(ce)))
			continue;
		if (lstat(ce->name, &st))
			continue;
		if (ie_match_stat(index, ce, &st, CE_MATCH_RACY_IS_DIRTY|CE_MATCH_IGNORE_FSMONITOR))
			continue;
		ce_mark_uptodate(ce);
		mark_fsmonitor_valid(index, ce);
	} while (--nr > 0);
	if (p->progress) {
		struct progress_data *pd = p->progress;

		pthread_mutex_lock(&pd->mutex);
		display_progress(pd->progress, pd->n + last_nr);
		pthread_mutex_unlock(&pd->mutex);
	}
	cache_def_clear(&cache);
	return NULL;
}