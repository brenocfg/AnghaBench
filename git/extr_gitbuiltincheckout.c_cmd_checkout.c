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
struct strbuf {int dummy; } ;
struct option {char* member_2; char* member_4; char* member_5; int /*<<< orphan*/  member_7; int /*<<< orphan*/  member_6; int /*<<< orphan*/ * member_3; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct object_id {int dummy; } ;
struct TYPE_2__ {scalar_t__ nr; } ;
struct checkout_opts {char* new_branch; char* new_branch_force; int new_branch_log; int force_detach; scalar_t__ track; char* new_orphan_branch; int merge; int overwrite_ignore; int patch_mode; int ignore_skipworktree; int ignore_other_worktrees; int show_progress; int overlay_mode; char const* prefix; int /*<<< orphan*/  name; TYPE_1__ pathspec; int /*<<< orphan*/  branch_exists; int /*<<< orphan*/  force; int /*<<< orphan*/  writeout_stage; scalar_t__ quiet; } ;
struct branch_info {char* new_branch; char* new_branch_force; int new_branch_log; int force_detach; scalar_t__ track; char* new_orphan_branch; int merge; int overwrite_ignore; int patch_mode; int ignore_skipworktree; int ignore_other_worktrees; int show_progress; int overlay_mode; char const* prefix; int /*<<< orphan*/  name; TYPE_1__ pathspec; int /*<<< orphan*/  branch_exists; int /*<<< orphan*/  force; int /*<<< orphan*/  writeout_stage; scalar_t__ quiet; } ;
typedef  int /*<<< orphan*/  opts ;
typedef  int /*<<< orphan*/  new_branch_info ;

/* Variables and functions */
 int /*<<< orphan*/  BRANCH_TRACK_EXPLICIT ; 
 scalar_t__ BRANCH_TRACK_UNSPECIFIED ; 
 int /*<<< orphan*/  N_ (char*) ; 
 int /*<<< orphan*/  OPTION_CALLBACK ; 
 struct option OPT_BOOL (char,char*,int*,int /*<<< orphan*/ ) ; 
 struct option OPT_BOOL_F (int /*<<< orphan*/ ,char*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct option OPT_END () ; 
 struct option OPT_SET_INT (char,char*,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct option OPT_SET_INT_F (char,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct option OPT_STRING (char,char*,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct option OPT__FORCE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct option OPT__QUIET (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PARSE_OPT_KEEP_DASHDASH ; 
 int /*<<< orphan*/  PARSE_OPT_NOCOMPLETE ; 
 int /*<<< orphan*/  PARSE_OPT_NONEG ; 
 int /*<<< orphan*/  PARSE_OPT_OPTARG ; 
 int /*<<< orphan*/  PATHSPEC_PREFIX_ORIGIN ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  UNLEAK (struct checkout_opts) ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ advice_checkout_ambiguous_remote_branch_name ; 
 int /*<<< orphan*/  advise (int /*<<< orphan*/ ,char const*,int) ; 
 int checkout_branch (struct checkout_opts*,struct checkout_opts*) ; 
 int checkout_paths (struct checkout_opts*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  checkout_usage ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  git_checkout_config ; 
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,struct checkout_opts*) ; 
 int /*<<< orphan*/  git_xmerge_config (char*,char*,int /*<<< orphan*/ *) ; 
 int isatty (int) ; 
 int /*<<< orphan*/  memset (struct checkout_opts*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  option_parse_recurse_submodules_worktree_updater ; 
 int parse_branchname_arg (int,char const**,int,struct checkout_opts*,struct checkout_opts*,struct object_id*,int*) ; 
 int parse_options (int,char const**,char const*,struct option*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_pathspec (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char const**) ; 
 int /*<<< orphan*/  skip_prefix (char const*,char*,char const**) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  validate_branchname (char const*,struct strbuf*) ; 
 int /*<<< orphan*/  validate_new_branchname (char const*,struct strbuf*,int /*<<< orphan*/ ) ; 

int cmd_checkout(int argc, const char **argv, const char *prefix)
{
	struct checkout_opts opts;
	struct branch_info new_branch_info;
	char *conflict_style = NULL;
	int dwim_new_local_branch, no_dwim_new_local_branch = 0;
	int dwim_remotes_matched = 0;
	struct option options[] = {
		OPT__QUIET(&opts.quiet, N_("suppress progress reporting")),
		OPT_STRING('b', NULL, &opts.new_branch, N_("branch"),
			   N_("create and checkout a new branch")),
		OPT_STRING('B', NULL, &opts.new_branch_force, N_("branch"),
			   N_("create/reset and checkout a branch")),
		OPT_BOOL('l', NULL, &opts.new_branch_log, N_("create reflog for new branch")),
		OPT_BOOL(0, "detach", &opts.force_detach, N_("detach HEAD at named commit")),
		OPT_SET_INT('t', "track",  &opts.track, N_("set upstream info for new branch"),
			BRANCH_TRACK_EXPLICIT),
		OPT_STRING(0, "orphan", &opts.new_orphan_branch, N_("new-branch"), N_("new unparented branch")),
		OPT_SET_INT_F('2', "ours", &opts.writeout_stage,
			      N_("checkout our version for unmerged files"),
			      2, PARSE_OPT_NONEG),
		OPT_SET_INT_F('3', "theirs", &opts.writeout_stage,
			      N_("checkout their version for unmerged files"),
			      3, PARSE_OPT_NONEG),
		OPT__FORCE(&opts.force, N_("force checkout (throw away local modifications)"),
			   PARSE_OPT_NOCOMPLETE),
		OPT_BOOL('m', "merge", &opts.merge, N_("perform a 3-way merge with the new branch")),
		OPT_BOOL_F(0, "overwrite-ignore", &opts.overwrite_ignore,
			   N_("update ignored files (default)"),
			   PARSE_OPT_NOCOMPLETE),
		OPT_STRING(0, "conflict", &conflict_style, N_("style"),
			   N_("conflict style (merge or diff3)")),
		OPT_BOOL('p', "patch", &opts.patch_mode, N_("select hunks interactively")),
		OPT_BOOL(0, "ignore-skip-worktree-bits", &opts.ignore_skipworktree,
			 N_("do not limit pathspecs to sparse entries only")),
		OPT_BOOL(0, "no-guess", &no_dwim_new_local_branch,
			 N_("do not second guess 'git checkout <no-such-branch>'")),
		OPT_BOOL(0, "ignore-other-worktrees", &opts.ignore_other_worktrees,
			 N_("do not check if another worktree is holding the given ref")),
		{ OPTION_CALLBACK, 0, "recurse-submodules", NULL,
			    "checkout", "control recursive updating of submodules",
			    PARSE_OPT_OPTARG, option_parse_recurse_submodules_worktree_updater },
		OPT_BOOL(0, "progress", &opts.show_progress, N_("force progress reporting")),
		OPT_BOOL(0, "overlay", &opts.overlay_mode, N_("use overlay mode (default)")),
		OPT_END(),
	};

	memset(&opts, 0, sizeof(opts));
	memset(&new_branch_info, 0, sizeof(new_branch_info));
	opts.overwrite_ignore = 1;
	opts.prefix = prefix;
	opts.show_progress = -1;
	opts.overlay_mode = -1;

	git_config(git_checkout_config, &opts);

	opts.track = BRANCH_TRACK_UNSPECIFIED;

	argc = parse_options(argc, argv, prefix, options, checkout_usage,
			     PARSE_OPT_KEEP_DASHDASH);

	dwim_new_local_branch = !no_dwim_new_local_branch;
	if (opts.show_progress < 0) {
		if (opts.quiet)
			opts.show_progress = 0;
		else
			opts.show_progress = isatty(2);
	}

	if (conflict_style) {
		opts.merge = 1; /* implied */
		git_xmerge_config("merge.conflictstyle", conflict_style, NULL);
	}

	if ((!!opts.new_branch + !!opts.new_branch_force + !!opts.new_orphan_branch) > 1)
		die(_("-b, -B and --orphan are mutually exclusive"));

	if (opts.overlay_mode == 1 && opts.patch_mode)
		die(_("-p and --overlay are mutually exclusive"));

	/*
	 * From here on, new_branch will contain the branch to be checked out,
	 * and new_branch_force and new_orphan_branch will tell us which one of
	 * -b/-B/--orphan is being used.
	 */
	if (opts.new_branch_force)
		opts.new_branch = opts.new_branch_force;

	if (opts.new_orphan_branch)
		opts.new_branch = opts.new_orphan_branch;

	/* --track without -b/-B/--orphan should DWIM */
	if (opts.track != BRANCH_TRACK_UNSPECIFIED && !opts.new_branch) {
		const char *argv0 = argv[0];
		if (!argc || !strcmp(argv0, "--"))
			die(_("--track needs a branch name"));
		skip_prefix(argv0, "refs/", &argv0);
		skip_prefix(argv0, "remotes/", &argv0);
		argv0 = strchr(argv0, '/');
		if (!argv0 || !argv0[1])
			die(_("missing branch name; try -b"));
		opts.new_branch = argv0 + 1;
	}

	/*
	 * Extract branch name from command line arguments, so
	 * all that is left is pathspecs.
	 *
	 * Handle
	 *
	 *  1) git checkout <tree> -- [<paths>]
	 *  2) git checkout -- [<paths>]
	 *  3) git checkout <something> [<paths>]
	 *
	 * including "last branch" syntax and DWIM-ery for names of
	 * remote branches, erroring out for invalid or ambiguous cases.
	 */
	if (argc) {
		struct object_id rev;
		int dwim_ok =
			!opts.patch_mode &&
			dwim_new_local_branch &&
			opts.track == BRANCH_TRACK_UNSPECIFIED &&
			!opts.new_branch;
		int n = parse_branchname_arg(argc, argv, dwim_ok,
					     &new_branch_info, &opts, &rev,
					     &dwim_remotes_matched);
		argv += n;
		argc -= n;
	}

	if (argc) {
		parse_pathspec(&opts.pathspec, 0,
			       opts.patch_mode ? PATHSPEC_PREFIX_ORIGIN : 0,
			       prefix, argv);

		if (!opts.pathspec.nr)
			die(_("invalid path specification"));

		/*
		 * Try to give more helpful suggestion.
		 * new_branch && argc > 1 will be caught later.
		 */
		if (opts.new_branch && argc == 1)
			die(_("'%s' is not a commit and a branch '%s' cannot be created from it"),
				argv[0], opts.new_branch);

		if (opts.force_detach)
			die(_("git checkout: --detach does not take a path argument '%s'"),
			    argv[0]);

		if (1 < !!opts.writeout_stage + !!opts.force + !!opts.merge)
			die(_("git checkout: --ours/--theirs, --force and --merge are incompatible when\n"
			      "checking out of the index."));
	}

	if (opts.new_branch) {
		struct strbuf buf = STRBUF_INIT;

		if (opts.new_branch_force)
			opts.branch_exists = validate_branchname(opts.new_branch, &buf);
		else
			opts.branch_exists =
				validate_new_branchname(opts.new_branch, &buf, 0);
		strbuf_release(&buf);
	}

	UNLEAK(opts);
	if (opts.patch_mode || opts.pathspec.nr) {
		int ret = checkout_paths(&opts, new_branch_info.name);
		if (ret && dwim_remotes_matched > 1 &&
		    advice_checkout_ambiguous_remote_branch_name)
			advise(_("'%s' matched more than one remote tracking branch.\n"
				 "We found %d remotes with a reference that matched. So we fell back\n"
				 "on trying to resolve the argument as a path, but failed there too!\n"
				 "\n"
				 "If you meant to check out a remote tracking branch on, e.g. 'origin',\n"
				 "you can do so by fully qualifying the name with the --track option:\n"
				 "\n"
				 "    git checkout --track origin/<name>\n"
				 "\n"
				 "If you'd like to always have checkouts of an ambiguous <name> prefer\n"
				 "one remote, e.g. the 'origin' remote, consider setting\n"
				 "checkout.defaultRemote=origin in your config."),
			       argv[0],
			       dwim_remotes_matched);
		return ret;
	} else {
		return checkout_branch(&opts, &new_branch_info);
	}
}