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
struct TYPE_2__ {int recursive; } ;
struct archiver_args {TYPE_1__ pathspec; } ;

/* Variables and functions */
 int /*<<< orphan*/  PATHSPEC_PREFER_FULL ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  parse_pathspec (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const**) ; 
 int /*<<< orphan*/  path_exists (struct archiver_args*,char const*) ; 

__attribute__((used)) static void parse_pathspec_arg(const char **pathspec,
		struct archiver_args *ar_args)
{
	/*
	 * must be consistent with parse_pathspec in path_exists()
	 * Also if pathspec patterns are dependent, we're in big
	 * trouble as we test each one separately
	 */
	parse_pathspec(&ar_args->pathspec, 0,
		       PATHSPEC_PREFER_FULL,
		       "", pathspec);
	ar_args->pathspec.recursive = 1;
	if (pathspec) {
		while (*pathspec) {
			if (**pathspec && !path_exists(ar_args, *pathspec))
				die(_("pathspec '%s' did not match any files"), *pathspec);
			pathspec++;
		}
	}
}