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
struct g_command {int /*<<< orphan*/ * gc_name; } ;

/* Variables and functions */
 int GEOM_CLASS_CMDS ; 
 int GEOM_STD_CMDS ; 
 struct g_command* class_commands ; 
 struct g_command* std_commands ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static struct g_command *
find_command(const char *cmdstr, int flags)
{
	struct g_command *cmd;
	unsigned i;

	/*
	 * First try to find command defined by loaded library.
	 */
	if ((flags & GEOM_CLASS_CMDS) != 0 && class_commands != NULL) {
		for (i = 0; ; i++) {
			cmd = &class_commands[i];
			if (cmd->gc_name == NULL)
				break;
			if (strcmp(cmd->gc_name, cmdstr) == 0)
				return (cmd);
		}
	}
	/*
	 * Now try to find in standard commands.
	 */
	if ((flags & GEOM_STD_CMDS) != 0) {
		for (i = 0; ; i++) {
			cmd = &std_commands[i];
			if (cmd->gc_name == NULL)
				break;
			if (strcmp(cmd->gc_name, cmdstr) == 0)
				return (cmd);
		}
	}
	return (NULL);
}