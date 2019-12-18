#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct submodule {int /*<<< orphan*/  name; int /*<<< orphan*/  path; } ;
struct strbuf {int /*<<< orphan*/  buf; } ;
struct repository {TYPE_1__* index; int /*<<< orphan*/  gitdir; } ;
struct cache_entry {int /*<<< orphan*/  name; int /*<<< orphan*/  ce_mode; } ;
struct TYPE_2__ {int cache_nr; struct cache_entry** cache; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  S_ISGITLINK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  connect_work_tree_and_git_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_submodule_active (struct repository*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  null_oid ; 
 int /*<<< orphan*/  repo_clear (struct repository*) ; 
 scalar_t__ repo_init (struct repository*,char const*,char const*) ; 
 scalar_t__ repo_read_index (struct repository*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct submodule* submodule_from_path (struct repository*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void connect_wt_gitdir_in_nested(const char *sub_worktree,
					const char *sub_gitdir)
{
	int i;
	struct repository subrepo;
	struct strbuf sub_wt = STRBUF_INIT;
	struct strbuf sub_gd = STRBUF_INIT;

	const struct submodule *sub;

	/* If the submodule has no working tree, we can ignore it. */
	if (repo_init(&subrepo, sub_gitdir, sub_worktree))
		return;

	if (repo_read_index(&subrepo) < 0)
		die(_("index file corrupt in repo %s"), subrepo.gitdir);

	for (i = 0; i < subrepo.index->cache_nr; i++) {
		const struct cache_entry *ce = subrepo.index->cache[i];

		if (!S_ISGITLINK(ce->ce_mode))
			continue;

		while (i + 1 < subrepo.index->cache_nr &&
		       !strcmp(ce->name, subrepo.index->cache[i + 1]->name))
			/*
			 * Skip entries with the same name in different stages
			 * to make sure an entry is returned only once.
			 */
			i++;

		sub = submodule_from_path(&subrepo, &null_oid, ce->name);
		if (!sub || !is_submodule_active(&subrepo, ce->name))
			/* .gitmodules broken or inactive sub */
			continue;

		strbuf_reset(&sub_wt);
		strbuf_reset(&sub_gd);
		strbuf_addf(&sub_wt, "%s/%s", sub_worktree, sub->path);
		strbuf_addf(&sub_gd, "%s/modules/%s", sub_gitdir, sub->name);

		connect_work_tree_and_git_dir(sub_wt.buf, sub_gd.buf, 1);
	}
	strbuf_release(&sub_wt);
	strbuf_release(&sub_gd);
	repo_clear(&subrepo);
}