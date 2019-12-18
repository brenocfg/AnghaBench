#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct args_info {int pos; } ;
struct TYPE_4__ {int no_commit; } ;
typedef  TYPE_1__ merge_options ;

/* Variables and functions */
 struct args_info ARGS_INFO_INIT ; 
 scalar_t__ match_str_arg (char const**,struct args_info*,char*) ; 
 int /*<<< orphan*/  opts_add_refish (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  print_usage () ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static void parse_options(const char **repo_path, merge_options *opts, int argc, char **argv)
{
	struct args_info args = ARGS_INFO_INIT;

	if (argc <= 1)
		print_usage();

	for (args.pos = 1; args.pos < argc; ++args.pos) {
		const char *curr = argv[args.pos];

		if (curr[0] != '-') {
			opts_add_refish(opts, curr);
		} else if (!strcmp(curr, "--no-commit")) {
			opts->no_commit = 1;
		} else if (match_str_arg(repo_path, &args, "--git-dir")) {
			continue;
		} else {
			print_usage();
		}
	}
}