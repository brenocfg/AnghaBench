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
struct rev_info {int dummy; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (char const**) ; 
 int /*<<< orphan*/  die (char*) ; 
 struct commit* get_revision (struct rev_info*) ; 
 scalar_t__ prepare_revision_walk (struct rev_info*) ; 
 int /*<<< orphan*/  print_commit (struct commit*) ; 
 int /*<<< orphan*/  repo_init_revisions (int /*<<< orphan*/ ,struct rev_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_revision_walk () ; 
 int /*<<< orphan*/  setup_revisions (int,char const**,struct rev_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static int run_revision_walk(void)
{
	struct rev_info rev;
	struct commit *commit;
	const char *argv[] = {NULL, "--all", NULL};
	int argc = ARRAY_SIZE(argv) - 1;
	int got_revision = 0;

	repo_init_revisions(the_repository, &rev, NULL);
	setup_revisions(argc, argv, &rev, NULL);
	if (prepare_revision_walk(&rev))
		die("revision walk setup failed");

	while ((commit = get_revision(&rev)) != NULL) {
		print_commit(commit);
		got_revision = 1;
	}

	reset_revision_walk();
	return got_revision;
}