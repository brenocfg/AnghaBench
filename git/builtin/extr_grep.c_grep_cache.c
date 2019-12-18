#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct strbuf {int /*<<< orphan*/  buf; int /*<<< orphan*/  len; } ;
struct repository {TYPE_1__* index; scalar_t__ submodule_prefix; } ;
struct pathspec {int dummy; } ;
struct grep_opt {scalar_t__ status_only; struct repository* repo; } ;
struct cache_entry {int ce_flags; scalar_t__ name; int /*<<< orphan*/  ce_mode; int /*<<< orphan*/  oid; } ;
struct TYPE_3__ {int cache_nr; struct cache_entry** cache; } ;

/* Variables and functions */
 int CE_VALID ; 
 struct strbuf STRBUF_INIT ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISGITLINK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ ce_intent_to_add (struct cache_entry const*) ; 
 scalar_t__ ce_skip_worktree (struct cache_entry const*) ; 
 scalar_t__ ce_stage (struct cache_entry const*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int grep_file (struct grep_opt*,int /*<<< orphan*/ ) ; 
 int grep_oid (struct grep_opt*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int grep_submodule (struct grep_opt*,struct pathspec const*,int /*<<< orphan*/ *,scalar_t__,scalar_t__,int) ; 
 scalar_t__ match_pathspec (TYPE_1__*,struct pathspec const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ recurse_submodules ; 
 scalar_t__ repo_read_index (struct repository*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,scalar_t__) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,int) ; 
 int /*<<< orphan*/  strcmp (scalar_t__,scalar_t__) ; 
 int strlen (scalar_t__) ; 
 scalar_t__ submodule_path_match (TYPE_1__*,struct pathspec const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int grep_cache(struct grep_opt *opt,
		      const struct pathspec *pathspec, int cached)
{
	struct repository *repo = opt->repo;
	int hit = 0;
	int nr;
	struct strbuf name = STRBUF_INIT;
	int name_base_len = 0;
	if (repo->submodule_prefix) {
		name_base_len = strlen(repo->submodule_prefix);
		strbuf_addstr(&name, repo->submodule_prefix);
	}

	if (repo_read_index(repo) < 0)
		die(_("index file corrupt"));

	for (nr = 0; nr < repo->index->cache_nr; nr++) {
		const struct cache_entry *ce = repo->index->cache[nr];
		strbuf_setlen(&name, name_base_len);
		strbuf_addstr(&name, ce->name);

		if (S_ISREG(ce->ce_mode) &&
		    match_pathspec(repo->index, pathspec, name.buf, name.len, 0, NULL,
				   S_ISDIR(ce->ce_mode) ||
				   S_ISGITLINK(ce->ce_mode))) {
			/*
			 * If CE_VALID is on, we assume worktree file and its
			 * cache entry are identical, even if worktree file has
			 * been modified, so use cache version instead
			 */
			if (cached || (ce->ce_flags & CE_VALID) ||
			    ce_skip_worktree(ce)) {
				if (ce_stage(ce) || ce_intent_to_add(ce))
					continue;
				hit |= grep_oid(opt, &ce->oid, name.buf,
						 0, name.buf);
			} else {
				hit |= grep_file(opt, name.buf);
			}
		} else if (recurse_submodules && S_ISGITLINK(ce->ce_mode) &&
			   submodule_path_match(repo->index, pathspec, name.buf, NULL)) {
			hit |= grep_submodule(opt, pathspec, NULL, ce->name,
					      ce->name, cached);
		} else {
			continue;
		}

		if (ce_stage(ce)) {
			do {
				nr++;
			} while (nr < repo->index->cache_nr &&
				 !strcmp(ce->name, repo->index->cache[nr]->name));
			nr--; /* compensate for loop control */
		}
		if (hit && opt->status_only)
			break;
	}

	strbuf_release(&name);
	return hit;
}