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
struct TYPE_2__ {int /*<<< orphan*/  buf; } ;
struct stash_info {TYPE_1__ revision; int /*<<< orphan*/  w_commit; } ;
struct child_process {int git_cmd; int no_stdout; int /*<<< orphan*/  args; } ;

/* Variables and functions */
 struct child_process CHILD_PROCESS_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  argv_array_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  argv_array_pushf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  argv_array_pushl (int /*<<< orphan*/ *,char*,char*,char*,char*,...) ; 
 int /*<<< orphan*/  do_clear_stash () ; 
 int error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf_ln (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ref_stash ; 
 int run_command (struct child_process*) ; 

__attribute__((used)) static int do_drop_stash(struct stash_info *info, int quiet)
{
	int ret;
	struct child_process cp_reflog = CHILD_PROCESS_INIT;
	struct child_process cp = CHILD_PROCESS_INIT;

	/*
	 * reflog does not provide a simple function for deleting refs. One will
	 * need to be added to avoid implementing too much reflog code here
	 */

	cp_reflog.git_cmd = 1;
	argv_array_pushl(&cp_reflog.args, "reflog", "delete", "--updateref",
			 "--rewrite", NULL);
	argv_array_push(&cp_reflog.args, info->revision.buf);
	ret = run_command(&cp_reflog);
	if (!ret) {
		if (!quiet)
			printf_ln(_("Dropped %s (%s)"), info->revision.buf,
				  oid_to_hex(&info->w_commit));
	} else {
		return error(_("%s: Could not drop stash entry"),
			     info->revision.buf);
	}

	/*
	 * This could easily be replaced by get_oid, but currently it will throw
	 * a fatal error when a reflog is empty, which we can not recover from.
	 */
	cp.git_cmd = 1;
	/* Even though --quiet is specified, rev-parse still outputs the hash */
	cp.no_stdout = 1;
	argv_array_pushl(&cp.args, "rev-parse", "--verify", "--quiet", NULL);
	argv_array_pushf(&cp.args, "%s@{0}", ref_stash);
	ret = run_command(&cp);

	/* do_clear_stash if we just dropped the last stash entry */
	if (ret)
		do_clear_stash();

	return 0;
}