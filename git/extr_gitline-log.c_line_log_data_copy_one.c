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
struct line_log_data {int /*<<< orphan*/  path; int /*<<< orphan*/  ranges; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct line_log_data*) ; 
 int /*<<< orphan*/  line_log_data_init (struct line_log_data*) ; 
 int /*<<< orphan*/  range_set_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct line_log_data* xmalloc (int) ; 
 int /*<<< orphan*/  xstrdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct line_log_data *line_log_data_copy_one(struct line_log_data *r)
{
	struct line_log_data *ret = xmalloc(sizeof(*ret));

	assert(r);
	line_log_data_init(ret);
	range_set_copy(&ret->ranges, &r->ranges);

	ret->path = xstrdup(r->path);

	return ret;
}