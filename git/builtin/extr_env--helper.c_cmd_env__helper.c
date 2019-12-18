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
 int /*<<< orphan*/  BUG (char*) ; 
#define  ENV_HELPER_TYPE_BOOL 129 
#define  ENV_HELPER_TYPE_ULONG 128 
 int /*<<< orphan*/  N_ (char*) ; 
 struct option OPT_BOOL (int /*<<< orphan*/ ,char*,int*,int /*<<< orphan*/ ) ; 
 struct option OPT_CALLBACK_F (int /*<<< orphan*/ ,char*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct option OPT_END () ; 
 struct option OPT_STRING (int /*<<< orphan*/ ,char*,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PARSE_OPT_KEEP_UNKNOWN ; 
 int /*<<< orphan*/  PARSE_OPT_NONEG ; 
 int /*<<< orphan*/  _ (char*) ; 
 int cmdmode ; 
 int /*<<< orphan*/  env__helper_usage ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,char const*) ; 
 int git_env_bool (char const*,int) ; 
 unsigned long git_env_ulong (char const*,unsigned long) ; 
 int git_parse_maybe_bool (char const*) ; 
 int /*<<< orphan*/  git_parse_ulong (char const*,unsigned long*) ; 
 int /*<<< orphan*/  option_parse_type ; 
 int parse_options (int,char const**,char const*,struct option*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,unsigned long) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  usage_with_options (int /*<<< orphan*/ ,struct option*) ; 

int cmd_env__helper(int argc, const char **argv, const char *prefix)
{
	int exit_code = 0;
	const char *env_variable = NULL;
	const char *env_default = NULL;
	int ret;
	int ret_int, default_int;
	unsigned long ret_ulong, default_ulong;
	struct option opts[] = {
		OPT_CALLBACK_F(0, "type", &cmdmode, N_("type"),
			       N_("value is given this type"), PARSE_OPT_NONEG,
			       option_parse_type),
		OPT_STRING(0, "default", &env_default, N_("value"),
			   N_("default for git_env_*(...) to fall back on")),
		OPT_BOOL(0, "exit-code", &exit_code,
			 N_("be quiet only use git_env_*() value as exit code")),
		OPT_END(),
	};

	argc = parse_options(argc, argv, prefix, opts, env__helper_usage,
			     PARSE_OPT_KEEP_UNKNOWN);
	if (env_default && !*env_default)
		usage_with_options(env__helper_usage, opts);
	if (!cmdmode)
		usage_with_options(env__helper_usage, opts);
	if (argc != 1)
		usage_with_options(env__helper_usage, opts);
	env_variable = argv[0];

	switch (cmdmode) {
	case ENV_HELPER_TYPE_BOOL:
		if (env_default) {
			default_int = git_parse_maybe_bool(env_default);
			if (default_int == -1) {
				error(_("option `--default' expects a boolean value with `--type=bool`, not `%s`"),
				      env_default);
				usage_with_options(env__helper_usage, opts);
			}
		} else {
			default_int = 0;
		}
		ret_int = git_env_bool(env_variable, default_int);
		if (!exit_code)
			puts(ret_int ? "true" : "false");
		ret = ret_int;
		break;
	case ENV_HELPER_TYPE_ULONG:
		if (env_default) {
			if (!git_parse_ulong(env_default, &default_ulong)) {
				error(_("option `--default' expects an unsigned long value with `--type=ulong`, not `%s`"),
				      env_default);
				usage_with_options(env__helper_usage, opts);
			}
		} else {
			default_ulong = 0;
		}
		ret_ulong = git_env_ulong(env_variable, default_ulong);
		if (!exit_code)
			printf("%lu\n", ret_ulong);
		ret = ret_ulong;
		break;
	default:
		BUG("unknown <type> value");
		break;
	}

	return !ret;
}