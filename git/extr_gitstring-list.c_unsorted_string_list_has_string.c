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
 int /*<<< orphan*/ * unsorted_string_list_lookup (struct string_list*,char const*) ; 

int unsorted_string_list_has_string(struct string_list *list,
				    const char *string)
{
	return unsorted_string_list_lookup(list, string) != NULL;
}