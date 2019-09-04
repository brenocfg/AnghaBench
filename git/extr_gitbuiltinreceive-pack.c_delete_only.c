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
struct command {int /*<<< orphan*/  new_oid; struct command* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  is_null_oid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int delete_only(struct command *commands)
{
	struct command *cmd;
	for (cmd = commands; cmd; cmd = cmd->next) {
		if (!is_null_oid(&cmd->new_oid))
			return 0;
	}
	return 1;
}