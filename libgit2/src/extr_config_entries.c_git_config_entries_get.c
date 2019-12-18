#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_config_entry ;
typedef  int /*<<< orphan*/  git_config_entries ;
struct TYPE_5__ {TYPE_1__* last; } ;
typedef  TYPE_2__ config_entry_list ;
struct TYPE_4__ {int /*<<< orphan*/ * entry; } ;

/* Variables and functions */
 int config_entry_get (TYPE_2__**,int /*<<< orphan*/ *,char const*) ; 

int git_config_entries_get(git_config_entry **out, git_config_entries *entries, const char *key)
{
	config_entry_list *entry;
	int error;

	if ((error = config_entry_get(&entry, entries, key)) < 0)
		return error;
	*out = entry->last->entry;

	return 0;
}