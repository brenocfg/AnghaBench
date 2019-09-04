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
struct option {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPG_VERIFY_RAW ; 
 unsigned int GPG_VERIFY_VERBOSE ; 
 int /*<<< orphan*/  N_ (char*) ; 
 struct option const OPT_BIT (int /*<<< orphan*/ ,char*,unsigned int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct option const OPT_END () ; 
 struct option const OPT__VERBOSE (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PARSE_OPT_KEEP_ARGV0 ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_verify_commit_config ; 
 int parse_options (int,char const**,char const*,struct option const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage_with_options (int /*<<< orphan*/ ,struct option const*) ; 
 scalar_t__ verify_commit (char const*,unsigned int) ; 
 int /*<<< orphan*/  verify_commit_usage ; 

int cmd_verify_commit(int argc, const char **argv, const char *prefix)
{
	int i = 1, verbose = 0, had_error = 0;
	unsigned flags = 0;
	const struct option verify_commit_options[] = {
		OPT__VERBOSE(&verbose, N_("print commit contents")),
		OPT_BIT(0, "raw", &flags, N_("print raw gpg status output"), GPG_VERIFY_RAW),
		OPT_END()
	};

	git_config(git_verify_commit_config, NULL);

	argc = parse_options(argc, argv, prefix, verify_commit_options,
			     verify_commit_usage, PARSE_OPT_KEEP_ARGV0);
	if (argc <= i)
		usage_with_options(verify_commit_usage, verify_commit_options);

	if (verbose)
		flags |= GPG_VERIFY_VERBOSE;

	/* sometimes the program was terminated because this signal
	 * was received in the process of writing the gpg input: */
	signal(SIGPIPE, SIG_IGN);
	while (i < argc)
		if (verify_commit(argv[i++], flags))
			had_error = 1;
	return had_error;
}