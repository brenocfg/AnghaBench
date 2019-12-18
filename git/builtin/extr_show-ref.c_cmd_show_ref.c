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
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*,...) ; 
 scalar_t__ exclude_arg ; 
 int exclude_existing (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exclude_existing_arg ; 
 int /*<<< orphan*/  for_each_ref (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  found_match ; 
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_default_config ; 
 int /*<<< orphan*/  head_ref (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int parse_options (int,char const**,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char const** pattern ; 
 int /*<<< orphan*/  quiet ; 
 int /*<<< orphan*/  read_ref (char const*,struct object_id*) ; 
 scalar_t__ show_head ; 
 int /*<<< orphan*/  show_one (char const*,struct object_id*) ; 
 int /*<<< orphan*/  show_ref ; 
 int /*<<< orphan*/  show_ref_options ; 
 int /*<<< orphan*/  show_ref_usage ; 
 scalar_t__ starts_with (char const*,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 scalar_t__ verify ; 

int cmd_show_ref(int argc, const char **argv, const char *prefix)
{
	git_config(git_default_config, NULL);

	argc = parse_options(argc, argv, prefix, show_ref_options,
			     show_ref_usage, 0);

	if (exclude_arg)
		return exclude_existing(exclude_existing_arg);

	pattern = argv;
	if (!*pattern)
		pattern = NULL;

	if (verify) {
		if (!pattern)
			die("--verify requires a reference");
		while (*pattern) {
			struct object_id oid;

			if ((starts_with(*pattern, "refs/") || !strcmp(*pattern, "HEAD")) &&
			    !read_ref(*pattern, &oid)) {
				show_one(*pattern, &oid);
			}
			else if (!quiet)
				die("'%s' - not a valid ref", *pattern);
			else
				return 1;
			pattern++;
		}
		return 0;
	}

	if (show_head)
		head_ref(show_ref, NULL);
	for_each_ref(show_ref, NULL);
	if (!found_match) {
		if (verify && !quiet)
			die("No match");
		return 1;
	}
	return 0;
}