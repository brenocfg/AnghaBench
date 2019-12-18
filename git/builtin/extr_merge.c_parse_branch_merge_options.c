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
 int /*<<< orphan*/  MOVE_ARRAY (char const**,char const**,int) ; 
 int /*<<< orphan*/  REALLOC_ARRAY (char const**,int) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  branch ; 
 int /*<<< orphan*/  builtin_merge_options ; 
 int /*<<< orphan*/  builtin_merge_usage ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char const**) ; 
 int /*<<< orphan*/  parse_options (int,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int split_cmdline (char*,char const***) ; 
 char* split_cmdline_strerror (int) ; 

__attribute__((used)) static void parse_branch_merge_options(char *bmo)
{
	const char **argv;
	int argc;

	if (!bmo)
		return;
	argc = split_cmdline(bmo, &argv);
	if (argc < 0)
		die(_("Bad branch.%s.mergeoptions string: %s"), branch,
		    _(split_cmdline_strerror(argc)));
	REALLOC_ARRAY(argv, argc + 2);
	MOVE_ARRAY(argv + 1, argv, argc + 1);
	argc++;
	argv[0] = "branch.*.mergeoptions";
	parse_options(argc, argv, NULL, builtin_merge_options,
		      builtin_merge_usage, 0);
	free(argv);
}