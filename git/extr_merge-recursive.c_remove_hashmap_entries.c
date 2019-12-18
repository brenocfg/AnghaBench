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
struct hashmap {int dummy; } ;
struct dir_rename_entry {int /*<<< orphan*/  ent; } ;
struct TYPE_2__ {struct dir_rename_entry* util; } ;

/* Variables and functions */
 int /*<<< orphan*/  hashmap_remove (struct hashmap*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  string_list_clear (struct string_list*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void remove_hashmap_entries(struct hashmap *dir_renames,
				   struct string_list *items_to_remove)
{
	int i;
	struct dir_rename_entry *entry;

	for (i = 0; i < items_to_remove->nr; i++) {
		entry = items_to_remove->items[i].util;
		hashmap_remove(dir_renames, &entry->ent, NULL);
	}
	string_list_clear(items_to_remove, 0);
}