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
struct opts {int member_0; char* dir; char* gitdir; scalar_t__ shared; scalar_t__ initial_commit; scalar_t__ bare; int /*<<< orphan*/  quiet; scalar_t__ template; scalar_t__ no_options; int /*<<< orphan*/  member_7; int /*<<< orphan*/  member_6; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; } ;
struct TYPE_4__ {char* workdir_path; scalar_t__ mode; scalar_t__ template_path; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ git_repository_init_options ;
typedef  int /*<<< orphan*/  git_repository ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_REPOSITORY_INIT_BARE ; 
 int /*<<< orphan*/  GIT_REPOSITORY_INIT_EXTERNAL_TEMPLATE ; 
 int /*<<< orphan*/  GIT_REPOSITORY_INIT_MKPATH ; 
 TYPE_1__ GIT_REPOSITORY_INIT_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_REPOSITORY_INIT_SHARED_UMASK ; 
 int /*<<< orphan*/  check_lg2 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  create_initial_commit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_init_ext (int /*<<< orphan*/ **,char*,TYPE_1__*) ; 
 char* git_repository_path (int /*<<< orphan*/ *) ; 
 char* git_repository_workdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_opts (struct opts*,int,char**) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int lg2_init(git_repository *repo, int argc, char *argv[])
{
	struct opts o = { 1, 0, 0, 0, GIT_REPOSITORY_INIT_SHARED_UMASK, 0, 0, 0 };

	parse_opts(&o, argc, argv);

	/* Initialize repository. */

	if (o.no_options) {
		/**
		 * No options were specified, so let's demonstrate the default
		 * simple case of git_repository_init() API usage...
		 */
		check_lg2(git_repository_init(&repo, o.dir, 0),
			"Could not initialize repository", NULL);
	}
	else {
		/**
		 * Some command line options were specified, so we'll use the
		 * extended init API to handle them
		 */
		git_repository_init_options initopts = GIT_REPOSITORY_INIT_OPTIONS_INIT;
		initopts.flags = GIT_REPOSITORY_INIT_MKPATH;

		if (o.bare)
			initopts.flags |= GIT_REPOSITORY_INIT_BARE;

		if (o.template) {
			initopts.flags |= GIT_REPOSITORY_INIT_EXTERNAL_TEMPLATE;
			initopts.template_path = o.template;
		}

		if (o.gitdir) {
			/**
			 * If you specified a separate git directory, then initialize
			 * the repository at that path and use the second path as the
			 * working directory of the repository (with a git-link file)
			 */
			initopts.workdir_path = o.dir;
			o.dir = o.gitdir;
		}

		if (o.shared != 0)
			initopts.mode = o.shared;

		check_lg2(git_repository_init_ext(&repo, o.dir, &initopts),
				"Could not initialize repository", NULL);
	}

	/** Print a message to stdout like "git init" does. */

	if (!o.quiet) {
		if (o.bare || o.gitdir)
			o.dir = git_repository_path(repo);
		else
			o.dir = git_repository_workdir(repo);

		printf("Initialized empty Git repository in %s\n", o.dir);
	}

	/**
	 * As an extension to the basic "git init" command, this example
	 * gives the option to create an empty initial commit.  This is
	 * mostly to demonstrate what it takes to do that, but also some
	 * people like to have that empty base commit in their repo.
	 */
	if (o.initial_commit) {
		create_initial_commit(repo);
		printf("Created empty initial commit\n");
	}

	git_repository_free(repo);

	return 0;
}