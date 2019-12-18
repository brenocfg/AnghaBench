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
struct replay_opts {int allow_ff; int allow_empty; int verbose; int /*<<< orphan*/  strategy; int /*<<< orphan*/  gpg_sign; int /*<<< orphan*/  reschedule_failed_exec; int /*<<< orphan*/  allow_empty_message; scalar_t__ allow_rerere_auto; int /*<<< orphan*/  signoff; int /*<<< orphan*/  action; } ;
struct rebase_options {int flags; int /*<<< orphan*/  strategy_opts; int /*<<< orphan*/  strategy; int /*<<< orphan*/  gpg_sign_opt; int /*<<< orphan*/  reschedule_failed_exec; int /*<<< orphan*/  allow_empty_message; scalar_t__ allow_rerere_autoupdate; int /*<<< orphan*/  signoff; } ;

/* Variables and functions */
 int REBASE_FORCE ; 
 int REBASE_VERBOSE ; 
 int /*<<< orphan*/  REPLAY_INTERACTIVE_REBASE ; 
 struct replay_opts REPLAY_OPTS_INIT ; 
 int /*<<< orphan*/  parse_strategy_opts (struct replay_opts*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sequencer_init_config (struct replay_opts*) ; 
 int /*<<< orphan*/  xstrdup_or_null (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct replay_opts get_replay_opts(const struct rebase_options *opts)
{
	struct replay_opts replay = REPLAY_OPTS_INIT;

	replay.action = REPLAY_INTERACTIVE_REBASE;
	sequencer_init_config(&replay);

	replay.signoff = opts->signoff;
	replay.allow_ff = !(opts->flags & REBASE_FORCE);
	if (opts->allow_rerere_autoupdate)
		replay.allow_rerere_auto = opts->allow_rerere_autoupdate;
	replay.allow_empty = 1;
	replay.allow_empty_message = opts->allow_empty_message;
	replay.verbose = opts->flags & REBASE_VERBOSE;
	replay.reschedule_failed_exec = opts->reschedule_failed_exec;
	replay.gpg_sign = xstrdup_or_null(opts->gpg_sign_opt);
	replay.strategy = opts->strategy;
	if (opts->strategy_opts)
		parse_strategy_opts(&replay, opts->strategy_opts);

	return replay;
}