#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct option {int dummy; } ;
struct TYPE_3__ {int (* fn ) (int,char const**) ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int BUG_exit_code ; 
 struct option OPT_END () ; 
 struct option OPT_STRING (char,int /*<<< orphan*/ *,char const**,char*,char*) ; 
 int PARSE_OPT_KEEP_ARGV0 ; 
 int PARSE_OPT_STOP_AT_NON_OPTION ; 
 scalar_t__ chdir (char const*) ; 
 TYPE_1__* cmds ; 
 int /*<<< orphan*/  die (char*,char const*) ; 
 int /*<<< orphan*/  die_usage () ; 
 int /*<<< orphan*/  error (char*,char const*) ; 
 int parse_options (int,char const**,int /*<<< orphan*/ *,struct option*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 
 int stub1 (int,char const**) ; 
 int /*<<< orphan*/  test_tool_usage ; 
 int /*<<< orphan*/  trace2_cmd_list_config () ; 
 int /*<<< orphan*/  trace2_cmd_name (int /*<<< orphan*/ ) ; 

int cmd_main(int argc, const char **argv)
{
	int i;
	const char *working_directory = NULL;
	struct option options[] = {
		OPT_STRING('C', NULL, &working_directory, "directory",
			   "change the working directory"),
		OPT_END()
	};

	BUG_exit_code = 99;
	argc = parse_options(argc, argv, NULL, options, test_tool_usage,
			     PARSE_OPT_STOP_AT_NON_OPTION |
			     PARSE_OPT_KEEP_ARGV0);

	if (argc < 2)
		die_usage();

	if (working_directory && chdir(working_directory) < 0)
		die("Could not cd to '%s'", working_directory);

	for (i = 0; i < ARRAY_SIZE(cmds); i++) {
		if (!strcmp(cmds[i].name, argv[1])) {
			argv++;
			argc--;
			trace2_cmd_name(cmds[i].name);
			trace2_cmd_list_config();
			return cmds[i].fn(argc, argv);
		}
	}
	error("there is no tool named '%s'", argv[1]);
	die_usage();
}