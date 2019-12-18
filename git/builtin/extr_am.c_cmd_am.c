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
struct option {char member_1; char* member_2; char const* member_4; char const* member_5; intptr_t member_8; int /*<<< orphan*/ * member_7; int /*<<< orphan*/  member_6; int /*<<< orphan*/ * member_3; int /*<<< orphan*/  member_0; } ;
struct argv_array {int /*<<< orphan*/  argv; int /*<<< orphan*/  argc; } ;
struct am_state {scalar_t__ signoff; scalar_t__ keep; int rebasing; scalar_t__ interactive; int /*<<< orphan*/  dir; int /*<<< orphan*/  sign_commit; int /*<<< orphan*/  allow_rerere_autoupdate; scalar_t__ ignore_date; scalar_t__ committer_date_is_author_date; int /*<<< orphan*/  resolvemsg; int /*<<< orphan*/  git_apply_opts; scalar_t__ scissors; scalar_t__ message_id; scalar_t__ utf8; int /*<<< orphan*/  quiet; scalar_t__ threeway; } ;
typedef  enum resume_mode { ____Placeholder_resume_mode } resume_mode ;

/* Variables and functions */
 struct argv_array ARGV_ARRAY_INIT ; 
 int /*<<< orphan*/  BUG (char*) ; 
 int /*<<< orphan*/  IDENT_STRICT ; 
 scalar_t__ KEEP_NON_PATCH ; 
 scalar_t__ KEEP_TRUE ; 
 char const* N_ (char*) ; 
 int /*<<< orphan*/  OPTION_STRING ; 
 struct option OPT_BOOL (char,char*,scalar_t__*,char const*) ; 
 struct option OPT_CALLBACK (int /*<<< orphan*/ ,char*,int*,char const*,char const*,int /*<<< orphan*/ ) ; 
 struct option OPT_CMDMODE (char,char*,int*,char const*,int) ; 
 struct option OPT_END () ; 
 struct option OPT_HIDDEN_BOOL (char,char*,int*,char const*) ; 
 struct option OPT_PASSTHRU_ARGV (char,char*,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ) ; 
 struct option OPT_RERERE_AUTOUPDATE (int /*<<< orphan*/ *) ; 
 struct option OPT_SET_INT (char,char*,scalar_t__*,char const*,scalar_t__) ; 
 struct option OPT_SET_INT_F (int /*<<< orphan*/ ,char*,int*,char const*,int,int /*<<< orphan*/ ) ; 
 struct option OPT_STRING (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 struct option OPT__QUIET (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  PARSE_OPT_NOARG ; 
 int /*<<< orphan*/  PARSE_OPT_NONEG ; 
 int /*<<< orphan*/  PARSE_OPT_OPTARG ; 
 int PATCH_FORMAT_UNKNOWN ; 
#define  RESUME_ABORT 134 
#define  RESUME_APPLY 133 
#define  RESUME_FALSE 132 
#define  RESUME_QUIT 131 
#define  RESUME_RESOLVED 130 
#define  RESUME_SHOW_PATCH 129 
#define  RESUME_SKIP 128 
 scalar_t__ SIGNOFF_EXPLICIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  am_abort (struct am_state*) ; 
 int /*<<< orphan*/  am_append_signoff (struct am_state*) ; 
 int /*<<< orphan*/  am_destroy (struct am_state*) ; 
 int am_in_progress (struct am_state*) ; 
 int /*<<< orphan*/  am_load (struct am_state*) ; 
 int /*<<< orphan*/  am_rerere_clear () ; 
 int /*<<< orphan*/  am_resolve (struct am_state*) ; 
 int /*<<< orphan*/  am_run (struct am_state*,int) ; 
 int /*<<< orphan*/  am_setup (struct am_state*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  am_skip (struct am_state*) ; 
 int /*<<< orphan*/  am_state_init (struct am_state*) ; 
 int /*<<< orphan*/  am_state_release (struct am_state*) ; 
 int /*<<< orphan*/  argv_array_clear (struct argv_array*) ; 
 int /*<<< orphan*/  argv_array_push (struct argv_array*,char const*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,...) ; 
 scalar_t__ file_exists (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf_ln (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_am_config ; 
 int /*<<< orphan*/  git_committer_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ is_absolute_path (char const*) ; 
 int /*<<< orphan*/  isatty (int /*<<< orphan*/ ) ; 
 char const* mkpath (char*,char const*,char const*) ; 
 int /*<<< orphan*/  parse_opt_patchformat ; 
 int parse_options (int,char const**,char const*,struct option*,char const* const*,int /*<<< orphan*/ ) ; 
 scalar_t__ repo_read_index_preload (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int show_patch (struct am_state*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  usage_with_options (char const* const*,struct option*) ; 

int cmd_am(int argc, const char **argv, const char *prefix)
{
	struct am_state state;
	int binary = -1;
	int keep_cr = -1;
	int patch_format = PATCH_FORMAT_UNKNOWN;
	enum resume_mode resume = RESUME_FALSE;
	int in_progress;
	int ret = 0;

	const char * const usage[] = {
		N_("git am [<options>] [(<mbox> | <Maildir>)...]"),
		N_("git am [<options>] (--continue | --skip | --abort)"),
		NULL
	};

	struct option options[] = {
		OPT_BOOL('i', "interactive", &state.interactive,
			N_("run interactively")),
		OPT_HIDDEN_BOOL('b', "binary", &binary,
			N_("historical option -- no-op")),
		OPT_BOOL('3', "3way", &state.threeway,
			N_("allow fall back on 3way merging if needed")),
		OPT__QUIET(&state.quiet, N_("be quiet")),
		OPT_SET_INT('s', "signoff", &state.signoff,
			N_("add a Signed-off-by line to the commit message"),
			SIGNOFF_EXPLICIT),
		OPT_BOOL('u', "utf8", &state.utf8,
			N_("recode into utf8 (default)")),
		OPT_SET_INT('k', "keep", &state.keep,
			N_("pass -k flag to git-mailinfo"), KEEP_TRUE),
		OPT_SET_INT(0, "keep-non-patch", &state.keep,
			N_("pass -b flag to git-mailinfo"), KEEP_NON_PATCH),
		OPT_BOOL('m', "message-id", &state.message_id,
			N_("pass -m flag to git-mailinfo")),
		OPT_SET_INT_F(0, "keep-cr", &keep_cr,
			N_("pass --keep-cr flag to git-mailsplit for mbox format"),
			1, PARSE_OPT_NONEG),
		OPT_SET_INT_F(0, "no-keep-cr", &keep_cr,
			N_("do not pass --keep-cr flag to git-mailsplit independent of am.keepcr"),
			0, PARSE_OPT_NONEG),
		OPT_BOOL('c', "scissors", &state.scissors,
			N_("strip everything before a scissors line")),
		OPT_PASSTHRU_ARGV(0, "whitespace", &state.git_apply_opts, N_("action"),
			N_("pass it through git-apply"),
			0),
		OPT_PASSTHRU_ARGV(0, "ignore-space-change", &state.git_apply_opts, NULL,
			N_("pass it through git-apply"),
			PARSE_OPT_NOARG),
		OPT_PASSTHRU_ARGV(0, "ignore-whitespace", &state.git_apply_opts, NULL,
			N_("pass it through git-apply"),
			PARSE_OPT_NOARG),
		OPT_PASSTHRU_ARGV(0, "directory", &state.git_apply_opts, N_("root"),
			N_("pass it through git-apply"),
			0),
		OPT_PASSTHRU_ARGV(0, "exclude", &state.git_apply_opts, N_("path"),
			N_("pass it through git-apply"),
			0),
		OPT_PASSTHRU_ARGV(0, "include", &state.git_apply_opts, N_("path"),
			N_("pass it through git-apply"),
			0),
		OPT_PASSTHRU_ARGV('C', NULL, &state.git_apply_opts, N_("n"),
			N_("pass it through git-apply"),
			0),
		OPT_PASSTHRU_ARGV('p', NULL, &state.git_apply_opts, N_("num"),
			N_("pass it through git-apply"),
			0),
		OPT_CALLBACK(0, "patch-format", &patch_format, N_("format"),
			N_("format the patch(es) are in"),
			parse_opt_patchformat),
		OPT_PASSTHRU_ARGV(0, "reject", &state.git_apply_opts, NULL,
			N_("pass it through git-apply"),
			PARSE_OPT_NOARG),
		OPT_STRING(0, "resolvemsg", &state.resolvemsg, NULL,
			N_("override error message when patch failure occurs")),
		OPT_CMDMODE(0, "continue", &resume,
			N_("continue applying patches after resolving a conflict"),
			RESUME_RESOLVED),
		OPT_CMDMODE('r', "resolved", &resume,
			N_("synonyms for --continue"),
			RESUME_RESOLVED),
		OPT_CMDMODE(0, "skip", &resume,
			N_("skip the current patch"),
			RESUME_SKIP),
		OPT_CMDMODE(0, "abort", &resume,
			N_("restore the original branch and abort the patching operation."),
			RESUME_ABORT),
		OPT_CMDMODE(0, "quit", &resume,
			N_("abort the patching operation but keep HEAD where it is."),
			RESUME_QUIT),
		OPT_CMDMODE(0, "show-current-patch", &resume,
			N_("show the patch being applied."),
			RESUME_SHOW_PATCH),
		OPT_BOOL(0, "committer-date-is-author-date",
			&state.committer_date_is_author_date,
			N_("lie about committer date")),
		OPT_BOOL(0, "ignore-date", &state.ignore_date,
			N_("use current timestamp for author date")),
		OPT_RERERE_AUTOUPDATE(&state.allow_rerere_autoupdate),
		{ OPTION_STRING, 'S', "gpg-sign", &state.sign_commit, N_("key-id"),
		  N_("GPG-sign commits"),
		  PARSE_OPT_OPTARG, NULL, (intptr_t) "" },
		OPT_HIDDEN_BOOL(0, "rebasing", &state.rebasing,
			N_("(internal use for git-rebase)")),
		OPT_END()
	};

	if (argc == 2 && !strcmp(argv[1], "-h"))
		usage_with_options(usage, options);

	git_config(git_am_config, NULL);

	am_state_init(&state);

	in_progress = am_in_progress(&state);
	if (in_progress)
		am_load(&state);

	argc = parse_options(argc, argv, prefix, options, usage, 0);

	if (binary >= 0)
		fprintf_ln(stderr, _("The -b/--binary option has been a no-op for long time, and\n"
				"it will be removed. Please do not use it anymore."));

	/* Ensure a valid committer ident can be constructed */
	git_committer_info(IDENT_STRICT);

	if (repo_read_index_preload(the_repository, NULL, 0) < 0)
		die(_("failed to read the index"));

	if (in_progress) {
		/*
		 * Catch user error to feed us patches when there is a session
		 * in progress:
		 *
		 * 1. mbox path(s) are provided on the command-line.
		 * 2. stdin is not a tty: the user is trying to feed us a patch
		 *    from standard input. This is somewhat unreliable -- stdin
		 *    could be /dev/null for example and the caller did not
		 *    intend to feed us a patch but wanted to continue
		 *    unattended.
		 */
		if (argc || (resume == RESUME_FALSE && !isatty(0)))
			die(_("previous rebase directory %s still exists but mbox given."),
				state.dir);

		if (resume == RESUME_FALSE)
			resume = RESUME_APPLY;

		if (state.signoff == SIGNOFF_EXPLICIT)
			am_append_signoff(&state);
	} else {
		struct argv_array paths = ARGV_ARRAY_INIT;
		int i;

		/*
		 * Handle stray state directory in the independent-run case. In
		 * the --rebasing case, it is up to the caller to take care of
		 * stray directories.
		 */
		if (file_exists(state.dir) && !state.rebasing) {
			if (resume == RESUME_ABORT || resume == RESUME_QUIT) {
				am_destroy(&state);
				am_state_release(&state);
				return 0;
			}

			die(_("Stray %s directory found.\n"
				"Use \"git am --abort\" to remove it."),
				state.dir);
		}

		if (resume)
			die(_("Resolve operation not in progress, we are not resuming."));

		for (i = 0; i < argc; i++) {
			if (is_absolute_path(argv[i]) || !prefix)
				argv_array_push(&paths, argv[i]);
			else
				argv_array_push(&paths, mkpath("%s/%s", prefix, argv[i]));
		}

		if (state.interactive && !paths.argc)
			die(_("interactive mode requires patches on the command line"));

		am_setup(&state, patch_format, paths.argv, keep_cr);

		argv_array_clear(&paths);
	}

	switch (resume) {
	case RESUME_FALSE:
		am_run(&state, 0);
		break;
	case RESUME_APPLY:
		am_run(&state, 1);
		break;
	case RESUME_RESOLVED:
		am_resolve(&state);
		break;
	case RESUME_SKIP:
		am_skip(&state);
		break;
	case RESUME_ABORT:
		am_abort(&state);
		break;
	case RESUME_QUIT:
		am_rerere_clear();
		am_destroy(&state);
		break;
	case RESUME_SHOW_PATCH:
		ret = show_patch(&state);
		break;
	default:
		BUG("invalid resume value");
	}

	am_state_release(&state);

	return ret;
}