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
struct object_id {int dummy; } ;
struct commit_list {struct commit* item; scalar_t__ next; } ;
struct commit {int dummy; } ;
struct branch {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_ARRAY (struct commit**,int) ; 
 int DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ base_auto ; 
 struct branch* branch_get (int /*<<< orphan*/ *) ; 
 char* branch_get_upstream (struct branch*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  free (struct commit**) ; 
 int /*<<< orphan*/  free_commit_list (struct commit_list*) ; 
 struct commit_list* get_merge_bases (struct commit*,struct commit*) ; 
 struct commit_list* get_merge_bases_many (struct commit*,int,struct commit**) ; 
 scalar_t__ get_oid (char const*,struct object_id*) ; 
 int /*<<< orphan*/  in_merge_bases (struct commit*,struct commit*) ; 
 struct commit* lookup_commit_or_die (struct object_id*,char*) ; 
 struct commit* lookup_commit_reference_by_name (char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static struct commit *get_base_commit(const char *base_commit,
				      struct commit **list,
				      int total)
{
	struct commit *base = NULL;
	struct commit **rev;
	int i = 0, rev_nr = 0;

	if (base_commit && strcmp(base_commit, "auto")) {
		base = lookup_commit_reference_by_name(base_commit);
		if (!base)
			die(_("unknown commit %s"), base_commit);
	} else if ((base_commit && !strcmp(base_commit, "auto")) || base_auto) {
		struct branch *curr_branch = branch_get(NULL);
		const char *upstream = branch_get_upstream(curr_branch, NULL);
		if (upstream) {
			struct commit_list *base_list;
			struct commit *commit;
			struct object_id oid;

			if (get_oid(upstream, &oid))
				die(_("failed to resolve '%s' as a valid ref"), upstream);
			commit = lookup_commit_or_die(&oid, "upstream base");
			base_list = get_merge_bases_many(commit, total, list);
			/* There should be one and only one merge base. */
			if (!base_list || base_list->next)
				die(_("could not find exact merge base"));
			base = base_list->item;
			free_commit_list(base_list);
		} else {
			die(_("failed to get upstream, if you want to record base commit automatically,\n"
			      "please use git branch --set-upstream-to to track a remote branch.\n"
			      "Or you could specify base commit by --base=<base-commit-id> manually"));
		}
	}

	ALLOC_ARRAY(rev, total);
	for (i = 0; i < total; i++)
		rev[i] = list[i];

	rev_nr = total;
	/*
	 * Get merge base through pair-wise computations
	 * and store it in rev[0].
	 */
	while (rev_nr > 1) {
		for (i = 0; i < rev_nr / 2; i++) {
			struct commit_list *merge_base;
			merge_base = get_merge_bases(rev[2 * i], rev[2 * i + 1]);
			if (!merge_base || merge_base->next)
				die(_("failed to find exact merge base"));

			rev[i] = merge_base->item;
		}

		if (rev_nr % 2)
			rev[i] = rev[2 * i];
		rev_nr = DIV_ROUND_UP(rev_nr, 2);
	}

	if (!in_merge_bases(base, rev[0]))
		die(_("base commit should be the ancestor of revision list"));

	for (i = 0; i < total; i++) {
		if (base == list[i])
			die(_("base commit shouldn't be in revision list"));
	}

	free(rev);
	return base;
}