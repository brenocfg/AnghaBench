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
struct checkout_opts {char* new_branch; int count_checkout_paths; scalar_t__ accept_pathspec; int /*<<< orphan*/  prefix; int /*<<< orphan*/  source_tree; int /*<<< orphan*/  quiet; } ;
struct branch_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ check_filename (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,...) ; 
 scalar_t__ get_oid_mb (char const*,struct object_id*) ; 
 int /*<<< orphan*/  no_wildcard (char const*) ; 
 int /*<<< orphan*/  setup_new_branch_info_and_source_tree (struct branch_info*,struct checkout_opts*,struct object_id*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 char* unique_tracking_name (char const*,struct object_id*,int*) ; 
 int /*<<< orphan*/  verify_non_filename (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int parse_branchname_arg(int argc, const char **argv,
				int dwim_new_local_branch_ok,
				struct branch_info *new_branch_info,
				struct checkout_opts *opts,
				struct object_id *rev,
				int *dwim_remotes_matched)
{
	const char **new_branch = &opts->new_branch;
	int argcount = 0;
	const char *arg;
	int dash_dash_pos;
	int has_dash_dash = 0;
	int i;

	/*
	 * case 1: git checkout <ref> -- [<paths>]
	 *
	 *   <ref> must be a valid tree, everything after the '--' must be
	 *   a path.
	 *
	 * case 2: git checkout -- [<paths>]
	 *
	 *   everything after the '--' must be paths.
	 *
	 * case 3: git checkout <something> [--]
	 *
	 *   (a) If <something> is a commit, that is to
	 *       switch to the branch or detach HEAD at it.  As a special case,
	 *       if <something> is A...B (missing A or B means HEAD but you can
	 *       omit at most one side), and if there is a unique merge base
	 *       between A and B, A...B names that merge base.
	 *
	 *   (b) If <something> is _not_ a commit, either "--" is present
	 *       or <something> is not a path, no -t or -b was given, and
	 *       and there is a tracking branch whose name is <something>
	 *       in one and only one remote (or if the branch exists on the
	 *       remote named in checkout.defaultRemote), then this is a
	 *       short-hand to fork local <something> from that
	 *       remote-tracking branch.
	 *
	 *   (c) Otherwise, if "--" is present, treat it like case (1).
	 *
	 *   (d) Otherwise :
	 *       - if it's a reference, treat it like case (1)
	 *       - else if it's a path, treat it like case (2)
	 *       - else: fail.
	 *
	 * case 4: git checkout <something> <paths>
	 *
	 *   The first argument must not be ambiguous.
	 *   - If it's *only* a reference, treat it like case (1).
	 *   - If it's only a path, treat it like case (2).
	 *   - else: fail.
	 *
	 */
	if (!argc)
		return 0;

	if (!opts->accept_pathspec) {
		if (argc > 1)
			die(_("only one reference expected"));
		has_dash_dash = 1; /* helps disambiguate */
	}

	arg = argv[0];
	dash_dash_pos = -1;
	for (i = 0; i < argc; i++) {
		if (opts->accept_pathspec && !strcmp(argv[i], "--")) {
			dash_dash_pos = i;
			break;
		}
	}
	if (dash_dash_pos == 0)
		return 1; /* case (2) */
	else if (dash_dash_pos == 1)
		has_dash_dash = 1; /* case (3) or (1) */
	else if (dash_dash_pos >= 2)
		die(_("only one reference expected, %d given."), dash_dash_pos);
	opts->count_checkout_paths = !opts->quiet && !has_dash_dash;

	if (!strcmp(arg, "-"))
		arg = "@{-1}";

	if (get_oid_mb(arg, rev)) {
		/*
		 * Either case (3) or (4), with <something> not being
		 * a commit, or an attempt to use case (1) with an
		 * invalid ref.
		 *
		 * It's likely an error, but we need to find out if
		 * we should auto-create the branch, case (3).(b).
		 */
		int recover_with_dwim = dwim_new_local_branch_ok;

		int could_be_checkout_paths = !has_dash_dash &&
			check_filename(opts->prefix, arg);

		if (!has_dash_dash && !no_wildcard(arg))
			recover_with_dwim = 0;

		/*
		 * Accept "git checkout foo", "git checkout foo --"
		 * and "git switch foo" as candidates for dwim.
		 */
		if (!(argc == 1 && !has_dash_dash) &&
		    !(argc == 2 && has_dash_dash) &&
		    opts->accept_pathspec)
			recover_with_dwim = 0;

		if (recover_with_dwim) {
			const char *remote = unique_tracking_name(arg, rev,
								  dwim_remotes_matched);
			if (remote) {
				if (could_be_checkout_paths)
					die(_("'%s' could be both a local file and a tracking branch.\n"
					      "Please use -- (and optionally --no-guess) to disambiguate"),
					    arg);
				*new_branch = arg;
				arg = remote;
				/* DWIMmed to create local branch, case (3).(b) */
			} else {
				recover_with_dwim = 0;
			}
		}

		if (!recover_with_dwim) {
			if (has_dash_dash)
				die(_("invalid reference: %s"), arg);
			return argcount;
		}
	}

	/* we can't end up being in (2) anymore, eat the argument */
	argcount++;
	argv++;
	argc--;

	setup_new_branch_info_and_source_tree(new_branch_info, opts, rev, arg);

	if (!opts->source_tree)                   /* case (1): want a tree */
		die(_("reference is not a tree: %s"), arg);

	if (!has_dash_dash) {	/* case (3).(d) -> (1) */
		/*
		 * Do not complain the most common case
		 *	git checkout branch
		 * even if there happen to be a file called 'branch';
		 * it would be extremely annoying.
		 */
		if (argc)
			verify_non_filename(opts->prefix, arg);
	} else if (opts->accept_pathspec) {
		argcount++;
		argv++;
		argc--;
	}

	return argcount;
}