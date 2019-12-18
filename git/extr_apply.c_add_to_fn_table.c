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
struct string_list_item {struct patch* util; } ;
struct patch {int /*<<< orphan*/ * old_name; scalar_t__ is_rename; int /*<<< orphan*/ * new_name; } ;
struct apply_state {int /*<<< orphan*/  fn_table; } ;

/* Variables and functions */
 struct patch* PATH_WAS_DELETED ; 
 struct string_list_item* string_list_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void add_to_fn_table(struct apply_state *state, struct patch *patch)
{
	struct string_list_item *item;

	/*
	 * Always add new_name unless patch is a deletion
	 * This should cover the cases for normal diffs,
	 * file creations and copies
	 */
	if (patch->new_name != NULL) {
		item = string_list_insert(&state->fn_table, patch->new_name);
		item->util = patch;
	}

	/*
	 * store a failure on rename/deletion cases because
	 * later chunks shouldn't patch old names
	 */
	if ((patch->new_name == NULL) || (patch->is_rename)) {
		item = string_list_insert(&state->fn_table, patch->old_name);
		item->util = PATH_WAS_DELETED;
	}
}