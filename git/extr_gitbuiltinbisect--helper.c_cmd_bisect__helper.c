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
struct bisect_terms {int /*<<< orphan*/ * term_bad; int /*<<< orphan*/ * term_good; } ;

/* Variables and functions */
 int /*<<< orphan*/  N_ (char*) ; 
 struct option OPT_BOOL (int /*<<< orphan*/ ,char*,int*,int /*<<< orphan*/ ) ; 
 struct option OPT_CMDMODE (int /*<<< orphan*/ ,char*,int*,int /*<<< orphan*/ ,int) ; 
 struct option OPT_END () ; 
 int PARSE_OPT_KEEP_DASHDASH ; 
 int PARSE_OPT_KEEP_UNKNOWN ; 
 int /*<<< orphan*/  _ (char*) ; 
 int bisect_clean_state () ; 
 int bisect_next_all (int /*<<< orphan*/ ,char const*,int) ; 
 int bisect_next_check (struct bisect_terms*,char const*) ; 
 int /*<<< orphan*/  bisect_reset (char const*) ; 
 int bisect_start (struct bisect_terms*,int,char const**,int) ; 
 int bisect_terms (struct bisect_terms*,char const*) ; 
 int bisect_write (char const*,char const*,struct bisect_terms*,int) ; 
 int check_and_set_terms (struct bisect_terms*,char const*) ; 
 int /*<<< orphan*/  check_expected_revs (char const**,int) ; 
 int error (char*,...) ; 
 int /*<<< orphan*/  free_terms (struct bisect_terms*) ; 
 int /*<<< orphan*/  git_bisect_helper_usage ; 
 int parse_options (int,char const**,char const*,struct option*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_terms (struct bisect_terms*,char const*,char const*) ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  usage_with_options (int /*<<< orphan*/ ,struct option*) ; 
 int write_terms (char const*,char const*) ; 

int cmd_bisect__helper(int argc, const char **argv, const char *prefix)
{
	enum {
		NEXT_ALL = 1,
		WRITE_TERMS,
		BISECT_CLEAN_STATE,
		CHECK_EXPECTED_REVS,
		BISECT_RESET,
		BISECT_WRITE,
		CHECK_AND_SET_TERMS,
		BISECT_NEXT_CHECK,
		BISECT_TERMS,
		BISECT_START
	} cmdmode = 0;
	int no_checkout = 0, res = 0, nolog = 0;
	struct option options[] = {
		OPT_CMDMODE(0, "next-all", &cmdmode,
			 N_("perform 'git bisect next'"), NEXT_ALL),
		OPT_CMDMODE(0, "write-terms", &cmdmode,
			 N_("write the terms to .git/BISECT_TERMS"), WRITE_TERMS),
		OPT_CMDMODE(0, "bisect-clean-state", &cmdmode,
			 N_("cleanup the bisection state"), BISECT_CLEAN_STATE),
		OPT_CMDMODE(0, "check-expected-revs", &cmdmode,
			 N_("check for expected revs"), CHECK_EXPECTED_REVS),
		OPT_CMDMODE(0, "bisect-reset", &cmdmode,
			 N_("reset the bisection state"), BISECT_RESET),
		OPT_CMDMODE(0, "bisect-write", &cmdmode,
			 N_("write out the bisection state in BISECT_LOG"), BISECT_WRITE),
		OPT_CMDMODE(0, "check-and-set-terms", &cmdmode,
			 N_("check and set terms in a bisection state"), CHECK_AND_SET_TERMS),
		OPT_CMDMODE(0, "bisect-next-check", &cmdmode,
			 N_("check whether bad or good terms exist"), BISECT_NEXT_CHECK),
		OPT_CMDMODE(0, "bisect-terms", &cmdmode,
			 N_("print out the bisect terms"), BISECT_TERMS),
		OPT_CMDMODE(0, "bisect-start", &cmdmode,
			 N_("start the bisect session"), BISECT_START),
		OPT_BOOL(0, "no-checkout", &no_checkout,
			 N_("update BISECT_HEAD instead of checking out the current commit")),
		OPT_BOOL(0, "no-log", &nolog,
			 N_("no log for BISECT_WRITE")),
		OPT_END()
	};
	struct bisect_terms terms = { .term_good = NULL, .term_bad = NULL };

	argc = parse_options(argc, argv, prefix, options,
			     git_bisect_helper_usage,
			     PARSE_OPT_KEEP_DASHDASH | PARSE_OPT_KEEP_UNKNOWN);

	if (!cmdmode)
		usage_with_options(git_bisect_helper_usage, options);

	switch (cmdmode) {
	case NEXT_ALL:
		return bisect_next_all(the_repository, prefix, no_checkout);
	case WRITE_TERMS:
		if (argc != 2)
			return error(_("--write-terms requires two arguments"));
		return write_terms(argv[0], argv[1]);
	case BISECT_CLEAN_STATE:
		if (argc != 0)
			return error(_("--bisect-clean-state requires no arguments"));
		return bisect_clean_state();
	case CHECK_EXPECTED_REVS:
		check_expected_revs(argv, argc);
		return 0;
	case BISECT_RESET:
		if (argc > 1)
			return error(_("--bisect-reset requires either no argument or a commit"));
		return !!bisect_reset(argc ? argv[0] : NULL);
	case BISECT_WRITE:
		if (argc != 4 && argc != 5)
			return error(_("--bisect-write requires either 4 or 5 arguments"));
		set_terms(&terms, argv[3], argv[2]);
		res = bisect_write(argv[0], argv[1], &terms, nolog);
		break;
	case CHECK_AND_SET_TERMS:
		if (argc != 3)
			return error(_("--check-and-set-terms requires 3 arguments"));
		set_terms(&terms, argv[2], argv[1]);
		res = check_and_set_terms(&terms, argv[0]);
		break;
	case BISECT_NEXT_CHECK:
		if (argc != 2 && argc != 3)
			return error(_("--bisect-next-check requires 2 or 3 arguments"));
		set_terms(&terms, argv[1], argv[0]);
		res = bisect_next_check(&terms, argc == 3 ? argv[2] : NULL);
		break;
	case BISECT_TERMS:
		if (argc > 1)
			return error(_("--bisect-terms requires 0 or 1 argument"));
		res = bisect_terms(&terms, argc == 1 ? argv[0] : NULL);
		break;
	case BISECT_START:
		set_terms(&terms, "bad", "good");
		res = bisect_start(&terms, no_checkout, argv, argc);
		break;
	default:
		return error("BUG: unknown subcommand '%d'", cmdmode);
	}
	free_terms(&terms);
	return !!res;
}