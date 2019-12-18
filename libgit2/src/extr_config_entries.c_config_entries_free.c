#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* next; struct TYPE_7__* list; int /*<<< orphan*/  map; } ;
typedef  TYPE_1__ git_config_entries ;
typedef  TYPE_1__ config_entry_list ;

/* Variables and functions */
 int /*<<< orphan*/  config_entry_list_free (TYPE_1__*) ; 
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_strmap_foreach_value (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_strmap_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void config_entries_free(git_config_entries *entries)
{
	config_entry_list *list = NULL, *next;

	git_strmap_foreach_value(entries->map, list, config_entry_list_free(list));
	git_strmap_free(entries->map);

	list = entries->list;
	while (list != NULL) {
		next = list->next;
		git__free(list);
		list = next;
	}

	git__free(entries);
}