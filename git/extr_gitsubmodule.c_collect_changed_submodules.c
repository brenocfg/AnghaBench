#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct string_list {int dummy; } ;
struct TYPE_4__ {struct collect_changed_submodules_cb_data* format_callback_data; int /*<<< orphan*/  format_callback; int /*<<< orphan*/  output_format; } ;
struct rev_info {TYPE_2__ diffopt; } ;
struct repository {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  oid; } ;
struct commit {TYPE_1__ object; } ;
struct collect_changed_submodules_cb_data {int /*<<< orphan*/ * commit_oid; struct string_list* changed; struct repository* repo; } ;
struct argv_array {int /*<<< orphan*/  argv; int /*<<< orphan*/  argc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF_FORMAT_CALLBACK ; 
 int /*<<< orphan*/  collect_changed_submodules_cb ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  diff_tree_combined_merge (struct commit const*,int,struct rev_info*) ; 
 struct commit* get_revision (struct rev_info*) ; 
 scalar_t__ prepare_revision_walk (struct rev_info*) ; 
 int /*<<< orphan*/  repo_init_revisions (struct repository*,struct rev_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_revision_walk () ; 
 int /*<<< orphan*/  setup_revisions (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rev_info*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void collect_changed_submodules(struct repository *r,
				       struct string_list *changed,
				       struct argv_array *argv)
{
	struct rev_info rev;
	const struct commit *commit;

	repo_init_revisions(r, &rev, NULL);
	setup_revisions(argv->argc, argv->argv, &rev, NULL);
	if (prepare_revision_walk(&rev))
		die("revision walk setup failed");

	while ((commit = get_revision(&rev))) {
		struct rev_info diff_rev;
		struct collect_changed_submodules_cb_data data;
		data.repo = r;
		data.changed = changed;
		data.commit_oid = &commit->object.oid;

		repo_init_revisions(r, &diff_rev, NULL);
		diff_rev.diffopt.output_format |= DIFF_FORMAT_CALLBACK;
		diff_rev.diffopt.format_callback = collect_changed_submodules_cb;
		diff_rev.diffopt.format_callback_data = &data;
		diff_tree_combined_merge(commit, 1, &diff_rev);
	}

	reset_revision_walk();
}