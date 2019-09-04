#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct strbuf {int /*<<< orphan*/  buf; } ;
struct TYPE_2__ {int /*<<< orphan*/  oid; } ;
struct commit {TYPE_1__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_ABBREV ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*) ; 
 char const* find_unique_abbrev (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct commit* lookup_commit_reference_by_name (char const*) ; 
 int /*<<< orphan*/  printf_ln (int /*<<< orphan*/ ,char const*,...) ; 
 scalar_t__ ref_exists (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_check_branch_ref (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static void print_preparing_worktree_line(int detach,
					  const char *branch,
					  const char *new_branch,
					  int force_new_branch)
{
	if (force_new_branch) {
		struct commit *commit = lookup_commit_reference_by_name(new_branch);
		if (!commit)
			printf_ln(_("Preparing worktree (new branch '%s')"), new_branch);
		else
			printf_ln(_("Preparing worktree (resetting branch '%s'; was at %s)"),
				  new_branch,
				  find_unique_abbrev(&commit->object.oid, DEFAULT_ABBREV));
	} else if (new_branch) {
		printf_ln(_("Preparing worktree (new branch '%s')"), new_branch);
	} else {
		struct strbuf s = STRBUF_INIT;
		if (!detach && !strbuf_check_branch_ref(&s, branch) &&
		    ref_exists(s.buf))
			printf_ln(_("Preparing worktree (checking out '%s')"),
				  branch);
		else {
			struct commit *commit = lookup_commit_reference_by_name(branch);
			if (!commit)
				die(_("invalid reference: %s"), branch);
			printf_ln(_("Preparing worktree (detached HEAD %s)"),
				  find_unique_abbrev(&commit->object.oid, DEFAULT_ABBREV));
		}
		strbuf_release(&s);
	}
}