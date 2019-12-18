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
struct string_list_item {int dummy; } ;
struct string_list {struct string_list_item* items; } ;

/* Variables and functions */
 int add_entry (int,struct string_list*,char const*) ; 

struct string_list_item *string_list_insert(struct string_list *list, const char *string)
{
	int index = add_entry(-1, list, string);

	if (index < 0)
		index = -1 - index;

	return list->items + index;
}