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
struct match_list {scalar_t__ count; int /*<<< orphan*/ * first; int /*<<< orphan*/ ** last; } ;

/* Variables and functions */

__attribute__((used)) static void
match_list_init(struct match_list *list)
{
	list->first = NULL;
	list->last = &(list->first);
	list->count = 0;
}