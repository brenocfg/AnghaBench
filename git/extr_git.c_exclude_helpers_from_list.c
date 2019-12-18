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
struct string_list {int nr; TYPE_1__* items; } ;
struct TYPE_2__ {int /*<<< orphan*/  string; } ;

/* Variables and functions */
 scalar_t__ strstr (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  unsorted_string_list_delete_item (struct string_list*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void exclude_helpers_from_list(struct string_list *list)
{
	int i = 0;

	while (i < list->nr) {
		if (strstr(list->items[i].string, "--"))
			unsorted_string_list_delete_item(list, i, 0);
		else
			i++;
	}
}