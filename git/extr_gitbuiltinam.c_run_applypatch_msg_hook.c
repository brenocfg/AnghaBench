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
struct am_state {int /*<<< orphan*/  msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_AND_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  am_path (struct am_state*,char*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ read_commit_msg (struct am_state*) ; 
 int run_hook_le (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int run_applypatch_msg_hook(struct am_state *state)
{
	int ret;

	assert(state->msg);
	ret = run_hook_le(NULL, "applypatch-msg", am_path(state, "final-commit"), NULL);

	if (!ret) {
		FREE_AND_NULL(state->msg);
		if (read_commit_msg(state) < 0)
			die(_("'%s' was deleted by the applypatch-msg hook"),
				am_path(state, "final-commit"));
	}

	return ret;
}