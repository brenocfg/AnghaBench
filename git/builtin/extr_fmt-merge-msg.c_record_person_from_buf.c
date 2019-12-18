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
struct string_list_item {void* util; } ;
struct string_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ isspace (char) ; 
 char* strchrnul (char*,char) ; 
 struct string_list_item* string_list_insert (struct string_list*,char*) ; 
 struct string_list_item* string_list_lookup (struct string_list*,char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 char* strstr (char const*,char const*) ; 
 scalar_t__ util_as_integral (struct string_list_item*) ; 
 char* xmemdupz (char*,int) ; 

__attribute__((used)) static void record_person_from_buf(int which, struct string_list *people,
				   const char *buffer)
{
	char *name_buf, *name, *name_end;
	struct string_list_item *elem;
	const char *field;

	field = (which == 'a') ? "\nauthor " : "\ncommitter ";
	name = strstr(buffer, field);
	if (!name)
		return;
	name += strlen(field);
	name_end = strchrnul(name, '<');
	if (*name_end)
		name_end--;
	while (isspace(*name_end) && name <= name_end)
		name_end--;
	if (name_end < name)
		return;
	name_buf = xmemdupz(name, name_end - name + 1);

	elem = string_list_lookup(people, name_buf);
	if (!elem) {
		elem = string_list_insert(people, name_buf);
		elem->util = (void *)0;
	}
	elem->util = (void*)(util_as_integral(elem) + 1);
	free(name_buf);
}