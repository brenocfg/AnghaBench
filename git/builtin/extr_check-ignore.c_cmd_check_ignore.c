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
struct dir_struct {int dummy; } ;
typedef  int /*<<< orphan*/  dir ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int check_ignore (struct dir_struct*,char const*,int,char const**) ; 
 int /*<<< orphan*/  check_ignore_options ; 
 int check_ignore_stdin_paths (struct dir_struct*,char const*) ; 
 int /*<<< orphan*/  check_ignore_usage ; 
 int /*<<< orphan*/  clear_directory (struct dir_struct*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_default_config ; 
 int /*<<< orphan*/  maybe_flush_or_die (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (struct dir_struct*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  no_index ; 
 scalar_t__ nul_term_line ; 
 int parse_options (int,char const**,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ quiet ; 
 scalar_t__ read_cache () ; 
 int /*<<< orphan*/  setup_standard_excludes (struct dir_struct*) ; 
 scalar_t__ show_non_matching ; 
 scalar_t__ stdin_paths ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ verbose ; 

int cmd_check_ignore(int argc, const char **argv, const char *prefix)
{
	int num_ignored;
	struct dir_struct dir;

	git_config(git_default_config, NULL);

	argc = parse_options(argc, argv, prefix, check_ignore_options,
			     check_ignore_usage, 0);

	if (stdin_paths) {
		if (argc > 0)
			die(_("cannot specify pathnames with --stdin"));
	} else {
		if (nul_term_line)
			die(_("-z only makes sense with --stdin"));
		if (argc == 0)
			die(_("no path specified"));
	}
	if (quiet) {
		if (argc > 1)
			die(_("--quiet is only valid with a single pathname"));
		if (verbose)
			die(_("cannot have both --quiet and --verbose"));
	}
	if (show_non_matching && !verbose)
		die(_("--non-matching is only valid with --verbose"));

	/* read_cache() is only necessary so we can watch out for submodules. */
	if (!no_index && read_cache() < 0)
		die(_("index file corrupt"));

	memset(&dir, 0, sizeof(dir));
	setup_standard_excludes(&dir);

	if (stdin_paths) {
		num_ignored = check_ignore_stdin_paths(&dir, prefix);
	} else {
		num_ignored = check_ignore(&dir, prefix, argc, argv);
		maybe_flush_or_die(stdout, "ignore to stdout");
	}

	clear_directory(&dir);

	return !num_ignored;
}