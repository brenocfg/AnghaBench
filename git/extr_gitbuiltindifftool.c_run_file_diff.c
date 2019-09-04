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
struct argv_array {int /*<<< orphan*/  argv; } ;

/* Variables and functions */
 struct argv_array ARGV_ARRAY_INIT ; 
 int /*<<< orphan*/  RUN_GIT_CMD ; 
 int /*<<< orphan*/  argv_array_push (struct argv_array*,char const*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int run_command_v_opt_cd_env (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char const**) ; 

__attribute__((used)) static int run_file_diff(int prompt, const char *prefix,
			 int argc, const char **argv)
{
	struct argv_array args = ARGV_ARRAY_INIT;
	const char *env[] = {
		"GIT_PAGER=", "GIT_EXTERNAL_DIFF=git-difftool--helper", NULL,
		NULL
	};
	int ret = 0, i;

	if (prompt > 0)
		env[2] = "GIT_DIFFTOOL_PROMPT=true";
	else if (!prompt)
		env[2] = "GIT_DIFFTOOL_NO_PROMPT=true";


	argv_array_push(&args, "diff");
	for (i = 0; i < argc; i++)
		argv_array_push(&args, argv[i]);
	ret = run_command_v_opt_cd_env(args.argv, RUN_GIT_CMD, prefix, env);
	exit(ret);
}