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
struct worktree {char* path; } ;
struct strbuf {int /*<<< orphan*/  buf; } ;
struct object_id {int dummy; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_ABBREV ; 
#define  FILTER_REFS_BRANCHES 129 
#define  FILTER_REFS_REMOTES 128 
 unsigned int INTERPRET_BRANCH_LOCAL ; 
 unsigned int INTERPRET_BRANCH_REMOTE ; 
 int REF_ISBROKEN ; 
 int REF_ISSYMREF ; 
 int /*<<< orphan*/  REF_NO_DEREF ; 
 int RESOLVE_REF_ALLOW_BAD_NAME ; 
 int RESOLVE_REF_NO_RECURSE ; 
 int RESOLVE_REF_READING ; 
 struct strbuf STRBUF_INIT ; 
 char* _ (char*) ; 
 scalar_t__ check_branch_commit (int /*<<< orphan*/ ,char*,struct object_id*,struct commit*,int,int) ; 
 int /*<<< orphan*/  delete_branch_config (int /*<<< orphan*/ ) ; 
 scalar_t__ delete_ref (int /*<<< orphan*/ *,char*,struct object_id*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ,...) ; 
 struct worktree* find_shared_symref (char*,char*) ; 
 char* find_unique_abbrev (struct object_id*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  head_oid ; 
 scalar_t__ is_null_oid (struct object_id*) ; 
 struct commit* lookup_commit_reference (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* mkpathdup (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,char*) ; 
 char* resolve_refdup (char*,int,struct object_id*,int*) ; 
 int /*<<< orphan*/  strbuf_branchname (struct strbuf*,char const*,unsigned int) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static int delete_branches(int argc, const char **argv, int force, int kinds,
			   int quiet)
{
	struct commit *head_rev = NULL;
	struct object_id oid;
	char *name = NULL;
	const char *fmt;
	int i;
	int ret = 0;
	int remote_branch = 0;
	struct strbuf bname = STRBUF_INIT;
	unsigned allowed_interpret;

	switch (kinds) {
	case FILTER_REFS_REMOTES:
		fmt = "refs/remotes/%s";
		/* For subsequent UI messages */
		remote_branch = 1;
		allowed_interpret = INTERPRET_BRANCH_REMOTE;

		force = 1;
		break;
	case FILTER_REFS_BRANCHES:
		fmt = "refs/heads/%s";
		allowed_interpret = INTERPRET_BRANCH_LOCAL;
		break;
	default:
		die(_("cannot use -a with -d"));
	}

	if (!force) {
		head_rev = lookup_commit_reference(the_repository, &head_oid);
		if (!head_rev)
			die(_("Couldn't look up commit object for HEAD"));
	}
	for (i = 0; i < argc; i++, strbuf_reset(&bname)) {
		char *target = NULL;
		int flags = 0;

		strbuf_branchname(&bname, argv[i], allowed_interpret);
		free(name);
		name = mkpathdup(fmt, bname.buf);

		if (kinds == FILTER_REFS_BRANCHES) {
			const struct worktree *wt =
				find_shared_symref("HEAD", name);
			if (wt) {
				error(_("Cannot delete branch '%s' "
					"checked out at '%s'"),
				      bname.buf, wt->path);
				ret = 1;
				continue;
			}
		}

		target = resolve_refdup(name,
					RESOLVE_REF_READING
					| RESOLVE_REF_NO_RECURSE
					| RESOLVE_REF_ALLOW_BAD_NAME,
					&oid, &flags);
		if (!target) {
			error(remote_branch
			      ? _("remote-tracking branch '%s' not found.")
			      : _("branch '%s' not found."), bname.buf);
			ret = 1;
			continue;
		}

		if (!(flags & (REF_ISSYMREF|REF_ISBROKEN)) &&
		    check_branch_commit(bname.buf, name, &oid, head_rev, kinds,
					force)) {
			ret = 1;
			goto next;
		}

		if (delete_ref(NULL, name, is_null_oid(&oid) ? NULL : &oid,
			       REF_NO_DEREF)) {
			error(remote_branch
			      ? _("Error deleting remote-tracking branch '%s'")
			      : _("Error deleting branch '%s'"),
			      bname.buf);
			ret = 1;
			goto next;
		}
		if (!quiet) {
			printf(remote_branch
			       ? _("Deleted remote-tracking branch %s (was %s).\n")
			       : _("Deleted branch %s (was %s).\n"),
			       bname.buf,
			       (flags & REF_ISBROKEN) ? "broken"
			       : (flags & REF_ISSYMREF) ? target
			       : find_unique_abbrev(&oid, DEFAULT_ABBREV));
		}
		delete_branch_config(bname.buf);

	next:
		free(target);
	}

	free(name);
	strbuf_release(&bname);

	return ret;
}