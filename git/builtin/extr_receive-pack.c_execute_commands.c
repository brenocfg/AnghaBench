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
struct string_list {int dummy; } ;
struct shallow_info {int dummy; } ;
struct iterate_data {struct shallow_info* si; struct command* cmds; } ;
struct command {char* error_string; struct command* next; } ;
struct check_connected_options {int err_fd; int progress; int /*<<< orphan*/  env; } ;
struct async {int in; int /*<<< orphan*/  proc; } ;
typedef  int /*<<< orphan*/  muxer ;

/* Variables and functions */
 struct check_connected_options CHECK_CONNECTED_INIT ; 
 int /*<<< orphan*/  check_aliased_updates (struct command*) ; 
 scalar_t__ check_connected (int /*<<< orphan*/ ,struct iterate_data*,struct check_connected_options*) ; 
 int /*<<< orphan*/  copy_to_sideband ; 
 int /*<<< orphan*/  execute_commands_atomic (struct command*,struct shallow_info*) ; 
 int /*<<< orphan*/  execute_commands_non_atomic (struct command*,struct shallow_info*) ; 
 int /*<<< orphan*/  finish_async (struct async*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  head_name ; 
 int /*<<< orphan*/  head_name_to_free ; 
 int /*<<< orphan*/  iterate_receive_command_list ; 
 int /*<<< orphan*/  memset (struct async*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  quiet ; 
 int /*<<< orphan*/  reject_updates_to_hidden (struct command*) ; 
 int /*<<< orphan*/  resolve_refdup (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ run_receive_hook (struct command*,char*,int /*<<< orphan*/ ,struct string_list const*) ; 
 int /*<<< orphan*/  set_connectivity_errors (struct command*,struct shallow_info*) ; 
 scalar_t__ shallow_update ; 
 int /*<<< orphan*/  start_async (struct async*) ; 
 int /*<<< orphan*/ * tmp_objdir ; 
 int /*<<< orphan*/  tmp_objdir_env (int /*<<< orphan*/ *) ; 
 scalar_t__ tmp_objdir_migrate (int /*<<< orphan*/ *) ; 
 scalar_t__ use_atomic ; 
 scalar_t__ use_sideband ; 
 int /*<<< orphan*/  warn_if_skipped_connectivity_check (struct command*,struct shallow_info*) ; 

__attribute__((used)) static void execute_commands(struct command *commands,
			     const char *unpacker_error,
			     struct shallow_info *si,
			     const struct string_list *push_options)
{
	struct check_connected_options opt = CHECK_CONNECTED_INIT;
	struct command *cmd;
	struct iterate_data data;
	struct async muxer;
	int err_fd = 0;

	if (unpacker_error) {
		for (cmd = commands; cmd; cmd = cmd->next)
			cmd->error_string = "unpacker error";
		return;
	}

	if (use_sideband) {
		memset(&muxer, 0, sizeof(muxer));
		muxer.proc = copy_to_sideband;
		muxer.in = -1;
		if (!start_async(&muxer))
			err_fd = muxer.in;
		/* ...else, continue without relaying sideband */
	}

	data.cmds = commands;
	data.si = si;
	opt.err_fd = err_fd;
	opt.progress = err_fd && !quiet;
	opt.env = tmp_objdir_env(tmp_objdir);
	if (check_connected(iterate_receive_command_list, &data, &opt))
		set_connectivity_errors(commands, si);

	if (use_sideband)
		finish_async(&muxer);

	reject_updates_to_hidden(commands);

	if (run_receive_hook(commands, "pre-receive", 0, push_options)) {
		for (cmd = commands; cmd; cmd = cmd->next) {
			if (!cmd->error_string)
				cmd->error_string = "pre-receive hook declined";
		}
		return;
	}

	/*
	 * Now we'll start writing out refs, which means the objects need
	 * to be in their final positions so that other processes can see them.
	 */
	if (tmp_objdir_migrate(tmp_objdir) < 0) {
		for (cmd = commands; cmd; cmd = cmd->next) {
			if (!cmd->error_string)
				cmd->error_string = "unable to migrate objects to permanent storage";
		}
		return;
	}
	tmp_objdir = NULL;

	check_aliased_updates(commands);

	free(head_name_to_free);
	head_name = head_name_to_free = resolve_refdup("HEAD", 0, NULL, NULL);

	if (use_atomic)
		execute_commands_atomic(commands, si);
	else
		execute_commands_non_atomic(commands, si);

	if (shallow_update)
		warn_if_skipped_connectivity_check(commands, si);
}