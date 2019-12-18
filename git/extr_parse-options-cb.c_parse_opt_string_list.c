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
struct option {struct string_list* value; } ;

/* Variables and functions */
 int /*<<< orphan*/  string_list_append (struct string_list*,char const*) ; 
 int /*<<< orphan*/  string_list_clear (struct string_list*,int /*<<< orphan*/ ) ; 

int parse_opt_string_list(const struct option *opt, const char *arg, int unset)
{
	struct string_list *v = opt->value;

	if (unset) {
		string_list_clear(v, 0);
		return 0;
	}

	if (!arg)
		return -1;

	string_list_append(v, arg);
	return 0;
}