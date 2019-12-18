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
struct hci_command {int (* handler ) (int,int,char**) ;char* command; char* description; } ;

/* Variables and functions */
#define  ERROR 131 
#define  FAILED 130 
#define  OK 129 
#define  USAGE 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 struct hci_command* find_hci_command (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  host_controller_baseband_commands ; 
 int /*<<< orphan*/  info_commands ; 
 int /*<<< orphan*/  le_commands ; 
 int /*<<< orphan*/  link_control_commands ; 
 int /*<<< orphan*/  link_policy_commands ; 
 int /*<<< orphan*/  node_commands ; 
 int /*<<< orphan*/  print_hci_command (int /*<<< orphan*/ ) ; 
 int socket_open (char const*) ; 
 int /*<<< orphan*/  status_commands ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int stub1 (int,int,char**) ; 

__attribute__((used)) static int
do_hci_command(char const *node, int argc, char **argv)
{
	char			*cmd = argv[0];
	struct hci_command	*c = NULL;
	int			 s, e, help;
	
	help = 0;
	if (strcasecmp(cmd, "help") == 0) {
		argc --;
		argv ++;

		if (argc <= 0) {
			fprintf(stdout, "Supported commands:\n");
			print_hci_command(link_control_commands);
			print_hci_command(link_policy_commands);
			print_hci_command(host_controller_baseband_commands);
			print_hci_command(info_commands);
			print_hci_command(status_commands);
			print_hci_command(le_commands);
			print_hci_command(node_commands);
			fprintf(stdout, "\nFor more information use " \
				"'help command'\n");

			return (OK);
		}

		help = 1;
		cmd = argv[0];
	}

	c = find_hci_command(cmd, link_control_commands);
	if (c != NULL)
		goto execute;

	c = find_hci_command(cmd, link_policy_commands);
	if (c != NULL)
		goto execute;

	c = find_hci_command(cmd, host_controller_baseband_commands);
	if (c != NULL)
		goto execute;

	c = find_hci_command(cmd, info_commands);
	if (c != NULL)
		goto execute;

	c = find_hci_command(cmd, status_commands);
	if (c != NULL)
		goto execute;

	c = find_hci_command(cmd, le_commands);
	if (c != NULL)
		goto execute;

	
	c = find_hci_command(cmd, node_commands);
	if (c == NULL) {
		fprintf(stdout, "Unknown command: \"%s\"\n", cmd);
		return (ERROR);
	}
execute:
	if (!help) {
		s = socket_open(node);
		e = (c->handler)(s, -- argc, ++ argv);
		close(s);
	} else
		e = USAGE;

	switch (e) {
	case OK:
	case FAILED:
		break;

	case ERROR:
		fprintf(stdout, "Could not execute command \"%s\". %s\n",
			cmd, strerror(errno));
		break;

	case USAGE:
		fprintf(stdout, "Usage: %s\n%s\n", c->command, c->description);
		break;

	default: assert(0); break;
	}


	return (e);
}