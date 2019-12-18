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
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  GEOM_CLASS_CMDS ; 
 struct g_command* class_commands ; 
 int /*<<< orphan*/ * class_name ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * find_command (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 struct g_command* std_commands ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  usage_command (struct g_command*,char const*) ; 

__attribute__((used)) static void
usage(void)
{

	if (class_name == NULL) {
		fprintf(stderr, "usage: geom <class> <command> [options]\n");
		fprintf(stderr, "       geom -p <provider-name>\n");
		fprintf(stderr, "       geom -t\n");
		exit(EXIT_FAILURE);
	} else {
		struct g_command *cmd;
		const char *prefix;
		unsigned i;

		prefix = "usage:";
		if (class_commands != NULL) {
			for (i = 0; ; i++) {
				cmd = &class_commands[i];
				if (cmd->gc_name == NULL)
					break;
				usage_command(cmd, prefix);
				prefix = "      ";
			}
		}
		for (i = 0; ; i++) {
			cmd = &std_commands[i];
			if (cmd->gc_name == NULL)
				break;
			/*
			 * If class defines command, which has the same name as
			 * standard command, skip it, because it was already
			 * shown on usage().
			 */
			if (find_command(cmd->gc_name, GEOM_CLASS_CMDS) != NULL)
				continue;
			usage_command(cmd, prefix);
			prefix = "      ";
		}
		exit(EXIT_FAILURE);
	}
}