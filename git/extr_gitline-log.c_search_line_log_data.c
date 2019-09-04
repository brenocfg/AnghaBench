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
struct line_log_data {struct line_log_data* next; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static struct line_log_data *
search_line_log_data(struct line_log_data *list, const char *path,
		     struct line_log_data **insertion_point)
{
	struct line_log_data *p = list;
	if (insertion_point)
		*insertion_point = NULL;
	while (p) {
		int cmp = strcmp(p->path, path);
		if (!cmp)
			return p;
		if (insertion_point && cmp < 0)
			*insertion_point = p;
		p = p->next;
	}
	return NULL;
}