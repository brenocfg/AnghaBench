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
struct pathspec {int dummy; } ;
struct cache_entry {scalar_t__ ce_mode; int /*<<< orphan*/  name; int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 int /*<<< orphan*/  PATHSPEC_PREFER_CWD ; 
 struct cache_entry** active_cache ; 
 int active_nr ; 
 int /*<<< orphan*/  ce_namelen (struct cache_entry const*) ; 
 int /*<<< orphan*/  ce_path_match (int /*<<< orphan*/ *,struct cache_entry const*,struct pathspec*,int /*<<< orphan*/ *) ; 
 scalar_t__ ce_stage (struct cache_entry const*) ; 
 int /*<<< orphan*/  clear_pathspec (struct pathspec*) ; 
 int /*<<< orphan*/  discard_cache_entry (struct cache_entry*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  head_oid ; 
 scalar_t__ oideq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_pathspec (struct pathspec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char const**) ; 
 struct cache_entry* read_one_ent (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ read_ref (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  the_index ; 
 int /*<<< orphan*/  update_one (char*) ; 
 char* xstrdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_reupdate(int ac, const char **av,
		       const char *prefix)
{
	/* Read HEAD and run update-index on paths that are
	 * merged and already different between index and HEAD.
	 */
	int pos;
	int has_head = 1;
	struct pathspec pathspec;

	parse_pathspec(&pathspec, 0,
		       PATHSPEC_PREFER_CWD,
		       prefix, av + 1);

	if (read_ref("HEAD", &head_oid))
		/* If there is no HEAD, that means it is an initial
		 * commit.  Update everything in the index.
		 */
		has_head = 0;
 redo:
	for (pos = 0; pos < active_nr; pos++) {
		const struct cache_entry *ce = active_cache[pos];
		struct cache_entry *old = NULL;
		int save_nr;
		char *path;

		if (ce_stage(ce) || !ce_path_match(&the_index, ce, &pathspec, NULL))
			continue;
		if (has_head)
			old = read_one_ent(NULL, &head_oid,
					   ce->name, ce_namelen(ce), 0);
		if (old && ce->ce_mode == old->ce_mode &&
		    oideq(&ce->oid, &old->oid)) {
			discard_cache_entry(old);
			continue; /* unchanged */
		}
		/* Be careful.  The working tree may not have the
		 * path anymore, in which case, under 'allow_remove',
		 * or worse yet 'allow_replace', active_nr may decrease.
		 */
		save_nr = active_nr;
		path = xstrdup(ce->name);
		update_one(path);
		free(path);
		discard_cache_entry(old);
		if (save_nr != active_nr)
			goto redo;
	}
	clear_pathspec(&pathspec);
	return 0;
}