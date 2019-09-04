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
struct string_list_item {int /*<<< orphan*/  util; } ;
struct patch {struct patch* next; int /*<<< orphan*/  old_name; scalar_t__ is_rename; int /*<<< orphan*/ * new_name; } ;
struct apply_state {int /*<<< orphan*/  fn_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  PATH_TO_BE_DELETED ; 
 struct string_list_item* string_list_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void prepare_fn_table(struct apply_state *state, struct patch *patch)
{
	/*
	 * store information about incoming file deletion
	 */
	while (patch) {
		if ((patch->new_name == NULL) || (patch->is_rename)) {
			struct string_list_item *item;
			item = string_list_insert(&state->fn_table, patch->old_name);
			item->util = PATH_TO_BE_DELETED;
		}
		patch = patch->next;
	}
}