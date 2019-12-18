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
struct rev_info {int /*<<< orphan*/  line_log_data; } ;
struct line_log_data {int dummy; } ;
struct commit {int /*<<< orphan*/  object; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_decoration (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct line_log_data*) ; 
 int /*<<< orphan*/  free_line_log_data (struct line_log_data*) ; 
 struct line_log_data* line_log_data_copy (struct line_log_data*) ; 
 struct line_log_data* line_log_data_merge (struct line_log_data*,struct line_log_data*) ; 
 struct line_log_data* lookup_decoration (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void add_line_range(struct rev_info *revs, struct commit *commit,
			   struct line_log_data *range)
{
	struct line_log_data *old_line = NULL;
	struct line_log_data *new_line = NULL;

	old_line = lookup_decoration(&revs->line_log_data, &commit->object);
	if (old_line && range) {
		new_line = line_log_data_merge(old_line, range);
		free_line_log_data(old_line);
	} else if (range)
		new_line = line_log_data_copy(range);

	if (new_line)
		add_decoration(&revs->line_log_data, &commit->object, new_line);
}