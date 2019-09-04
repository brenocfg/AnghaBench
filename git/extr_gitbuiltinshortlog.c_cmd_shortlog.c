#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct shortlog {int user_format; scalar_t__ file; int /*<<< orphan*/  abbrev; int /*<<< orphan*/  email; int /*<<< orphan*/  summary; int /*<<< orphan*/  sort_by_number; int /*<<< orphan*/  committer; int /*<<< orphan*/  member_0; } ;
struct TYPE_5__ {scalar_t__ nr; } ;
struct TYPE_4__ {scalar_t__ file; } ;
struct rev_info {scalar_t__ commit_format; TYPE_2__ pending; TYPE_1__ diffopt; int /*<<< orphan*/  abbrev; } ;
struct parse_opt_ctx_t {int dummy; } ;
struct option {char member_1; int /*<<< orphan*/ * member_7; int /*<<< orphan*/  member_6; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; struct shortlog* member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/  member_0; } ;
struct TYPE_6__ {int /*<<< orphan*/  have_repository; } ;

/* Variables and functions */
 scalar_t__ CMIT_FMT_USERFORMAT ; 
 int /*<<< orphan*/  N_ (char*) ; 
 int /*<<< orphan*/  OPTION_CALLBACK ; 
 struct option const OPT_BOOL (char,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct option const OPT_END () ; 
#define  PARSE_OPT_COMPLETE 131 
#define  PARSE_OPT_DONE 130 
#define  PARSE_OPT_ERROR 129 
#define  PARSE_OPT_HELP 128 
 int PARSE_OPT_KEEP_ARGV0 ; 
 int PARSE_OPT_KEEP_DASHDASH ; 
 int /*<<< orphan*/  PARSE_OPT_OPTARG ; 
 int /*<<< orphan*/  STRING_LIST_INIT_NODUP ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  add_head_to_pending (struct rev_info*) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (scalar_t__) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  get_from_rev (struct rev_info*,struct shortlog*) ; 
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_default_config ; 
 scalar_t__ isatty (int /*<<< orphan*/ ) ; 
 int parse_options_end (struct parse_opt_ctx_t*) ; 
 int /*<<< orphan*/  parse_options_start (struct parse_opt_ctx_t*,int,char const**,char const*,struct option const*,int) ; 
 int parse_options_step (struct parse_opt_ctx_t*,struct option const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_revision_opt (struct rev_info*,struct parse_opt_ctx_t*,struct option const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_wrap_args ; 
 int /*<<< orphan*/  read_from_stdin (struct shortlog*) ; 
 int /*<<< orphan*/  repo_init_revisions (int /*<<< orphan*/ ,struct rev_info*,char const*) ; 
 int setup_revisions (int,char const**,struct rev_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shortlog_init (struct shortlog*) ; 
 int /*<<< orphan*/  shortlog_output (struct shortlog*) ; 
 int /*<<< orphan*/  shortlog_usage ; 
 TYPE_3__* startup_info ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ stdout ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  usage_with_options (int /*<<< orphan*/ ,struct option const*) ; 

int cmd_shortlog(int argc, const char **argv, const char *prefix)
{
	struct shortlog log = { STRING_LIST_INIT_NODUP };
	struct rev_info rev;
	int nongit = !startup_info->have_repository;

	const struct option options[] = {
		OPT_BOOL('c', "committer", &log.committer,
			 N_("Group by committer rather than author")),
		OPT_BOOL('n', "numbered", &log.sort_by_number,
			 N_("sort output according to the number of commits per author")),
		OPT_BOOL('s', "summary", &log.summary,
			 N_("Suppress commit descriptions, only provides commit count")),
		OPT_BOOL('e', "email", &log.email,
			 N_("Show the email address of each author")),
		{ OPTION_CALLBACK, 'w', NULL, &log, N_("<w>[,<i1>[,<i2>]]"),
			N_("Linewrap output"), PARSE_OPT_OPTARG,
			&parse_wrap_args },
		OPT_END(),
	};

	struct parse_opt_ctx_t ctx;

	git_config(git_default_config, NULL);
	shortlog_init(&log);
	repo_init_revisions(the_repository, &rev, prefix);
	parse_options_start(&ctx, argc, argv, prefix, options,
			    PARSE_OPT_KEEP_DASHDASH | PARSE_OPT_KEEP_ARGV0);

	for (;;) {
		switch (parse_options_step(&ctx, options, shortlog_usage)) {
		case PARSE_OPT_HELP:
		case PARSE_OPT_ERROR:
			exit(129);
		case PARSE_OPT_COMPLETE:
			exit(0);
		case PARSE_OPT_DONE:
			goto parse_done;
		}
		parse_revision_opt(&rev, &ctx, options, shortlog_usage);
	}
parse_done:
	argc = parse_options_end(&ctx);

	if (nongit && argc > 1) {
		error(_("too many arguments given outside repository"));
		usage_with_options(shortlog_usage, options);
	}

	if (setup_revisions(argc, argv, &rev, NULL) != 1) {
		error(_("unrecognized argument: %s"), argv[1]);
		usage_with_options(shortlog_usage, options);
	}

	log.user_format = rev.commit_format == CMIT_FMT_USERFORMAT;
	log.abbrev = rev.abbrev;
	log.file = rev.diffopt.file;

	/* assume HEAD if from a tty */
	if (!nongit && !rev.pending.nr && isatty(0))
		add_head_to_pending(&rev);
	if (rev.pending.nr == 0) {
		if (isatty(0))
			fprintf(stderr, _("(reading log message from standard input)\n"));
		read_from_stdin(&log);
	}
	else
		get_from_rev(&rev, &log);

	shortlog_output(&log);
	if (log.file != stdout)
		fclose(log.file);
	return 0;
}