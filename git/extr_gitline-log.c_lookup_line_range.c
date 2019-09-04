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
struct line_log_data {int /*<<< orphan*/  ranges; struct line_log_data* next; } ;
struct commit {int /*<<< orphan*/  object; } ;

/* Variables and functions */
 struct line_log_data* lookup_decoration (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  range_set_check_invariants (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct line_log_data *lookup_line_range(struct rev_info *revs,
					       struct commit *commit)
{
	struct line_log_data *ret = NULL;
	struct line_log_data *d;

	ret = lookup_decoration(&revs->line_log_data, &commit->object);

	for (d = ret; d; d = d->next)
		range_set_check_invariants(&d->ranges);

	return ret;
}