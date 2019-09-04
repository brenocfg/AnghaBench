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
struct string_list_item {scalar_t__ util; } ;
struct patch {int dummy; } ;
struct apply_state {int /*<<< orphan*/  fn_table; } ;

/* Variables and functions */
 struct string_list_item* string_list_lookup (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static struct patch *in_fn_table(struct apply_state *state, const char *name)
{
	struct string_list_item *item;

	if (name == NULL)
		return NULL;

	item = string_list_lookup(&state->fn_table, name);
	if (item != NULL)
		return (struct patch *)item->util;

	return NULL;
}