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
struct command_map_entry {int (* fn ) (int,char**) ;int /*<<< orphan*/  silent; } ;

/* Variables and functions */
 int /*<<< orphan*/ * be ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 struct command_map_entry* get_cmd_info (char const*) ; 
 int /*<<< orphan*/  libbe_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * libbe_init (char*) ; 
 int /*<<< orphan*/  libbe_print_on_error (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char const*,char*) ; 
 char* strdup (char*) ; 
 int stub1 (int,char**) ; 
 int usage (int) ; 

int
main(int argc, char *argv[])
{
	struct command_map_entry *cmd;
	const char *command;
	char *root;
	int rc;

	cmd = NULL;
	root = NULL;
	if (argc < 2)
		return (usage(false));

	if (strcmp(argv[1], "-r") == 0) {
		if (argc < 4)
			return (usage(false));
		root = strdup(argv[2]);
		command = argv[3];
		argc -= 3;
		argv += 3;
	} else {
		command = argv[1];
		argc -= 1;
		argv += 1;
	}

	/* Handle command aliases */
	if (strcmp(command, "umount") == 0)
		command = "unmount";

	if (strcmp(command, "ujail") == 0)
		command = "unjail";

	if ((strcmp(command, "-?") == 0) || (strcmp(command, "-h") == 0))
		return (usage(true));

	if ((cmd = get_cmd_info(command)) == NULL) {
		fprintf(stderr, "unknown command: %s\n", command);
		return (usage(false));
	}

	if ((be = libbe_init(root)) == NULL)
		return (-1);

	libbe_print_on_error(be, !cmd->silent);

	rc = cmd->fn(argc, argv);

	libbe_close(be);
	return (rc);
}