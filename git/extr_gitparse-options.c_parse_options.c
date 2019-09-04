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
struct parse_opt_ctx_t {char** argv; char** opt; } ;
struct option {int dummy; } ;

/* Variables and functions */
#define  PARSE_OPT_COMPLETE 132 
#define  PARSE_OPT_DONE 131 
#define  PARSE_OPT_ERROR 130 
#define  PARSE_OPT_HELP 129 
#define  PARSE_OPT_NON_OPTION 128 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  disallow_abbreviated_options ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  git_env_bool (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isascii (char*) ; 
 int parse_options_end (struct parse_opt_ctx_t*) ; 
 int /*<<< orphan*/  parse_options_start (struct parse_opt_ctx_t*,int,char const**,char const*,struct option const*,int) ; 
 int parse_options_step (struct parse_opt_ctx_t*,struct option const*,char const* const*) ; 
 int /*<<< orphan*/  precompose_argv (int,char const**) ; 
 int /*<<< orphan*/  usage_with_options (char const* const*,struct option const*) ; 

int parse_options(int argc, const char **argv, const char *prefix,
		  const struct option *options, const char * const usagestr[],
		  int flags)
{
	struct parse_opt_ctx_t ctx;

	disallow_abbreviated_options =
		git_env_bool("GIT_TEST_DISALLOW_ABBREVIATED_OPTIONS", 0);

	parse_options_start(&ctx, argc, argv, prefix, options, flags);
	switch (parse_options_step(&ctx, options, usagestr)) {
	case PARSE_OPT_HELP:
	case PARSE_OPT_ERROR:
		exit(129);
	case PARSE_OPT_COMPLETE:
		exit(0);
	case PARSE_OPT_NON_OPTION:
	case PARSE_OPT_DONE:
		break;
	default: /* PARSE_OPT_UNKNOWN */
		if (ctx.argv[0][1] == '-') {
			error(_("unknown option `%s'"), ctx.argv[0] + 2);
		} else if (isascii(*ctx.opt)) {
			error(_("unknown switch `%c'"), *ctx.opt);
		} else {
			error(_("unknown non-ascii option in string: `%s'"),
			      ctx.argv[0]);
		}
		usage_with_options(usagestr, options);
	}

	precompose_argv(argc, argv);
	return parse_options_end(&ctx);
}