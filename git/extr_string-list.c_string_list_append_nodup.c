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
struct string_list_item {char* string; int /*<<< orphan*/ * util; } ;
struct string_list {scalar_t__ nr; struct string_list_item* items; int /*<<< orphan*/  alloc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (struct string_list_item*,scalar_t__,int /*<<< orphan*/ ) ; 

struct string_list_item *string_list_append_nodup(struct string_list *list,
						  char *string)
{
	struct string_list_item *retval;
	ALLOC_GROW(list->items, list->nr + 1, list->alloc);
	retval = &list->items[list->nr++];
	retval->string = string;
	retval->util = NULL;
	return retval;
}