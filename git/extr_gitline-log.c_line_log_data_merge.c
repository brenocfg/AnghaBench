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
struct line_log_data {int /*<<< orphan*/  ranges; struct line_log_data* next; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  line_log_data_init (struct line_log_data*) ; 
 int /*<<< orphan*/  range_set_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  range_set_union (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct line_log_data* xmalloc (int) ; 
 int /*<<< orphan*/  xstrdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct line_log_data *line_log_data_merge(struct line_log_data *a,
						 struct line_log_data *b)
{
	struct line_log_data *head = NULL, **pp = &head;

	while (a || b) {
		struct line_log_data *src;
		struct line_log_data *src2 = NULL;
		struct line_log_data *d;
		int cmp;
		if (!a)
			cmp = 1;
		else if (!b)
			cmp = -1;
		else
			cmp = strcmp(a->path, b->path);
		if (cmp < 0) {
			src = a;
			a = a->next;
		} else if (cmp == 0) {
			src = a;
			a = a->next;
			src2 = b;
			b = b->next;
		} else {
			src = b;
			b = b->next;
		}
		d = xmalloc(sizeof(struct line_log_data));
		line_log_data_init(d);
		d->path = xstrdup(src->path);
		*pp = d;
		pp = &d->next;
		if (src2)
			range_set_union(&d->ranges, &src->ranges, &src2->ranges);
		else
			range_set_copy(&d->ranges, &src->ranges);
	}

	return head;
}