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

/* Variables and functions */
 char* GIT_HOST_CPU ; 
 char const* N_ (char*) ; 
 struct option OPT_BOOL (int /*<<< orphan*/ ,char*,int*,char*) ; 
 struct option OPT_END () ; 
 char* git_built_from_commit_string ; 
 char* git_version_string ; 
 int parse_options (int,char const**,char const*,struct option*,char const* const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int cmd_version(int argc, const char **argv, const char *prefix)
{
	int build_options = 0;
	const char * const usage[] = {
		N_("git version [<options>]"),
		NULL
	};
	struct option options[] = {
		OPT_BOOL(0, "build-options", &build_options,
			 "also print build options"),
		OPT_END()
	};

	argc = parse_options(argc, argv, prefix, options, usage, 0);

	/*
	 * The format of this string should be kept stable for compatibility
	 * with external projects that rely on the output of "git version".
	 *
	 * Always show the version, even if other options are given.
	 */
	printf("git version %s\n", git_version_string);

	if (build_options) {
		printf("cpu: %s\n", GIT_HOST_CPU);
		if (git_built_from_commit_string[0])
			printf("built from commit: %s\n",
			       git_built_from_commit_string);
		else
			printf("no commit associated with this build\n");
		printf("sizeof-long: %d\n", (int)sizeof(long));
		printf("sizeof-size_t: %d\n", (int)sizeof(size_t));
		/* NEEDSWORK: also save and output GIT-BUILD_OPTIONS? */
	}
	return 0;
}