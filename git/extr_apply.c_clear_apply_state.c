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
struct apply_state {int /*<<< orphan*/  root; int /*<<< orphan*/  symlink_changes; int /*<<< orphan*/  limit_by_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  strbuf_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  string_list_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void clear_apply_state(struct apply_state *state)
{
	string_list_clear(&state->limit_by_name, 0);
	string_list_clear(&state->symlink_changes, 0);
	strbuf_release(&state->root);

	/* &state->fn_table is cleared at the end of apply_patch() */
}