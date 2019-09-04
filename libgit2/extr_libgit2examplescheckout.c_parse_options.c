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
struct args_info {int argc; int pos; char** argv; } ;
struct TYPE_4__ {int progress; int force; int perf; } ;
typedef  TYPE_1__ checkout_options ;

/* Variables and functions */
 scalar_t__ match_bool_arg (int*,struct args_info*,char*) ; 
 scalar_t__ match_str_arg (char const**,struct args_info*,char*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  print_usage () ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static void parse_options(const char **repo_path, checkout_options *opts, struct args_info *args)
{
	if (args->argc <= 1)
		print_usage();

	memset(opts, 0, sizeof(*opts));

	/* Default values */
	opts->progress = 1;

	for (args->pos = 1; args->pos < args->argc; ++args->pos) {
		const char *curr = args->argv[args->pos];
		int bool_arg;

		if (strcmp(curr, "--") == 0) {
			break;
		} else if (!strcmp(curr, "--force")) {
			opts->force = 1;
		} else if (match_bool_arg(&bool_arg, args, "--progress")) {
			opts->progress = bool_arg;
		} else if (match_bool_arg(&bool_arg, args, "--perf")) {
			opts->perf = bool_arg;
		} else if (match_str_arg(repo_path, args, "--git-dir")) {
			continue;
		} else {
			break;
		}
	}
}