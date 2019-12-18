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
struct object_id {int dummy; } ;
struct command {int /*<<< orphan*/  new_oid; } ;

/* Variables and functions */
 scalar_t__ is_null_oid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oidcpy (struct object_id*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int command_singleton_iterator(void *cb_data, struct object_id *oid)
{
	struct command **cmd_list = cb_data;
	struct command *cmd = *cmd_list;

	if (!cmd || is_null_oid(&cmd->new_oid))
		return -1; /* end of list */
	*cmd_list = NULL; /* this returns only one */
	oidcpy(oid, &cmd->new_oid);
	return 0;
}