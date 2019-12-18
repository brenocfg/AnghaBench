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
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  die (char*,...) ; 
 int err ; 
 int /*<<< orphan*/  merge_all () ; 
 int /*<<< orphan*/  merge_one_path (char const*) ; 
 int one_shot ; 
 char const* pgm ; 
 int quiet ; 
 int /*<<< orphan*/  read_cache () ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  usage (char*) ; 

int cmd_merge_index(int argc, const char **argv, const char *prefix)
{
	int i, force_file = 0;

	/* Without this we cannot rely on waitpid() to tell
	 * what happened to our children.
	 */
	signal(SIGCHLD, SIG_DFL);

	if (argc < 3)
		usage("git merge-index [-o] [-q] <merge-program> (-a | [--] [<filename>...])");

	read_cache();

	i = 1;
	if (!strcmp(argv[i], "-o")) {
		one_shot = 1;
		i++;
	}
	if (!strcmp(argv[i], "-q")) {
		quiet = 1;
		i++;
	}
	pgm = argv[i++];
	for (; i < argc; i++) {
		const char *arg = argv[i];
		if (!force_file && *arg == '-') {
			if (!strcmp(arg, "--")) {
				force_file = 1;
				continue;
			}
			if (!strcmp(arg, "-a")) {
				merge_all();
				continue;
			}
			die("git merge-index: unknown option %s", arg);
		}
		merge_one_path(arg);
	}
	if (err && !quiet)
		die("merge program failed");
	return err;
}