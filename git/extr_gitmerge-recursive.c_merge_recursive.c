#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct tree {int dummy; } ;
struct merge_options {char* branch1; char* branch2; char* ancestor; int buffer_output; int /*<<< orphan*/  needed_rename_limit; int /*<<< orphan*/  obuf; scalar_t__ call_depth; TYPE_2__* repo; } ;
struct commit_list {struct commit* item; struct commit_list* next; } ;
struct commit {TYPE_5__* parents; } ;
struct TYPE_8__ {struct TYPE_8__* next; } ;
struct TYPE_7__ {int /*<<< orphan*/  index; TYPE_1__* hash_algo; } ;
struct TYPE_6__ {int /*<<< orphan*/  empty_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  Q_ (char*,char*,unsigned int) ; 
 int /*<<< orphan*/  _ (char*) ; 
 unsigned int commit_list_count (struct commit_list*) ; 
 int /*<<< orphan*/  commit_list_insert (struct commit*,TYPE_5__**) ; 
 int /*<<< orphan*/  diff_warn_rename_limit (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  discard_index (int /*<<< orphan*/ ) ; 
 int err (struct merge_options*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_output (struct merge_options*) ; 
 int /*<<< orphan*/  get_commit_tree (struct commit*) ; 
 struct commit_list* get_merge_bases (struct commit*,struct commit*) ; 
 struct tree* lookup_tree (TYPE_2__*,int /*<<< orphan*/ ) ; 
 struct commit* make_virtual_commit (TYPE_2__*,struct tree*,char*) ; 
 int merge_trees (struct merge_options*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tree**) ; 
 int /*<<< orphan*/  output (struct merge_options*,int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  output_commit_title (struct merge_options*,struct commit*) ; 
 struct commit* pop_commit (struct commit_list**) ; 
 int /*<<< orphan*/  repo_read_index (TYPE_2__*) ; 
 struct commit_list* reverse_commit_list (struct commit_list*) ; 
 scalar_t__ show (struct merge_options*,int) ; 
 int /*<<< orphan*/  strbuf_release (int /*<<< orphan*/ *) ; 

int merge_recursive(struct merge_options *o,
		    struct commit *h1,
		    struct commit *h2,
		    struct commit_list *ca,
		    struct commit **result)
{
	struct commit_list *iter;
	struct commit *merged_common_ancestors;
	struct tree *mrtree;
	int clean;

	if (show(o, 4)) {
		output(o, 4, _("Merging:"));
		output_commit_title(o, h1);
		output_commit_title(o, h2);
	}

	if (!ca) {
		ca = get_merge_bases(h1, h2);
		ca = reverse_commit_list(ca);
	}

	if (show(o, 5)) {
		unsigned cnt = commit_list_count(ca);

		output(o, 5, Q_("found %u common ancestor:",
				"found %u common ancestors:", cnt), cnt);
		for (iter = ca; iter; iter = iter->next)
			output_commit_title(o, iter->item);
	}

	merged_common_ancestors = pop_commit(&ca);
	if (merged_common_ancestors == NULL) {
		/* if there is no common ancestor, use an empty tree */
		struct tree *tree;

		tree = lookup_tree(o->repo, o->repo->hash_algo->empty_tree);
		merged_common_ancestors = make_virtual_commit(o->repo, tree, "ancestor");
	}

	for (iter = ca; iter; iter = iter->next) {
		const char *saved_b1, *saved_b2;
		o->call_depth++;
		/*
		 * When the merge fails, the result contains files
		 * with conflict markers. The cleanness flag is
		 * ignored (unless indicating an error), it was never
		 * actually used, as result of merge_trees has always
		 * overwritten it: the committed "conflicts" were
		 * already resolved.
		 */
		discard_index(o->repo->index);
		saved_b1 = o->branch1;
		saved_b2 = o->branch2;
		o->branch1 = "Temporary merge branch 1";
		o->branch2 = "Temporary merge branch 2";
		if (merge_recursive(o, merged_common_ancestors, iter->item,
				    NULL, &merged_common_ancestors) < 0)
			return -1;
		o->branch1 = saved_b1;
		o->branch2 = saved_b2;
		o->call_depth--;

		if (!merged_common_ancestors)
			return err(o, _("merge returned no commit"));
	}

	discard_index(o->repo->index);
	if (!o->call_depth)
		repo_read_index(o->repo);

	o->ancestor = "merged common ancestors";
	clean = merge_trees(o, get_commit_tree(h1), get_commit_tree(h2),
			    get_commit_tree(merged_common_ancestors),
			    &mrtree);
	if (clean < 0) {
		flush_output(o);
		return clean;
	}

	if (o->call_depth) {
		*result = make_virtual_commit(o->repo, mrtree, "merged tree");
		commit_list_insert(h1, &(*result)->parents);
		commit_list_insert(h2, &(*result)->parents->next);
	}
	flush_output(o);
	if (!o->call_depth && o->buffer_output < 2)
		strbuf_release(&o->obuf);
	if (show(o, 2))
		diff_warn_rename_limit("merge.renamelimit",
				       o->needed_rename_limit, 0);
	return clean;
}