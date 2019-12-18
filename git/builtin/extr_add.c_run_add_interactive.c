#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pathspec {int nr; TYPE_1__* items; } ;
struct argv_array {int /*<<< orphan*/  argv; } ;
struct TYPE_2__ {char* original; } ;

/* Variables and functions */
 struct argv_array ARGV_ARRAY_INIT ; 
 int /*<<< orphan*/  RUN_GIT_CMD ; 
 int /*<<< orphan*/  argv_array_clear (struct argv_array*) ; 
 int /*<<< orphan*/  argv_array_push (struct argv_array*,char const*) ; 
 int run_command_v_opt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int run_add_interactive(const char *revision, const char *patch_mode,
			const struct pathspec *pathspec)
{
	int status, i;
	struct argv_array argv = ARGV_ARRAY_INIT;

	argv_array_push(&argv, "add--interactive");
	if (patch_mode)
		argv_array_push(&argv, patch_mode);
	if (revision)
		argv_array_push(&argv, revision);
	argv_array_push(&argv, "--");
	for (i = 0; i < pathspec->nr; i++)
		/* pass original pathspec, to be re-parsed */
		argv_array_push(&argv, pathspec->items[i].original);

	status = run_command_v_opt(argv.argv, RUN_GIT_CMD);
	argv_array_clear(&argv);
	return status;
}