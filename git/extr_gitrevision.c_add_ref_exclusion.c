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
 int /*<<< orphan*/  string_list_append (struct string_list*,char const*) ; 
 struct string_list* xcalloc (int,int) ; 

void add_ref_exclusion(struct string_list **ref_excludes_p, const char *exclude)
{
	if (!*ref_excludes_p) {
		*ref_excludes_p = xcalloc(1, sizeof(**ref_excludes_p));
		(*ref_excludes_p)->strdup_strings = 1;
	}
	string_list_append(*ref_excludes_p, exclude);
}