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
struct update_callback_data {int flags; int /*<<< orphan*/  add_errors; } ;
struct TYPE_3__ {int override_submodule_config; } ;
struct TYPE_4__ {TYPE_1__ flags; struct update_callback_data* format_callback_data; int /*<<< orphan*/  format_callback; int /*<<< orphan*/  output_format; } ;
struct rev_info {int /*<<< orphan*/  prune_data; scalar_t__ max_count; TYPE_2__ diffopt; } ;
struct pathspec {int dummy; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF_FORMAT_CALLBACK ; 
 int /*<<< orphan*/  DIFF_RACY_IS_MODIFIED ; 
 int /*<<< orphan*/  clear_pathspec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  copy_pathspec (int /*<<< orphan*/ *,struct pathspec const*) ; 
 int /*<<< orphan*/  memset (struct update_callback_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  repo_init_revisions (int /*<<< orphan*/ ,struct rev_info*,char const*) ; 
 int /*<<< orphan*/  run_diff_files (struct rev_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_revisions (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct rev_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  update_callback ; 

int add_files_to_cache(const char *prefix,
		       const struct pathspec *pathspec, int flags)
{
	struct update_callback_data data;
	struct rev_info rev;

	memset(&data, 0, sizeof(data));
	data.flags = flags;

	repo_init_revisions(the_repository, &rev, prefix);
	setup_revisions(0, NULL, &rev, NULL);
	if (pathspec)
		copy_pathspec(&rev.prune_data, pathspec);
	rev.diffopt.output_format = DIFF_FORMAT_CALLBACK;
	rev.diffopt.format_callback = update_callback;
	rev.diffopt.format_callback_data = &data;
	rev.diffopt.flags.override_submodule_config = 1;
	rev.max_count = 0; /* do not compare unmerged paths with stage #2 */
	run_diff_files(&rev, DIFF_RACY_IS_MODIFIED);
	clear_pathspec(&rev.prune_data);
	return !!data.add_errors;
}