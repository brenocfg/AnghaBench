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
struct command {struct command* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct command*) ; 

void
freecommands(struct command *cmd)
{
	struct command *next;

	while (cmd) {
		next = cmd->next;
		free(cmd);
		cmd = next;
	}
}