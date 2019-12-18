#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct strbuf {int /*<<< orphan*/  buf; } ;
struct stat {int dummy; } ;
struct repository {TYPE_1__* index; } ;
struct dir_struct {int flags; } ;
struct cache_entry {int ce_flags; } ;
struct TYPE_6__ {int cache_nr; struct cache_entry** cache; } ;

/* Variables and functions */
 int CE_UPDATE ; 
 int DIR_COLLECT_KILLED_ONLY ; 
 int DIR_SHOW_IGNORED ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  ce_excluded (struct dir_struct*,TYPE_1__*,int /*<<< orphan*/ ,struct cache_entry const*) ; 
 scalar_t__ ce_skip_worktree (struct cache_entry const*) ; 
 scalar_t__ ce_stage (struct cache_entry const*) ; 
 int /*<<< orphan*/  construct_fullname (struct strbuf*,struct repository*,struct cache_entry const*) ; 
 int /*<<< orphan*/  fill_directory (struct dir_struct*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ ie_modified (TYPE_1__*,struct cache_entry const*,struct stat*,int /*<<< orphan*/ ) ; 
 int lstat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  pathspec ; 
 scalar_t__ show_cached ; 
 int /*<<< orphan*/  show_ce (struct repository*,struct dir_struct*,struct cache_entry const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ show_deleted ; 
 scalar_t__ show_killed ; 
 int /*<<< orphan*/  show_killed_files (TYPE_1__*,struct dir_struct*) ; 
 scalar_t__ show_modified ; 
 int /*<<< orphan*/  show_other_files (TYPE_1__*,struct dir_struct*) ; 
 scalar_t__ show_others ; 
 scalar_t__ show_stage ; 
 scalar_t__ show_unmerged ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  tag_cached ; 
 int /*<<< orphan*/  tag_modified ; 
 int /*<<< orphan*/  tag_removed ; 
 int /*<<< orphan*/  tag_skip_worktree ; 
 int /*<<< orphan*/  tag_unmerged ; 

__attribute__((used)) static void show_files(struct repository *repo, struct dir_struct *dir)
{
	int i;
	struct strbuf fullname = STRBUF_INIT;

	/* For cached/deleted files we don't need to even do the readdir */
	if (show_others || show_killed) {
		if (!show_others)
			dir->flags |= DIR_COLLECT_KILLED_ONLY;
		fill_directory(dir, repo->index, &pathspec);
		if (show_others)
			show_other_files(repo->index, dir);
		if (show_killed)
			show_killed_files(repo->index, dir);
	}
	if (show_cached || show_stage) {
		for (i = 0; i < repo->index->cache_nr; i++) {
			const struct cache_entry *ce = repo->index->cache[i];

			construct_fullname(&fullname, repo, ce);

			if ((dir->flags & DIR_SHOW_IGNORED) &&
			    !ce_excluded(dir, repo->index, fullname.buf, ce))
				continue;
			if (show_unmerged && !ce_stage(ce))
				continue;
			if (ce->ce_flags & CE_UPDATE)
				continue;
			show_ce(repo, dir, ce, fullname.buf,
				ce_stage(ce) ? tag_unmerged :
				(ce_skip_worktree(ce) ? tag_skip_worktree :
				 tag_cached));
		}
	}
	if (show_deleted || show_modified) {
		for (i = 0; i < repo->index->cache_nr; i++) {
			const struct cache_entry *ce = repo->index->cache[i];
			struct stat st;
			int err;

			construct_fullname(&fullname, repo, ce);

			if ((dir->flags & DIR_SHOW_IGNORED) &&
			    !ce_excluded(dir, repo->index, fullname.buf, ce))
				continue;
			if (ce->ce_flags & CE_UPDATE)
				continue;
			if (ce_skip_worktree(ce))
				continue;
			err = lstat(fullname.buf, &st);
			if (show_deleted && err)
				show_ce(repo, dir, ce, fullname.buf, tag_removed);
			if (show_modified && ie_modified(repo->index, ce, &st, 0))
				show_ce(repo, dir, ce, fullname.buf, tag_modified);
		}
	}

	strbuf_release(&fullname);
}