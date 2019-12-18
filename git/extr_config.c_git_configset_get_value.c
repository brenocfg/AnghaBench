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
struct config_set {int dummy; } ;
struct TYPE_2__ {char* string; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 struct string_list* git_configset_get_value_multi (struct config_set*,char const*) ; 

int git_configset_get_value(struct config_set *cs, const char *key, const char **value)
{
	const struct string_list *values = NULL;
	/*
	 * Follows "last one wins" semantic, i.e., if there are multiple matches for the
	 * queried key in the files of the configset, the value returned will be the last
	 * value in the value list for that key.
	 */
	values = git_configset_get_value_multi(cs, key);

	if (!values)
		return 1;
	assert(values->nr > 0);
	*value = values->items[values->nr - 1].string;
	return 0;
}