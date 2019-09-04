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
struct repository {int dummy; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (char const**) ; 
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_ui_config ; 
 int /*<<< orphan*/  log_tree_commit (struct rev_info*,struct commit*) ; 
 int /*<<< orphan*/  repo_init_revisions (struct repository*,struct rev_info*,char const*) ; 
 int /*<<< orphan*/  setup_revisions (scalar_t__,char const**,struct rev_info*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void show_diff_tree(struct repository *r,
			   const char *prefix,
			   struct commit *commit)
{
	const char *argv[] = {
		"diff-tree", "--pretty", "--stat", "--summary", "--cc", NULL
	};
	struct rev_info opt;

	git_config(git_diff_ui_config, NULL);
	repo_init_revisions(r, &opt, prefix);

	setup_revisions(ARRAY_SIZE(argv) - 1, argv, &opt, NULL);
	log_tree_commit(&opt, commit);
}