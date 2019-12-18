#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct strbuf {int dummy; } ;
struct replay_opts {int /*<<< orphan*/  action; } ;
struct rebase_options {scalar_t__ type; int /*<<< orphan*/  state_dir; } ;
struct TYPE_2__ {int /*<<< orphan*/  objects; } ;

/* Variables and functions */
 scalar_t__ REBASE_INTERACTIVE ; 
 int /*<<< orphan*/  REF_NO_DEREF ; 
 int /*<<< orphan*/  REPLAY_INTERACTIVE_REBASE ; 
 struct replay_opts REPLAY_OPTS_INIT ; 
 int /*<<< orphan*/  RUN_GIT_CMD ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  apply_autostash (struct rebase_options*) ; 
 int /*<<< orphan*/  close_object_store (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delete_ref (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ remove_dir_recursively (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  run_command_v_opt (char const**,int /*<<< orphan*/ ) ; 
 int sequencer_remove_state (struct replay_opts*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 TYPE_1__* the_repository ; 

__attribute__((used)) static int finish_rebase(struct rebase_options *opts)
{
	struct strbuf dir = STRBUF_INIT;
	const char *argv_gc_auto[] = { "gc", "--auto", NULL };
	int ret = 0;

	delete_ref(NULL, "REBASE_HEAD", NULL, REF_NO_DEREF);
	apply_autostash(opts);
	close_object_store(the_repository->objects);
	/*
	 * We ignore errors in 'gc --auto', since the
	 * user should see them.
	 */
	run_command_v_opt(argv_gc_auto, RUN_GIT_CMD);
	if (opts->type == REBASE_INTERACTIVE) {
		struct replay_opts replay = REPLAY_OPTS_INIT;

		replay.action = REPLAY_INTERACTIVE_REBASE;
		ret = sequencer_remove_state(&replay);
	} else {
		strbuf_addstr(&dir, opts->state_dir);
		if (remove_dir_recursively(&dir, 0))
			ret = error(_("could not remove '%s'"),
				    opts->state_dir);
		strbuf_release(&dir);
	}

	return ret;
}