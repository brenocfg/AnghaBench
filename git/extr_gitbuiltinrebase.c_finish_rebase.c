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
struct rebase_options {int /*<<< orphan*/  state_dir; } ;
struct TYPE_2__ {int /*<<< orphan*/  objects; } ;

/* Variables and functions */
 int /*<<< orphan*/  REF_NO_DEREF ; 
 int /*<<< orphan*/  RUN_GIT_CMD ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  apply_autostash (struct rebase_options*) ; 
 int /*<<< orphan*/  close_all_packs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delete_ref (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_dir_recursively (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  run_command_v_opt (char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 TYPE_1__* the_repository ; 

__attribute__((used)) static int finish_rebase(struct rebase_options *opts)
{
	struct strbuf dir = STRBUF_INIT;
	const char *argv_gc_auto[] = { "gc", "--auto", NULL };

	delete_ref(NULL, "REBASE_HEAD", NULL, REF_NO_DEREF);
	apply_autostash(opts);
	close_all_packs(the_repository->objects);
	/*
	 * We ignore errors in 'gc --auto', since the
	 * user should see them.
	 */
	run_command_v_opt(argv_gc_auto, RUN_GIT_CMD);
	strbuf_addstr(&dir, opts->state_dir);
	remove_dir_recursively(&dir, 0);
	strbuf_release(&dir);

	return 0;
}