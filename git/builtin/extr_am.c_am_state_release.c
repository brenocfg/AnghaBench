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
struct am_state {int /*<<< orphan*/  git_apply_opts; int /*<<< orphan*/  msg; int /*<<< orphan*/  author_date; int /*<<< orphan*/  author_email; int /*<<< orphan*/  author_name; int /*<<< orphan*/  dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  argv_array_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void am_state_release(struct am_state *state)
{
	free(state->dir);
	free(state->author_name);
	free(state->author_email);
	free(state->author_date);
	free(state->msg);
	argv_array_clear(&state->git_apply_opts);
}