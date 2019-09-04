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
struct submodule_update_strategy {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  SM_UPDATE_CHECKOUT ; 
 int /*<<< orphan*/  determine_submodule_update_strategy (int /*<<< orphan*/ ,int,char const*,char const*,struct submodule_update_strategy*) ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int git_config_int (char*,char const*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  submodule_strategy_to_string (struct submodule_update_strategy*) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static int module_update_module_mode(int argc, const char **argv, const char *prefix)
{
	const char *path, *update = NULL;
	int just_cloned;
	struct submodule_update_strategy update_strategy = { .type = SM_UPDATE_CHECKOUT };

	if (argc < 3 || argc > 4)
		die("submodule--helper update-module-clone expects <just-cloned> <path> [<update>]");

	just_cloned = git_config_int("just_cloned", argv[1]);
	path = argv[2];

	if (argc == 4)
		update = argv[3];

	determine_submodule_update_strategy(the_repository,
					    just_cloned, path, update,
					    &update_strategy);
	fputs(submodule_strategy_to_string(&update_strategy), stdout);

	return 0;
}