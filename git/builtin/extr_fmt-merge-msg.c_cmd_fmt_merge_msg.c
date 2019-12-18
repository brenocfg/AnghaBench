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
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct option {char* member_2; int* member_3; int member_6; int /*<<< orphan*/  member_8; int /*<<< orphan*/ * member_7; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct fmt_merge_msg_opts {int add_title; int credit_people; int shortlog_len; } ;
typedef  int /*<<< orphan*/  opts ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_MERGE_LOG_LEN ; 
 int /*<<< orphan*/  N_ (char*) ; 
 int /*<<< orphan*/  OPTION_INTEGER ; 
 struct option OPT_END () ; 
 struct option OPT_FILENAME (float,char*,char const**,int /*<<< orphan*/ ) ; 
 struct option OPT_STRING (char,char*,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PARSE_OPT_HIDDEN ; 
 int PARSE_OPT_OPTARG ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  die_errno (char*,...) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int fmt_merge_msg (struct strbuf*,struct strbuf*,struct fmt_merge_msg_opts*) ; 
 int /*<<< orphan*/  fmt_merge_msg_config ; 
 int /*<<< orphan*/  fmt_merge_msg_usage ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct fmt_merge_msg_opts*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ merge_log_config ; 
 int parse_options (int,char const**,char const*,struct option*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 scalar_t__ strbuf_read (struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  usage_with_options (int /*<<< orphan*/ ,struct option*) ; 
 int /*<<< orphan*/  write_in_full (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int cmd_fmt_merge_msg(int argc, const char **argv, const char *prefix)
{
	const char *inpath = NULL;
	const char *message = NULL;
	int shortlog_len = -1;
	struct option options[] = {
		{ OPTION_INTEGER, 0, "log", &shortlog_len, N_("n"),
		  N_("populate log with at most <n> entries from shortlog"),
		  PARSE_OPT_OPTARG, NULL, DEFAULT_MERGE_LOG_LEN },
		{ OPTION_INTEGER, 0, "summary", &shortlog_len, N_("n"),
		  N_("alias for --log (deprecated)"),
		  PARSE_OPT_OPTARG | PARSE_OPT_HIDDEN, NULL,
		  DEFAULT_MERGE_LOG_LEN },
		OPT_STRING('m', "message", &message, N_("text"),
			N_("use <text> as start of message")),
		OPT_FILENAME('F', "file", &inpath, N_("file to read from")),
		OPT_END()
	};

	FILE *in = stdin;
	struct strbuf input = STRBUF_INIT, output = STRBUF_INIT;
	int ret;
	struct fmt_merge_msg_opts opts;

	git_config(fmt_merge_msg_config, NULL);
	argc = parse_options(argc, argv, prefix, options, fmt_merge_msg_usage,
			     0);
	if (argc > 0)
		usage_with_options(fmt_merge_msg_usage, options);
	if (shortlog_len < 0)
		shortlog_len = (merge_log_config > 0) ? merge_log_config : 0;

	if (inpath && strcmp(inpath, "-")) {
		in = fopen(inpath, "r");
		if (!in)
			die_errno("cannot open '%s'", inpath);
	}

	if (strbuf_read(&input, fileno(in), 0) < 0)
		die_errno("could not read input file");

	if (message)
		strbuf_addstr(&output, message);

	memset(&opts, 0, sizeof(opts));
	opts.add_title = !message;
	opts.credit_people = 1;
	opts.shortlog_len = shortlog_len;

	ret = fmt_merge_msg(&input, &output, &opts);
	if (ret)
		return ret;
	write_in_full(STDOUT_FILENO, output.buf, output.len);
	return 0;
}