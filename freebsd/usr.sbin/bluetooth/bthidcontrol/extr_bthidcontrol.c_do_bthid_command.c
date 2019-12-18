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
struct bthid_command {int (* handler ) (int /*<<< orphan*/ ,int,char**) ;char* command; char* description; } ;
typedef  int /*<<< orphan*/  bdaddr_p ;

/* Variables and functions */
#define  ERROR 131 
#define  FAILED 130 
#define  OK 129 
#define  USAGE 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 struct bthid_command* find_bthid_command (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  hid_commands ; 
 int /*<<< orphan*/  print_bthid_command (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdp_commands ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,int,char**) ; 

__attribute__((used)) static int
do_bthid_command(bdaddr_p bdaddr, int argc, char **argv)
{
	char			*cmd = argv[0];
	struct bthid_command	*c = NULL;
	int			 e, help;

	help = 0;
	if (strcasecmp(cmd, "help") == 0) {
		argc --;
		argv ++;

		if (argc <= 0) {
			fprintf(stdout, "Supported commands:\n");
			print_bthid_command(sdp_commands);
			print_bthid_command(hid_commands);
			fprintf(stdout, "\nFor more information use " \
					"'help command'\n");

			return (OK);
		}

		help = 1;
		cmd = argv[0];
	}

	c = find_bthid_command(cmd, sdp_commands); 
	if (c == NULL)
		c = find_bthid_command(cmd, hid_commands); 

	if (c == NULL) {
		fprintf(stdout, "Unknown command: \"%s\"\n", cmd);
		return (ERROR);
	}

	if (!help)
		e = (c->handler)(bdaddr, -- argc, ++ argv);
	else
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