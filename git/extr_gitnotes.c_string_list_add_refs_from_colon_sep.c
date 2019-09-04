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
 struct string_list STRING_LIST_INIT_NODUP ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  string_list_add_refs_by_glob (struct string_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_list_clear (struct string_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_list_remove_empty_items (struct string_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_list_split_in_place (struct string_list*,char*,char,int) ; 
 char* xstrdup (char const*) ; 

void string_list_add_refs_from_colon_sep(struct string_list *list,
					 const char *globs)
{
	struct string_list split = STRING_LIST_INIT_NODUP;
	char *globs_copy = xstrdup(globs);
	int i;

	string_list_split_in_place(&split, globs_copy, ':', -1);
	string_list_remove_empty_items(&split, 0);

	for (i = 0; i < split.nr; i++)
		string_list_add_refs_by_glob(list, split.items[i].string);

	string_list_clear(&split, 0);
	free(globs_copy);
}