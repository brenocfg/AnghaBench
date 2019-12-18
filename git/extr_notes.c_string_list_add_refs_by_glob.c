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
struct string_list {int /*<<< orphan*/  strdup_strings; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  for_each_glob_ref (int /*<<< orphan*/ ,char const*,struct string_list*) ; 
 scalar_t__ get_oid (char const*,struct object_id*) ; 
 scalar_t__ has_glob_specials (char const*) ; 
 int /*<<< orphan*/  string_list_add_one_ref ; 
 int /*<<< orphan*/  string_list_append (struct string_list*,char const*) ; 
 int /*<<< orphan*/  unsorted_string_list_has_string (struct string_list*,char const*) ; 
 int /*<<< orphan*/  warning (char*,char const*) ; 

void string_list_add_refs_by_glob(struct string_list *list, const char *glob)
{
	assert(list->strdup_strings);
	if (has_glob_specials(glob)) {
		for_each_glob_ref(string_list_add_one_ref, glob, list);
	} else {
		struct object_id oid;
		if (get_oid(glob, &oid))
			warning("notes ref %s is invalid", glob);
		if (!unsorted_string_list_has_string(list, glob))
			string_list_append(list, glob);
	}
}