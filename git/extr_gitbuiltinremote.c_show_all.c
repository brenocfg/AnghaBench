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
struct string_list_item {char* string; scalar_t__ util; } ;
struct string_list {int strdup_strings; int nr; struct string_list_item* items; } ;

/* Variables and functions */
 struct string_list STRING_LIST_INIT_NODUP ; 
 int for_each_remote (int /*<<< orphan*/ ,struct string_list*) ; 
 int /*<<< orphan*/  get_one_entry ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  string_list_clear (struct string_list*,int) ; 
 int /*<<< orphan*/  string_list_sort (struct string_list*) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static int show_all(void)
{
	struct string_list list = STRING_LIST_INIT_NODUP;
	int result;

	list.strdup_strings = 1;
	result = for_each_remote(get_one_entry, &list);

	if (!result) {
		int i;

		string_list_sort(&list);
		for (i = 0; i < list.nr; i++) {
			struct string_list_item *item = list.items + i;
			if (verbose)
				printf("%s\t%s\n", item->string,
					item->util ? (const char *)item->util : "");
			else {
				if (i && !strcmp((item - 1)->string, item->string))
					continue;
				printf("%s\n", item->string);
			}
		}
	}
	string_list_clear(&list, 1);
	return result;
}