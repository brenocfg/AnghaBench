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
struct TYPE_2__ {int flags; int /*<<< orphan*/  show; } ;
struct opts {char* member_1; scalar_t__ format; scalar_t__ repeat; int /*<<< orphan*/ * repodir; scalar_t__ showsubmod; scalar_t__ showbranch; TYPE_1__ statusopt; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  git_status_list ;
typedef  int /*<<< orphan*/  git_repository ;

/* Variables and functions */
 scalar_t__ FORMAT_LONG ; 
 int /*<<< orphan*/  GIT_STATUS_OPTIONS_INIT ; 
 int GIT_STATUS_OPT_INCLUDE_UNTRACKED ; 
 int GIT_STATUS_OPT_RENAMES_HEAD_TO_INDEX ; 
 int GIT_STATUS_OPT_SORT_CASE_SENSITIVELY ; 
 int /*<<< orphan*/  GIT_STATUS_SHOW_INDEX_AND_WORKDIR ; 
 int /*<<< orphan*/  check_lg2 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fatal (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ git_repository_is_bare (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_status_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_status_list_new (int /*<<< orphan*/ **,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_submodule_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  parse_opts (struct opts*,int,char**) ; 
 int /*<<< orphan*/  print_long (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_short (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_submod ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  show_branch (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  sleep (scalar_t__) ; 

int lg2_status(git_repository *repo, int argc, char *argv[])
{
	git_status_list *status;
	struct opts o = { GIT_STATUS_OPTIONS_INIT, "." };

	o.statusopt.show  = GIT_STATUS_SHOW_INDEX_AND_WORKDIR;
	o.statusopt.flags = GIT_STATUS_OPT_INCLUDE_UNTRACKED |
		GIT_STATUS_OPT_RENAMES_HEAD_TO_INDEX |
		GIT_STATUS_OPT_SORT_CASE_SENSITIVELY;

	parse_opts(&o, argc, argv);

	if (git_repository_is_bare(repo))
		fatal("Cannot report status on bare repository",
			git_repository_path(repo));

show_status:
	if (o.repeat)
		printf("\033[H\033[2J");

	/**
	 * Run status on the repository
	 *
	 * We use `git_status_list_new()` to generate a list of status
	 * information which lets us iterate over it at our
	 * convenience and extract the data we want to show out of
	 * each entry.
	 *
	 * You can use `git_status_foreach()` or
	 * `git_status_foreach_ext()` if you'd prefer to execute a
	 * callback for each entry. The latter gives you more control
	 * about what results are presented.
	 */
	check_lg2(git_status_list_new(&status, repo, &o.statusopt),
		"Could not get status", NULL);

	if (o.showbranch)
		show_branch(repo, o.format);

	if (o.showsubmod) {
		int submod_count = 0;
		check_lg2(git_submodule_foreach(repo, print_submod, &submod_count),
			"Cannot iterate submodules", o.repodir);
	}

	if (o.format == FORMAT_LONG)
		print_long(status);
	else
		print_short(repo, status);

	git_status_list_free(status);

	if (o.repeat) {
		sleep(o.repeat);
		goto show_status;
	}

	return 0;
}