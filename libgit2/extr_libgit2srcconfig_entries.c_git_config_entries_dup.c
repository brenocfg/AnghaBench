#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  include_depth; int /*<<< orphan*/  level; void* value; void* name; } ;
typedef  TYPE_2__ git_config_entry ;
struct TYPE_14__ {TYPE_4__* list; } ;
typedef  TYPE_3__ git_config_entries ;
struct TYPE_15__ {TYPE_1__* entry; struct TYPE_15__* next; } ;
typedef  TYPE_4__ config_entry_list ;
struct TYPE_12__ {int /*<<< orphan*/  include_depth; int /*<<< orphan*/  level; scalar_t__ value; scalar_t__ name; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (void*) ; 
 TYPE_2__* git__calloc (int,int) ; 
 void* git__strdup (scalar_t__) ; 
 int git_config_entries_append (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  git_config_entries_free (TYPE_3__*) ; 
 int git_config_entries_new (TYPE_3__**) ; 

int git_config_entries_dup(git_config_entries **out, git_config_entries *entries)
{
	git_config_entries *result = NULL;
	config_entry_list *head;
	int error;

	if ((error = git_config_entries_new(&result)) < 0)
		goto out;

	for (head = entries->list; head; head = head->next) {
		git_config_entry *dup;

		dup = git__calloc(1, sizeof(git_config_entry));
		dup->name = git__strdup(head->entry->name);
		GIT_ERROR_CHECK_ALLOC(dup->name);
		if (head->entry->value) {
			dup->value = git__strdup(head->entry->value);
			GIT_ERROR_CHECK_ALLOC(dup->value);
		}
		dup->level = head->entry->level;
		dup->include_depth = head->entry->include_depth;

		if ((error = git_config_entries_append(result, dup)) < 0)
			goto out;
	}

	*out = result;
	result = NULL;

out:
	git_config_entries_free(result);
	return error;
}