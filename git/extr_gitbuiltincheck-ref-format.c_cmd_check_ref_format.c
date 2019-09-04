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
 int REFNAME_ALLOW_ONELEVEL ; 
 int REFNAME_REFSPEC_PATTERN ; 
 int /*<<< orphan*/  builtin_check_ref_format_usage ; 
 int check_ref_format_branch (char const*) ; 
 scalar_t__ check_refname_format (char const*,int) ; 
 char* collapse_slashes (char const*) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 

int cmd_check_ref_format(int argc, const char **argv, const char *prefix)
{
	int i;
	int normalize = 0;
	int flags = 0;
	const char *refname;

	if (argc == 2 && !strcmp(argv[1], "-h"))
		usage(builtin_check_ref_format_usage);

	if (argc == 3 && !strcmp(argv[1], "--branch"))
		return check_ref_format_branch(argv[2]);

	for (i = 1; i < argc && argv[i][0] == '-'; i++) {
		if (!strcmp(argv[i], "--normalize") || !strcmp(argv[i], "--print"))
			normalize = 1;
		else if (!strcmp(argv[i], "--allow-onelevel"))
			flags |= REFNAME_ALLOW_ONELEVEL;
		else if (!strcmp(argv[i], "--no-allow-onelevel"))
			flags &= ~REFNAME_ALLOW_ONELEVEL;
		else if (!strcmp(argv[i], "--refspec-pattern"))
			flags |= REFNAME_REFSPEC_PATTERN;
		else
			usage(builtin_check_ref_format_usage);
	}
	if (! (i == argc - 1))
		usage(builtin_check_ref_format_usage);

	refname = argv[i];
	if (normalize)
		refname = collapse_slashes(refname);
	if (check_refname_format(refname, flags))
		return 1;
	if (normalize)
		printf("%s\n", refname);

	return 0;
}