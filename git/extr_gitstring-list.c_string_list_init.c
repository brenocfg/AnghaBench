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
struct string_list {int strdup_strings; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct string_list*,int /*<<< orphan*/ ,int) ; 

void string_list_init(struct string_list *list, int strdup_strings)
{
	memset(list, 0, sizeof(*list));
	list->strdup_strings = strdup_strings;
}