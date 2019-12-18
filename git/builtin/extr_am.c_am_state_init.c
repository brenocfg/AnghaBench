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
struct am_state {int prec; int threeway; int utf8; int message_id; char* sign_commit; int /*<<< orphan*/  git_apply_opts; int /*<<< orphan*/  scissors; int /*<<< orphan*/  dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCISSORS_UNSET ; 
 int /*<<< orphan*/  argv_array_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_bool (char*,int*) ; 
 int /*<<< orphan*/  git_pathdup (char*) ; 
 int /*<<< orphan*/  memset (struct am_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void am_state_init(struct am_state *state)
{
	int gpgsign;

	memset(state, 0, sizeof(*state));

	state->dir = git_pathdup("rebase-apply");

	state->prec = 4;

	git_config_get_bool("am.threeway", &state->threeway);

	state->utf8 = 1;

	git_config_get_bool("am.messageid", &state->message_id);

	state->scissors = SCISSORS_UNSET;

	argv_array_init(&state->git_apply_opts);

	if (!git_config_get_bool("commit.gpgsign", &gpgsign))
		state->sign_commit = gpgsign ? "" : NULL;
}