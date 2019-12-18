#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rev_info {int limited; int /*<<< orphan*/  prune_data; TYPE_1__* repo; } ;
struct object_id {int dummy; } ;
struct index_state {int cache_nr; struct cache_entry** cache; } ;
struct commit_list {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct commit {TYPE_2__ object; } ;
struct cache_entry {char* name; } ;
struct TYPE_3__ {struct index_state* index; } ;

/* Variables and functions */
 int BOTTOM ; 
 int PATHSPEC_ALL_MAGIC ; 
 int PATHSPEC_LITERAL ; 
 int PATHSPEC_LITERAL_PATH ; 
 int PATHSPEC_PREFER_FULL ; 
 int /*<<< orphan*/  REALLOC_ARRAY (char const**,int) ; 
 int /*<<< orphan*/  REV_CMD_MERGE_BASE ; 
 int /*<<< orphan*/  SYMMETRIC_LEFT ; 
 int UNINTERESTING ; 
 int /*<<< orphan*/  add_pending_commit_list (struct rev_info*,struct commit_list*,int) ; 
 int /*<<< orphan*/  add_pending_object (struct rev_info*,TYPE_2__*,char*) ; 
 int /*<<< orphan*/  add_rev_cmdline_list (struct rev_info*,struct commit_list*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ce_path_match (struct index_state*,struct cache_entry const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ce_same_name (struct cache_entry const*,struct cache_entry*) ; 
 int /*<<< orphan*/  ce_stage (struct cache_entry const*) ; 
 int /*<<< orphan*/  clear_pathspec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  free_commit_list (struct commit_list*) ; 
 struct commit_list* get_merge_bases (struct commit*,struct commit*) ; 
 scalar_t__ get_oid (char*,struct object_id*) ; 
 struct commit* lookup_commit_or_die (struct object_id*,char*) ; 
 int /*<<< orphan*/  parse_pathspec (int /*<<< orphan*/ *,int,int,char*,char const**) ; 
 int /*<<< orphan*/  repo_read_index (TYPE_1__*) ; 

__attribute__((used)) static void prepare_show_merge(struct rev_info *revs)
{
	struct commit_list *bases;
	struct commit *head, *other;
	struct object_id oid;
	const char **prune = NULL;
	int i, prune_num = 1; /* counting terminating NULL */
	struct index_state *istate = revs->repo->index;

	if (get_oid("HEAD", &oid))
		die("--merge without HEAD?");
	head = lookup_commit_or_die(&oid, "HEAD");
	if (get_oid("MERGE_HEAD", &oid))
		die("--merge without MERGE_HEAD?");
	other = lookup_commit_or_die(&oid, "MERGE_HEAD");
	add_pending_object(revs, &head->object, "HEAD");
	add_pending_object(revs, &other->object, "MERGE_HEAD");
	bases = get_merge_bases(head, other);
	add_rev_cmdline_list(revs, bases, REV_CMD_MERGE_BASE, UNINTERESTING | BOTTOM);
	add_pending_commit_list(revs, bases, UNINTERESTING | BOTTOM);
	free_commit_list(bases);
	head->object.flags |= SYMMETRIC_LEFT;

	if (!istate->cache_nr)
		repo_read_index(revs->repo);
	for (i = 0; i < istate->cache_nr; i++) {
		const struct cache_entry *ce = istate->cache[i];
		if (!ce_stage(ce))
			continue;
		if (ce_path_match(istate, ce, &revs->prune_data, NULL)) {
			prune_num++;
			REALLOC_ARRAY(prune, prune_num);
			prune[prune_num-2] = ce->name;
			prune[prune_num-1] = NULL;
		}
		while ((i+1 < istate->cache_nr) &&
		       ce_same_name(ce, istate->cache[i+1]))
			i++;
	}
	clear_pathspec(&revs->prune_data);
	parse_pathspec(&revs->prune_data, PATHSPEC_ALL_MAGIC & ~PATHSPEC_LITERAL,
		       PATHSPEC_PREFER_FULL | PATHSPEC_LITERAL_PATH, "", prune);
	revs->limited = 1;
}