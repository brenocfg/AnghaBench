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
struct commit {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  branch_merged (int,char const*,struct commit*,struct commit*) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,char const*,...) ; 
 struct commit* lookup_commit_reference (int /*<<< orphan*/ ,struct object_id const*) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static int check_branch_commit(const char *branchname, const char *refname,
			       const struct object_id *oid, struct commit *head_rev,
			       int kinds, int force)
{
	struct commit *rev = lookup_commit_reference(the_repository, oid);
	if (!rev) {
		error(_("Couldn't look up commit object for '%s'"), refname);
		return -1;
	}
	if (!force && !branch_merged(kinds, branchname, rev, head_rev)) {
		error(_("The branch '%s' is not fully merged.\n"
		      "If you are sure you want to delete it, "
		      "run 'git branch -D %s'."), branchname, branchname);
		return -1;
	}
	return 0;
}