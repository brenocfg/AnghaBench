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
struct string_list {int nr; TYPE_1__* items; } ;
struct argv_array {int /*<<< orphan*/  argv; } ;
struct TYPE_2__ {char* string; } ;

/* Variables and functions */
 struct argv_array ARGV_ARRAY_INIT ; 
 int /*<<< orphan*/  RUN_GIT_CMD ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  add_options_to_argv (struct argv_array*) ; 
 int /*<<< orphan*/  append ; 
 int /*<<< orphan*/  argv_array_clear (struct argv_array*) ; 
 int /*<<< orphan*/  argv_array_pop (struct argv_array*) ; 
 int /*<<< orphan*/  argv_array_push (struct argv_array*,char const*) ; 
 int /*<<< orphan*/  argv_array_pushl (struct argv_array*,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dry_run ; 
 int /*<<< orphan*/  error (char*,char const*) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 scalar_t__ run_command_v_opt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int truncate_fetch_head () ; 
 scalar_t__ verbosity ; 

__attribute__((used)) static int fetch_multiple(struct string_list *list)
{
	int i, result = 0;
	struct argv_array argv = ARGV_ARRAY_INIT;

	if (!append && !dry_run) {
		int errcode = truncate_fetch_head();
		if (errcode)
			return errcode;
	}

	argv_array_pushl(&argv, "fetch", "--append", NULL);
	add_options_to_argv(&argv);

	for (i = 0; i < list->nr; i++) {
		const char *name = list->items[i].string;
		argv_array_push(&argv, name);
		if (verbosity >= 0)
			printf(_("Fetching %s\n"), name);
		if (run_command_v_opt(argv.argv, RUN_GIT_CMD)) {
			error(_("Could not fetch %s"), name);
			result = 1;
		}
		argv_array_pop(&argv);
	}

	argv_array_clear(&argv);
	return result;
}