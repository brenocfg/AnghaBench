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
struct object_id {int dummy; } ;
struct checkout_opts {struct tree* source_tree; } ;
struct branch_info {char const* name; int /*<<< orphan*/  commit; int /*<<< orphan*/ * path; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_refname_format (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct tree* get_commit_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lookup_commit_reference_gently (int /*<<< orphan*/ ,struct object_id*,int) ; 
 int /*<<< orphan*/  oidcpy (struct object_id*,struct object_id*) ; 
 int /*<<< orphan*/  parse_commit_or_die (int /*<<< orphan*/ ) ; 
 struct tree* parse_tree_indirect (struct object_id*) ; 
 int /*<<< orphan*/  read_ref (int /*<<< orphan*/ *,struct object_id*) ; 
 int /*<<< orphan*/  setup_branch_path (struct branch_info*) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static void setup_new_branch_info_and_source_tree(
	struct branch_info *new_branch_info,
	struct checkout_opts *opts,
	struct object_id *rev,
	const char *arg)
{
	struct tree **source_tree = &opts->source_tree;
	struct object_id branch_rev;

	new_branch_info->name = arg;
	setup_branch_path(new_branch_info);

	if (!check_refname_format(new_branch_info->path, 0) &&
	    !read_ref(new_branch_info->path, &branch_rev))
		oidcpy(rev, &branch_rev);
	else
		new_branch_info->path = NULL; /* not an existing branch */

	new_branch_info->commit = lookup_commit_reference_gently(the_repository, rev, 1);
	if (!new_branch_info->commit) {
		/* not a commit */
		*source_tree = parse_tree_indirect(rev);
	} else {
		parse_commit_or_die(new_branch_info->commit);
		*source_tree = get_commit_tree(new_branch_info->commit);
	}
}