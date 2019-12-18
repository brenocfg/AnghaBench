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
struct worktree {int /*<<< orphan*/  path; } ;
struct strbuf {int /*<<< orphan*/  buf; } ;
struct index_state {int cache_nr; struct cache_entry** cache; int /*<<< orphan*/ * member_0; } ;
struct cache_entry {int /*<<< orphan*/  name; int /*<<< orphan*/  ce_mode; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  S_ISGITLINK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  discard_index (struct index_state*) ; 
 int /*<<< orphan*/  get_worktree_git_dir (struct worktree const*) ; 
 scalar_t__ is_directory (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_submodule_populated_gently (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ read_index_from (struct index_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 int /*<<< orphan*/  worktree_git_path (struct worktree const*,char*) ; 

__attribute__((used)) static void validate_no_submodules(const struct worktree *wt)
{
	struct index_state istate = { NULL };
	struct strbuf path = STRBUF_INIT;
	int i, found_submodules = 0;

	if (is_directory(worktree_git_path(wt, "modules"))) {
		/*
		 * There could be false positives, e.g. the "modules"
		 * directory exists but is empty. But it's a rare case and
		 * this simpler check is probably good enough for now.
		 */
		found_submodules = 1;
	} else if (read_index_from(&istate, worktree_git_path(wt, "index"),
				   get_worktree_git_dir(wt)) > 0) {
		for (i = 0; i < istate.cache_nr; i++) {
			struct cache_entry *ce = istate.cache[i];
			int err;

			if (!S_ISGITLINK(ce->ce_mode))
				continue;

			strbuf_reset(&path);
			strbuf_addf(&path, "%s/%s", wt->path, ce->name);
			if (!is_submodule_populated_gently(path.buf, &err))
				continue;

			found_submodules = 1;
			break;
		}
	}
	discard_index(&istate);
	strbuf_release(&path);

	if (found_submodules)
		die(_("working trees containing submodules cannot be moved or removed"));
}