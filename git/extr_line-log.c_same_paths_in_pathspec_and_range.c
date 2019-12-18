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
struct pathspec {int nr; TYPE_1__* items; } ;
struct line_log_data {int /*<<< orphan*/  path; struct line_log_data* next; } ;
struct TYPE_2__ {int /*<<< orphan*/  match; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int same_paths_in_pathspec_and_range(struct pathspec *pathspec,
					    struct line_log_data *range)
{
	int i;
	struct line_log_data *r;

	for (i = 0, r = range; i < pathspec->nr && r; i++, r = r->next)
		if (strcmp(pathspec->items[i].match, r->path))
			return 0;
	if (i < pathspec->nr || r)
		/* different number of pathspec items and ranges */
		return 0;

	return 1;
}