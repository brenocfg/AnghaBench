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

/* Variables and functions */
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_default_config ; 
 int /*<<< orphan*/  list_vars () ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 char* read_var (char const*) ; 
 int /*<<< orphan*/  show_config ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_usage ; 

int cmd_var(int argc, const char **argv, const char *prefix)
{
	const char *val = NULL;
	if (argc != 2)
		usage(var_usage);

	if (strcmp(argv[1], "-l") == 0) {
		git_config(show_config, NULL);
		list_vars();
		return 0;
	}
	git_config(git_default_config, NULL);
	val = read_var(argv[1]);
	if (!val)
		usage(var_usage);

	printf("%s\n", val);

	return 0;
}