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
struct shallow_info {scalar_t__* shallow_ref; } ;
struct command {size_t index; char* error_string; struct command* next; } ;
struct check_connected_options {int /*<<< orphan*/  env; } ;

/* Variables and functions */
 struct check_connected_options CHECK_CONNECTED_INIT ; 
 int /*<<< orphan*/  check_connected (int /*<<< orphan*/ ,struct command**,struct check_connected_options*) ; 
 int /*<<< orphan*/  command_singleton_iterator ; 
 scalar_t__ shallow_update ; 
 int /*<<< orphan*/  tmp_objdir ; 
 int /*<<< orphan*/  tmp_objdir_env (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_connectivity_errors(struct command *commands,
				    struct shallow_info *si)
{
	struct command *cmd;

	for (cmd = commands; cmd; cmd = cmd->next) {
		struct command *singleton = cmd;
		struct check_connected_options opt = CHECK_CONNECTED_INIT;

		if (shallow_update && si->shallow_ref[cmd->index])
			/* to be checked in update_shallow_ref() */
			continue;

		opt.env = tmp_objdir_env(tmp_objdir);
		if (!check_connected(command_singleton_iterator, &singleton,
				     &opt))
			continue;

		cmd->error_string = "missing necessary objects";
	}
}