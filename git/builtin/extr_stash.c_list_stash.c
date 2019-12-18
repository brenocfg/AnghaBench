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
struct child_process {int git_cmd; int /*<<< orphan*/  args; } ;

/* Variables and functions */
 struct child_process CHILD_PROCESS_INIT ; 
 struct option OPT_END () ; 
 int /*<<< orphan*/  PARSE_OPT_KEEP_UNKNOWN ; 
 int /*<<< orphan*/  argv_array_push (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  argv_array_pushl (int /*<<< orphan*/ *,char*,char*,char*,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  argv_array_pushv (int /*<<< orphan*/ *,char const**) ; 
 int /*<<< orphan*/  git_stash_list_usage ; 
 int parse_options (int,char const**,char const*,struct option*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ref_exists (char*) ; 
 char* ref_stash ; 
 int run_command (struct child_process*) ; 

__attribute__((used)) static int list_stash(int argc, const char **argv, const char *prefix)
{
	struct child_process cp = CHILD_PROCESS_INIT;
	struct option options[] = {
		OPT_END()
	};

	argc = parse_options(argc, argv, prefix, options,
			     git_stash_list_usage,
			     PARSE_OPT_KEEP_UNKNOWN);

	if (!ref_exists(ref_stash))
		return 0;

	cp.git_cmd = 1;
	argv_array_pushl(&cp.args, "log", "--format=%gd: %gs", "-g",
			 "--first-parent", "-m", NULL);
	argv_array_pushv(&cp.args, argv);
	argv_array_push(&cp.args, ref_stash);
	argv_array_push(&cp.args, "--");
	return run_command(&cp);
}