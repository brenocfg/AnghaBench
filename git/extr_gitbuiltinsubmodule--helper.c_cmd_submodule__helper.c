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
struct TYPE_3__ {char* cmd; int option; int (* fn ) (int,char const**,char const*) ;} ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int SUPPORT_SUPER_PREFIX ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_1__* commands ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ get_super_prefix () ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int stub1 (int,char const**,char const*) ; 
 int /*<<< orphan*/  usage (char*) ; 

int cmd_submodule__helper(int argc, const char **argv, const char *prefix)
{
	int i;
	if (argc < 2 || !strcmp(argv[1], "-h"))
		usage("git submodule--helper <command>");

	for (i = 0; i < ARRAY_SIZE(commands); i++) {
		if (!strcmp(argv[1], commands[i].cmd)) {
			if (get_super_prefix() &&
			    !(commands[i].option & SUPPORT_SUPER_PREFIX))
				die(_("%s doesn't support --super-prefix"),
				    commands[i].cmd);
			return commands[i].fn(argc - 1, argv + 1, prefix);
		}
	}

	die(_("'%s' is not a valid submodule--helper "
	      "subcommand"), argv[1]);
}