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
struct TYPE_2__ {int /*<<< orphan*/  oid; } ;
struct tree {TYPE_1__ object; } ;
struct string_list_item {struct stage_data* util; } ;
struct string_list {int dummy; } ;
struct stage_data {int /*<<< orphan*/ * stages; } ;
struct repository {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_tree_entry_if_blob (struct repository*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 struct string_list_item* string_list_insert (struct string_list*,char const*) ; 
 struct stage_data* xcalloc (int,int) ; 

__attribute__((used)) static struct stage_data *insert_stage_data(struct repository *r,
		const char *path,
		struct tree *o, struct tree *a, struct tree *b,
		struct string_list *entries)
{
	struct string_list_item *item;
	struct stage_data *e = xcalloc(1, sizeof(struct stage_data));
	get_tree_entry_if_blob(r, &o->object.oid, path, &e->stages[1]);
	get_tree_entry_if_blob(r, &a->object.oid, path, &e->stages[2]);
	get_tree_entry_if_blob(r, &b->object.oid, path, &e->stages[3]);
	item = string_list_insert(entries, path);
	item->util = e;
	return e;
}