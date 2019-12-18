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
typedef  int /*<<< orphan*/  stack ;

/* Variables and functions */
 int TCPS_CLOSED ; 
 int TCPS_LISTEN ; 
 int TCP_FUNCTION_NAME_LEN_MAX ; 
 int TCP_NSTATES ; 
 int /*<<< orphan*/  exit (int) ; 
 char* findport (char*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 int tcpdrop_list_commands ; 
 int /*<<< orphan*/  tcpdropall (char*,int) ; 
 int /*<<< orphan*/  tcpdropbyname (char*,char*,char*,char*) ; 
 int /*<<< orphan*/ * tcpstates ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	char stack[TCP_FUNCTION_NAME_LEN_MAX];
	char *lport, *fport;
	bool dropall, dropallstack;
	int ch, state;

	dropall = false;
	dropallstack = false;
	stack[0] = '\0';
	state = -1;

	while ((ch = getopt(argc, argv, "alS:s:")) != -1) {
		switch (ch) {
		case 'a':
			dropall = true;
			break;
		case 'l':
			tcpdrop_list_commands = true;
			break;
		case 'S':
			dropallstack = true;
			strlcpy(stack, optarg, sizeof(stack));
			break;
		case 's':
			dropallstack = true;
			for (state = 0; state < TCP_NSTATES; state++) {
				if (strcmp(tcpstates[state], optarg) == 0)
					break;
			}
			break;
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;

	if (state == TCP_NSTATES ||
	    state == TCPS_CLOSED ||
	    state == TCPS_LISTEN)
		usage();
	if (dropall && dropallstack)
		usage();
	if (dropall || dropallstack) {
		if (argc != 0)
			usage();
		if (!tcpdropall(stack, state))
			exit(1);
		exit(0);
	}

	if ((argc != 2 && argc != 4) || tcpdrop_list_commands)
		usage();

	if (argc == 2) {
		lport = findport(argv[0]);
		fport = findport(argv[1]);
		if (lport == NULL || lport[1] == '\0' || fport == NULL ||
		    fport[1] == '\0')
			usage();
		*lport++ = '\0';
		*fport++ = '\0';
		if (!tcpdropbyname(argv[0], lport, argv[1], fport))
			exit(1);
	} else if (!tcpdropbyname(argv[0], argv[1], argv[2], argv[3]))
		exit(1);

	exit(0);
}