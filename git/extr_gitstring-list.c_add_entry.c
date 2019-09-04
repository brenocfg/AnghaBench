#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct string_list {int nr; TYPE_1__* items; scalar_t__ strdup_strings; int /*<<< orphan*/  alloc; } ;
struct TYPE_4__ {char* string; int /*<<< orphan*/ * util; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MOVE_ARRAY (TYPE_1__*,TYPE_1__*,int) ; 
 int get_entry_index (struct string_list*,char const*,int*) ; 
 char* xstrdup (char const*) ; 

__attribute__((used)) static int add_entry(int insert_at, struct string_list *list, const char *string)
{
	int exact_match = 0;
	int index = insert_at != -1 ? insert_at : get_entry_index(list, string, &exact_match);

	if (exact_match)
		return -1 - index;

	ALLOC_GROW(list->items, list->nr+1, list->alloc);
	if (index < list->nr)
		MOVE_ARRAY(list->items + index + 1, list->items + index,
			   list->nr - index);
	list->items[index].string = list->strdup_strings ?
		xstrdup(string) : (char *)string;
	list->items[index].util = NULL;
	list->nr++;

	return index;
}