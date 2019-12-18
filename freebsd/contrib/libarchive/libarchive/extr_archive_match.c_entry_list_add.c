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
struct match_file {struct match_file* next; } ;
struct entry_list {int /*<<< orphan*/  count; struct match_file** last; } ;

/* Variables and functions */

__attribute__((used)) static void
entry_list_add(struct entry_list *list, struct match_file *file)
{
	*list->last = file;
	list->last = &(file->next);
	list->count++;
}