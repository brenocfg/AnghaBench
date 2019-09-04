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
struct TYPE_2__ {int /*<<< orphan*/  pathspec; int /*<<< orphan*/  detect_rename; int /*<<< orphan*/  repo; } ;
struct rev_info {TYPE_1__ diffopt; } ;
struct line_log_data {int /*<<< orphan*/  path; struct line_log_data* next; } ;
struct commit {int dummy; } ;
struct argv_array {int dummy; } ;

/* Variables and functions */
 struct argv_array ARGV_ARRAY_INIT ; 
 int /*<<< orphan*/  PATHSPEC_PREFER_FULL ; 
 int /*<<< orphan*/  add_line_range (struct rev_info*,struct commit*,struct line_log_data*) ; 
 char** argv_array_detach (struct argv_array*) ; 
 int /*<<< orphan*/  argv_array_push (struct argv_array*,int /*<<< orphan*/ ) ; 
 struct commit* check_single_commit (struct rev_info*) ; 
 int /*<<< orphan*/  free (char const**) ; 
 struct line_log_data* parse_lines (int /*<<< orphan*/ ,struct commit*,char const*,struct string_list*) ; 
 int /*<<< orphan*/  parse_pathspec (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const**) ; 

void line_log_init(struct rev_info *rev, const char *prefix, struct string_list *args)
{
	struct commit *commit = NULL;
	struct line_log_data *range;

	commit = check_single_commit(rev);
	range = parse_lines(rev->diffopt.repo, commit, prefix, args);
	add_line_range(rev, commit, range);

	if (!rev->diffopt.detect_rename) {
		struct line_log_data *r;
		struct argv_array array = ARGV_ARRAY_INIT;
		const char **paths;

		for (r = range; r; r = r->next)
			argv_array_push(&array, r->path);
		paths = argv_array_detach(&array);

		parse_pathspec(&rev->diffopt.pathspec, 0,
			       PATHSPEC_PREFER_FULL, "", paths);
		/* strings are now owned by pathspec */
		free(paths);
	}
}