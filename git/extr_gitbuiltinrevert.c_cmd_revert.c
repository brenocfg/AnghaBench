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
struct replay_opts {int edit; int /*<<< orphan*/  action; } ;

/* Variables and functions */
 struct replay_opts REPLAY_OPTS_INIT ; 
 int /*<<< orphan*/  REPLAY_REVERT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 scalar_t__ isatty (int /*<<< orphan*/ ) ; 
 int run_sequencer (int,char const**,struct replay_opts*) ; 
 int /*<<< orphan*/  sequencer_init_config (struct replay_opts*) ; 

int cmd_revert(int argc, const char **argv, const char *prefix)
{
	struct replay_opts opts = REPLAY_OPTS_INIT;
	int res;

	if (isatty(0))
		opts.edit = 1;
	opts.action = REPLAY_REVERT;
	sequencer_init_config(&opts);
	res = run_sequencer(argc, argv, &opts);
	if (res < 0)
		die(_("revert failed"));
	return res;
}