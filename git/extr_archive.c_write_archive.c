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
struct repository {int dummy; } ;
struct archiver_args {struct repository* repo; } ;
struct archiver {int (* write_archive ) (struct archiver const*,struct archiver_args*) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  have_repository; } ;

/* Variables and functions */
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_bool (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_default_config ; 
 int parse_archive_args (int,char const**,struct archiver const**,struct archiver_args*,char const*,int) ; 
 int /*<<< orphan*/  parse_pathspec_arg (char const**,struct archiver_args*) ; 
 int /*<<< orphan*/  parse_treeish_arg (char const**,struct archiver_args*,char const*,int) ; 
 int /*<<< orphan*/  remote_allow_unreachable ; 
 int /*<<< orphan*/  setup_git_directory () ; 
 TYPE_1__* startup_info ; 
 int stub1 (struct archiver const*,struct archiver_args*) ; 

int write_archive(int argc, const char **argv, const char *prefix,
		  struct repository *repo,
		  const char *name_hint, int remote)
{
	const struct archiver *ar = NULL;
	struct archiver_args args;

	git_config_get_bool("uploadarchive.allowunreachable", &remote_allow_unreachable);
	git_config(git_default_config, NULL);

	args.repo = repo;
	argc = parse_archive_args(argc, argv, &ar, &args, name_hint, remote);
	if (!startup_info->have_repository) {
		/*
		 * We know this will die() with an error, so we could just
		 * die ourselves; but its error message will be more specific
		 * than what we could write here.
		 */
		setup_git_directory();
	}

	parse_treeish_arg(argv, &args, prefix, remote);
	parse_pathspec_arg(argv + 1, &args);

	return ar->write_archive(ar, &args);
}