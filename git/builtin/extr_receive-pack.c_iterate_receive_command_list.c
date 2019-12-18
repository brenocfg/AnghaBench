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
struct object_id {int dummy; } ;
struct iterate_data {TYPE_1__* si; struct command* cmds; } ;
struct command {size_t index; struct command* next; int /*<<< orphan*/  new_oid; int /*<<< orphan*/  skip_update; } ;
struct TYPE_2__ {scalar_t__* shallow_ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  is_null_oid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oidcpy (struct object_id*,int /*<<< orphan*/ *) ; 
 scalar_t__ shallow_update ; 

__attribute__((used)) static int iterate_receive_command_list(void *cb_data, struct object_id *oid)
{
	struct iterate_data *data = cb_data;
	struct command **cmd_list = &data->cmds;
	struct command *cmd = *cmd_list;

	for (; cmd; cmd = cmd->next) {
		if (shallow_update && data->si->shallow_ref[cmd->index])
			/* to be checked in update_shallow_ref() */
			continue;
		if (!is_null_oid(&cmd->new_oid) && !cmd->skip_update) {
			oidcpy(oid, &cmd->new_oid);
			*cmd_list = cmd->next;
			return 0;
		}
	}
	*cmd_list = NULL;
	return -1; /* end of list */
}