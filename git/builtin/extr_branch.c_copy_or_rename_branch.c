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
struct strbuf {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ copy_existing_ref (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,...) ; 
 scalar_t__ git_config_copy_section (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ git_config_rename_section (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ref_exists (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reject_rebase_or_bisect_branch (int /*<<< orphan*/ ) ; 
 scalar_t__ rename_ref (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ replace_each_worktree_head_symref (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip_prefix (int /*<<< orphan*/ ,char*,char const**) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*,...) ; 
 scalar_t__ strbuf_check_branch_ref (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  validate_branchname (char const*,struct strbuf*) ; 
 int /*<<< orphan*/  validate_new_branchname (char const*,struct strbuf*,int) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void copy_or_rename_branch(const char *oldname, const char *newname, int copy, int force)
{
	struct strbuf oldref = STRBUF_INIT, newref = STRBUF_INIT, logmsg = STRBUF_INIT;
	struct strbuf oldsection = STRBUF_INIT, newsection = STRBUF_INIT;
	const char *interpreted_oldname = NULL;
	const char *interpreted_newname = NULL;
	int recovery = 0;

	if (!oldname) {
		if (copy)
			die(_("cannot copy the current branch while not on any."));
		else
			die(_("cannot rename the current branch while not on any."));
	}

	if (strbuf_check_branch_ref(&oldref, oldname)) {
		/*
		 * Bad name --- this could be an attempt to rename a
		 * ref that we used to allow to be created by accident.
		 */
		if (ref_exists(oldref.buf))
			recovery = 1;
		else
			die(_("Invalid branch name: '%s'"), oldname);
	}

	/*
	 * A command like "git branch -M currentbranch currentbranch" cannot
	 * cause the worktree to become inconsistent with HEAD, so allow it.
	 */
	if (!strcmp(oldname, newname))
		validate_branchname(newname, &newref);
	else
		validate_new_branchname(newname, &newref, force);

	reject_rebase_or_bisect_branch(oldref.buf);

	if (!skip_prefix(oldref.buf, "refs/heads/", &interpreted_oldname) ||
	    !skip_prefix(newref.buf, "refs/heads/", &interpreted_newname)) {
		BUG("expected prefix missing for refs");
	}

	if (copy)
		strbuf_addf(&logmsg, "Branch: copied %s to %s",
			    oldref.buf, newref.buf);
	else
		strbuf_addf(&logmsg, "Branch: renamed %s to %s",
			    oldref.buf, newref.buf);

	if (!copy && rename_ref(oldref.buf, newref.buf, logmsg.buf))
		die(_("Branch rename failed"));
	if (copy && copy_existing_ref(oldref.buf, newref.buf, logmsg.buf))
		die(_("Branch copy failed"));

	if (recovery) {
		if (copy)
			warning(_("Created a copy of a misnamed branch '%s'"),
				interpreted_oldname);
		else
			warning(_("Renamed a misnamed branch '%s' away"),
				interpreted_oldname);
	}

	if (!copy &&
	    replace_each_worktree_head_symref(oldref.buf, newref.buf, logmsg.buf))
		die(_("Branch renamed to %s, but HEAD is not updated!"), newname);

	strbuf_release(&logmsg);

	strbuf_addf(&oldsection, "branch.%s", interpreted_oldname);
	strbuf_release(&oldref);
	strbuf_addf(&newsection, "branch.%s", interpreted_newname);
	strbuf_release(&newref);
	if (!copy && git_config_rename_section(oldsection.buf, newsection.buf) < 0)
		die(_("Branch is renamed, but update of config-file failed"));
	if (copy && strcmp(oldname, newname) && git_config_copy_section(oldsection.buf, newsection.buf) < 0)
		die(_("Branch is copied, but update of config-file failed"));
	strbuf_release(&oldsection);
	strbuf_release(&newsection);
}