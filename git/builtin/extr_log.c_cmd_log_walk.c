#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ check_failed; } ;
struct TYPE_6__ {int close_file; int needed_rename_limit; int degraded_cc_to_c; int output_format; TYPE_1__ flags; int /*<<< orphan*/  file; } ;
struct rev_info {scalar_t__ max_count; TYPE_3__ diffopt; int /*<<< orphan*/  reflog_info; scalar_t__ early_output; } ;
struct commit {int /*<<< orphan*/ * parents; } ;
struct TYPE_5__ {int /*<<< orphan*/  parsed_objects; } ;

/* Variables and functions */
 int DIFF_FORMAT_CHECKDIFF ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int diff_result_code (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_early_output (struct rev_info*) ; 
 int /*<<< orphan*/  free_commit_buffer (int /*<<< orphan*/ ,struct commit*) ; 
 int /*<<< orphan*/  free_commit_list (int /*<<< orphan*/ *) ; 
 struct commit* get_revision (struct rev_info*) ; 
 int /*<<< orphan*/  log_tree_commit (struct rev_info*,struct commit*) ; 
 scalar_t__ prepare_revision_walk (struct rev_info*) ; 
 int /*<<< orphan*/  setup_early_output () ; 
 TYPE_2__* the_repository ; 

__attribute__((used)) static int cmd_log_walk(struct rev_info *rev)
{
	struct commit *commit;
	int saved_nrl = 0;
	int saved_dcctc = 0, close_file = rev->diffopt.close_file;

	if (rev->early_output)
		setup_early_output();

	if (prepare_revision_walk(rev))
		die(_("revision walk setup failed"));

	if (rev->early_output)
		finish_early_output(rev);

	/*
	 * For --check and --exit-code, the exit code is based on CHECK_FAILED
	 * and HAS_CHANGES being accumulated in rev->diffopt, so be careful to
	 * retain that state information if replacing rev->diffopt in this loop
	 */
	rev->diffopt.close_file = 0;
	while ((commit = get_revision(rev)) != NULL) {
		if (!log_tree_commit(rev, commit) && rev->max_count >= 0)
			/*
			 * We decremented max_count in get_revision,
			 * but we didn't actually show the commit.
			 */
			rev->max_count++;
		if (!rev->reflog_info) {
			/*
			 * We may show a given commit multiple times when
			 * walking the reflogs.
			 */
			free_commit_buffer(the_repository->parsed_objects,
					   commit);
			free_commit_list(commit->parents);
			commit->parents = NULL;
		}
		if (saved_nrl < rev->diffopt.needed_rename_limit)
			saved_nrl = rev->diffopt.needed_rename_limit;
		if (rev->diffopt.degraded_cc_to_c)
			saved_dcctc = 1;
	}
	rev->diffopt.degraded_cc_to_c = saved_dcctc;
	rev->diffopt.needed_rename_limit = saved_nrl;
	if (close_file)
		fclose(rev->diffopt.file);

	if (rev->diffopt.output_format & DIFF_FORMAT_CHECKDIFF &&
	    rev->diffopt.flags.check_failed) {
		return 02;
	}
	return diff_result_code(&rev->diffopt, 0);
}