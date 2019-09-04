#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  map; } ;
typedef  TYPE_1__ git_config_entries ;
typedef  int /*<<< orphan*/  config_entry_list ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/ * git_strmap_get (int /*<<< orphan*/ ,char const*) ; 

int config_entry_get(config_entry_list **out, git_config_entries *entries, const char *key)
{
	config_entry_list *list;

	if ((list = git_strmap_get(entries->map, key)) == NULL)
		return GIT_ENOTFOUND;

	*out = list;

	return 0;
}