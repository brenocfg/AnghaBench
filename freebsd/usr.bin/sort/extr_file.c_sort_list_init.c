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
struct sort_list {int memsize; int /*<<< orphan*/ * list; scalar_t__ size; scalar_t__ count; } ;

/* Variables and functions */

void
sort_list_init(struct sort_list *l)
{

	if (l) {
		l->count = 0;
		l->size = 0;
		l->memsize = sizeof(struct sort_list);
		l->list = NULL;
	}
}