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
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  string_list_split (struct string_list*,char const*,char,int) ; 

__attribute__((used)) static void parse_string_list(struct string_list *list, const char *arg)
{
	if (!strcmp(arg, "-"))
		return;

	(void)string_list_split(list, arg, ':', -1);
}