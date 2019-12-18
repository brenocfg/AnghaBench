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
 int /*<<< orphan*/  builtin_merge_ours_usage ; 
 int /*<<< orphan*/  die_errno (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ index_differs_from (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ read_cache () ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 

int cmd_merge_ours(int argc, const char **argv, const char *prefix)
{
	if (argc == 2 && !strcmp(argv[1], "-h"))
		usage(builtin_merge_ours_usage);

	/*
	 * The contents of the current index becomes the tree we
	 * commit.  The index must match HEAD, or this merge cannot go
	 * through.
	 */
	if (read_cache() < 0)
		die_errno("read_cache failed");
	if (index_differs_from(the_repository, "HEAD", NULL, 0))
		exit(2);
	exit(0);
}