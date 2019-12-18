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
struct file_list {int tmp; int /*<<< orphan*/ * fns; scalar_t__ sz; scalar_t__ count; } ;

/* Variables and functions */

void
file_list_init(struct file_list *fl, bool tmp)
{

	if (fl) {
		fl->count = 0;
		fl->sz = 0;
		fl->fns = NULL;
		fl->tmp = tmp;
	}
}