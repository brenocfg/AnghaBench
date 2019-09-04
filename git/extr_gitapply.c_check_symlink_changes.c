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
struct apply_state {int /*<<< orphan*/  symlink_changes; } ;

/* Variables and functions */
 struct string_list_item* string_list_lookup (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static uintptr_t check_symlink_changes(struct apply_state *state, const char *path)
{
	struct string_list_item *ent;

	ent = string_list_lookup(&state->symlink_changes, path);
	if (!ent)
		return 0;
	return (uintptr_t)ent->util;
}