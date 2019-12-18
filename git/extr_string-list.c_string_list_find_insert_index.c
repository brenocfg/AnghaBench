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
struct string_list {int dummy; } ;

/* Variables and functions */
 int get_entry_index (struct string_list const*,char const*,int*) ; 

int string_list_find_insert_index(const struct string_list *list, const char *string,
				  int negative_existing_index)
{
	int exact_match;
	int index = get_entry_index(list, string, &exact_match);
	if (exact_match)
		index = -1 - (negative_existing_index ? index : 0);
	return index;
}