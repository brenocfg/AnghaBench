#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ git_config_entry ;
struct TYPE_13__ {TYPE_3__* list; int /*<<< orphan*/  map; } ;
typedef  TYPE_2__ git_config_entries ;
struct TYPE_14__ {TYPE_1__* entry; struct TYPE_14__* last; } ;
typedef  TYPE_3__ config_entry_list ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_3__*) ; 
 int /*<<< orphan*/  config_entry_list_append (TYPE_3__**,TYPE_3__*) ; 
 TYPE_3__* git__calloc (int,int) ; 
 TYPE_3__* git_strmap_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int git_strmap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 

int git_config_entries_append(git_config_entries *entries, git_config_entry *entry)
{
	config_entry_list *existing, *var;
	int error = 0;

	var = git__calloc(1, sizeof(config_entry_list));
	GIT_ERROR_CHECK_ALLOC(var);
	var->entry = entry;

	if ((existing = git_strmap_get(entries->map, entry->name)) == NULL) {
		/*
		 * We only ever inspect `last` from the first config
		 * entry in a multivar. In case where this new entry is
		 * the first one in the entry map, it will also be the
		 * last one at the time of adding it, which is
		 * why we set `last` here to itself. Otherwise we
		 * do not have to set `last` and leave it set to
		 * `NULL`.
		 */
		var->last = var;

		error = git_strmap_set(entries->map, entry->name, var);
	} else {
		config_entry_list_append(&existing, var);
	}

	var = git__calloc(1, sizeof(config_entry_list));
	GIT_ERROR_CHECK_ALLOC(var);
	var->entry = entry;
	config_entry_list_append(&entries->list, var);

	return error;
}