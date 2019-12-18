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
 int /*<<< orphan*/  generate_id_list (int) ; 
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  git_patch_id_config ; 
 int /*<<< orphan*/  patch_id_usage ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 

int cmd_patch_id(int argc, const char **argv, const char *prefix)
{
	int stable = -1;

	git_config(git_patch_id_config, &stable);

	/* If nothing is set, default to unstable. */
	if (stable < 0)
		stable = 0;

	if (argc == 2 && !strcmp(argv[1], "--stable"))
		stable = 1;
	else if (argc == 2 && !strcmp(argv[1], "--unstable"))
		stable = 0;
	else if (argc != 1)
		usage(patch_id_usage);

	generate_id_list(stable);
	return 0;
}