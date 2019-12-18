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
struct command {size_t index; int /*<<< orphan*/  ref_name; struct command* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ should_process_cmd (struct command*) ; 

__attribute__((used)) static void warn_if_skipped_connectivity_check(struct command *commands,
					       struct shallow_info *si)
{
	struct command *cmd;
	int checked_connectivity = 1;

	for (cmd = commands; cmd; cmd = cmd->next) {
		if (should_process_cmd(cmd) && si->shallow_ref[cmd->index]) {
			error("BUG: connectivity check has not been run on ref %s",
			      cmd->ref_name);
			checked_connectivity = 0;
		}
	}
	if (!checked_connectivity)
		BUG("connectivity check skipped???");
}