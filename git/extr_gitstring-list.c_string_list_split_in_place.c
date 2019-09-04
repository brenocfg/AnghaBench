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
struct string_list {scalar_t__ strdup_strings; } ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*) ; 
 char* strchr (char*,int) ; 
 int /*<<< orphan*/  string_list_append (struct string_list*,char*) ; 

int string_list_split_in_place(struct string_list *list, char *string,
			       int delim, int maxsplit)
{
	int count = 0;
	char *p = string, *end;

	if (list->strdup_strings)
		die("internal error in string_list_split_in_place(): "
		    "list->strdup_strings must not be set");
	for (;;) {
		count++;
		if (maxsplit >= 0 && count > maxsplit) {
			string_list_append(list, p);
			return count;
		}
		end = strchr(p, delim);
		if (end) {
			*end = '\0';
			string_list_append(list, p);
			p = end + 1;
		} else {
			string_list_append(list, p);
			return count;
		}
	}
}