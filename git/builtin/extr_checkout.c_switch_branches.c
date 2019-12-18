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
struct checkout_opts {int /*<<< orphan*/  quiet; scalar_t__ only_merge_on_switching_branches; scalar_t__ orphan_from_empty_tree; scalar_t__ new_orphan_branch; } ;
struct branch_info {char* name; scalar_t__ commit; int /*<<< orphan*/ * path; } ;
typedef  int /*<<< orphan*/  old_branch_info ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 int REF_ISSYMREF ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/ * lookup_commit_reference_gently (int /*<<< orphan*/ ,struct object_id*,int) ; 
 int /*<<< orphan*/  memset (struct branch_info*,int /*<<< orphan*/ ,int) ; 
 int merge_working_tree (struct checkout_opts const*,struct branch_info*,struct branch_info*,int*) ; 
 int /*<<< orphan*/  orphaned_commit_warning (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  parse_commit_or_die (int /*<<< orphan*/ *) ; 
 int post_checkout_hook (scalar_t__,scalar_t__,int) ; 
 void* resolve_refdup (char*,int /*<<< orphan*/ ,struct object_id*,int*) ; 
 int /*<<< orphan*/  skip_prefix (int /*<<< orphan*/ *,char*,char**) ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  trace2_cmd_mode (char*) ; 
 int /*<<< orphan*/  update_refs_for_switch (struct checkout_opts const*,struct branch_info*,struct branch_info*) ; 

__attribute__((used)) static int switch_branches(const struct checkout_opts *opts,
			   struct branch_info *new_branch_info)
{
	int ret = 0;
	struct branch_info old_branch_info;
	void *path_to_free;
	struct object_id rev;
	int flag, writeout_error = 0;
	int do_merge = 1;

	trace2_cmd_mode("branch");

	memset(&old_branch_info, 0, sizeof(old_branch_info));
	old_branch_info.path = path_to_free = resolve_refdup("HEAD", 0, &rev, &flag);
	if (old_branch_info.path)
		old_branch_info.commit = lookup_commit_reference_gently(the_repository, &rev, 1);
	if (!(flag & REF_ISSYMREF))
		old_branch_info.path = NULL;

	if (old_branch_info.path)
		skip_prefix(old_branch_info.path, "refs/heads/", &old_branch_info.name);

	if (opts->new_orphan_branch && opts->orphan_from_empty_tree) {
		if (new_branch_info->name)
			BUG("'switch --orphan' should never accept a commit as starting point");
		new_branch_info->commit = NULL;
		new_branch_info->name = "(empty)";
		do_merge = 1;
	}

	if (!new_branch_info->name) {
		new_branch_info->name = "HEAD";
		new_branch_info->commit = old_branch_info.commit;
		if (!new_branch_info->commit)
			die(_("You are on a branch yet to be born"));
		parse_commit_or_die(new_branch_info->commit);

		if (opts->only_merge_on_switching_branches)
			do_merge = 0;
	}

	if (do_merge) {
		ret = merge_working_tree(opts, &old_branch_info, new_branch_info, &writeout_error);
		if (ret) {
			free(path_to_free);
			return ret;
		}
	}

	if (!opts->quiet && !old_branch_info.path && old_branch_info.commit && new_branch_info->commit != old_branch_info.commit)
		orphaned_commit_warning(old_branch_info.commit, new_branch_info->commit);

	update_refs_for_switch(opts, &old_branch_info, new_branch_info);

	ret = post_checkout_hook(old_branch_info.commit, new_branch_info->commit, 1);
	free(path_to_free);
	return ret || writeout_error;
}