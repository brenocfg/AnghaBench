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
struct object_id {int dummy; } ;
struct diff_options {int dummy; } ;
struct commit_list {int dummy; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_commit_marks (struct commit*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  diff_emit_submodule_error (struct diff_options*,char*) ; 
 int /*<<< orphan*/  free (struct repository*) ; 
 int /*<<< orphan*/  free_commit_list (struct commit_list*) ; 
 struct repository* open_submodule (char const*) ; 
 scalar_t__ prepare_submodule_summary (struct rev_info*,char const*,struct commit*,struct commit*,struct commit_list*) ; 
 int /*<<< orphan*/  print_submodule_summary (struct repository*,struct rev_info*,struct diff_options*) ; 
 int /*<<< orphan*/  repo_clear (struct repository*) ; 
 int /*<<< orphan*/  show_submodule_header (struct diff_options*,char const*,struct object_id*,struct object_id*,unsigned int,struct repository*,struct commit**,struct commit**,struct commit_list**) ; 

void show_submodule_summary(struct diff_options *o, const char *path,
		struct object_id *one, struct object_id *two,
		unsigned dirty_submodule)
{
	struct rev_info rev;
	struct commit *left = NULL, *right = NULL;
	struct commit_list *merge_bases = NULL;
	struct repository *sub;

	sub = open_submodule(path);
	show_submodule_header(o, path, one, two, dirty_submodule,
			      sub, &left, &right, &merge_bases);

	/*
	 * If we don't have both a left and a right pointer, there is no
	 * reason to try and display a summary. The header line should contain
	 * all the information the user needs.
	 */
	if (!left || !right || !sub)
		goto out;

	/* Treat revision walker failure the same as missing commits */
	if (prepare_submodule_summary(&rev, path, left, right, merge_bases)) {
		diff_emit_submodule_error(o, "(revision walker failed)\n");
		goto out;
	}

	print_submodule_summary(sub, &rev, o);

out:
	if (merge_bases)
		free_commit_list(merge_bases);
	clear_commit_marks(left, ~0);
	clear_commit_marks(right, ~0);
	if (sub) {
		repo_clear(sub);
		free(sub);
	}
}