#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct string_list_item {struct branch_info* util; int /*<<< orphan*/  string; } ;
struct show_info {int width; int any_rebase; int /*<<< orphan*/  list; struct ref_states* states; } ;
struct ref_states {TYPE_2__* remote; } ;
struct TYPE_3__ {int /*<<< orphan*/  nr; } ;
struct branch_info {scalar_t__ rebase; int /*<<< orphan*/  remote_name; TYPE_1__ merge; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct string_list_item* string_list_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int add_local_to_show_info(struct string_list_item *branch_item, void *cb_data)
{
	struct show_info *show_info = cb_data;
	struct ref_states *states = show_info->states;
	struct branch_info *branch_info = branch_item->util;
	struct string_list_item *item;
	int n;

	if (!branch_info->merge.nr || !branch_info->remote_name ||
	    strcmp(states->remote->name, branch_info->remote_name))
		return 0;
	if ((n = strlen(branch_item->string)) > show_info->width)
		show_info->width = n;
	if (branch_info->rebase)
		show_info->any_rebase = 1;

	item = string_list_insert(show_info->list, branch_item->string);
	item->util = branch_info;

	return 0;
}