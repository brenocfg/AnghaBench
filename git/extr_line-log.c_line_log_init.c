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
struct string_list {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pathspec; int /*<<< orphan*/  repo; } ;
struct rev_info {TYPE_1__ diffopt; } ;
struct line_log_data {int dummy; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_line_range (struct rev_info*,struct commit*,struct line_log_data*) ; 
 struct commit* check_single_commit (struct rev_info*) ; 
 struct line_log_data* parse_lines (int /*<<< orphan*/ ,struct commit*,char const*,struct string_list*) ; 
 int /*<<< orphan*/  parse_pathspec_from_ranges (int /*<<< orphan*/ *,struct line_log_data*) ; 

void line_log_init(struct rev_info *rev, const char *prefix, struct string_list *args)
{
	struct commit *commit = NULL;
	struct line_log_data *range;

	commit = check_single_commit(rev);
	range = parse_lines(rev->diffopt.repo, commit, prefix, args);
	add_line_range(rev, commit, range);

	parse_pathspec_from_ranges(&rev->diffopt.pathspec, range);
}