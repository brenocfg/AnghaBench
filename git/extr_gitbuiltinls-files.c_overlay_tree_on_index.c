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
struct tree {int dummy; } ;
struct pathspec {int dummy; } ;
struct object_id {int dummy; } ;
struct index_state {int cache_nr; struct cache_entry** cache; } ;
struct cache_entry {int /*<<< orphan*/  ce_flags; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  pathspec ;

/* Variables and functions */
 int /*<<< orphan*/  CE_STAGEMASK ; 
 int /*<<< orphan*/  CE_UPDATE ; 
 int /*<<< orphan*/  PATHSPEC_ALL_MAGIC ; 
 int /*<<< orphan*/  PATHSPEC_PREFER_CWD ; 
 int ce_stage (struct cache_entry*) ; 
 int /*<<< orphan*/  die (char*,char const*) ; 
 scalar_t__ get_oid (char const*,struct object_id*) ; 
 int /*<<< orphan*/  memset (struct pathspec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  parse_pathspec (struct pathspec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char const**) ; 
 struct tree* parse_tree_indirect (struct object_id*) ; 
 scalar_t__ read_tree (int /*<<< orphan*/ ,struct tree*,int,struct pathspec*,struct index_state*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  the_repository ; 

void overlay_tree_on_index(struct index_state *istate,
			   const char *tree_name, const char *prefix)
{
	struct tree *tree;
	struct object_id oid;
	struct pathspec pathspec;
	struct cache_entry *last_stage0 = NULL;
	int i;

	if (get_oid(tree_name, &oid))
		die("tree-ish %s not found.", tree_name);
	tree = parse_tree_indirect(&oid);
	if (!tree)
		die("bad tree-ish %s", tree_name);

	/* Hoist the unmerged entries up to stage #3 to make room */
	for (i = 0; i < istate->cache_nr; i++) {
		struct cache_entry *ce = istate->cache[i];
		if (!ce_stage(ce))
			continue;
		ce->ce_flags |= CE_STAGEMASK;
	}

	if (prefix) {
		static const char *(matchbuf[1]);
		matchbuf[0] = NULL;
		parse_pathspec(&pathspec, PATHSPEC_ALL_MAGIC,
			       PATHSPEC_PREFER_CWD, prefix, matchbuf);
	} else
		memset(&pathspec, 0, sizeof(pathspec));
	if (read_tree(the_repository, tree, 1, &pathspec, istate))
		die("unable to read tree entries %s", tree_name);

	for (i = 0; i < istate->cache_nr; i++) {
		struct cache_entry *ce = istate->cache[i];
		switch (ce_stage(ce)) {
		case 0:
			last_stage0 = ce;
			/* fallthru */
		default:
			continue;
		case 1:
			/*
			 * If there is stage #0 entry for this, we do not
			 * need to show it.  We use CE_UPDATE bit to mark
			 * such an entry.
			 */
			if (last_stage0 &&
			    !strcmp(last_stage0->name, ce->name))
				ce->ce_flags |= CE_UPDATE;
		}
	}
}