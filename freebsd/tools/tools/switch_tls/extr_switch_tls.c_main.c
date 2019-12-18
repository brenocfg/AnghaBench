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
 int IFNET_TLS ; 
 int SW_TLS ; 
 int TCP_FUNCTION_NAME_LEN_MAX ; 
 int /*<<< orphan*/  exit (int) ; 
 char* findport (char*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 int tcpswitch_list_commands ; 
 int /*<<< orphan*/  tcpswitchall (char*,int) ; 
 int /*<<< orphan*/  tcpswitchbyname (char*,char*,char*,char*,int) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	char stack[TCP_FUNCTION_NAME_LEN_MAX];
	char *lport, *fport;
	bool switchall, switchallstack;
	int ch, mode;

	switchall = false;
	switchallstack = false;
	stack[0] = '\0';
	mode = SW_TLS;

	while ((ch = getopt(argc, argv, "ailS:s")) != -1) {
		switch (ch) {
		case 'a':
			switchall = true;
			break;
		case 'i':
			mode = IFNET_TLS;
			break;
		case 'l':
			tcpswitch_list_commands = true;
			break;
		case 'S':
			switchallstack = true;
			strlcpy(stack, optarg, sizeof(stack));
			break;
		case 's':
			mode = SW_TLS;
			break;
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;

	if (switchall && switchallstack)
		usage();
	if (switchall || switchallstack) {
		if (argc != 0)
			usage();
		if (!tcpswitchall(stack, mode))
			exit(1);
		exit(0);
	}

	if ((argc != 2 && argc != 4) || tcpswitch_list_commands)
		usage();

	if (argc == 2) {
		lport = findport(argv[0]);
		fport = findport(argv[1]);
		if (lport == NULL || lport[1] == '\0' || fport == NULL ||
		    fport[1] == '\0')
			usage();
		*lport++ = '\0';
		*fport++ = '\0';
		if (!tcpswitchbyname(argv[0], lport, argv[1], fport, mode))
			exit(1);
	} else if (!tcpswitchbyname(argv[0], argv[1], argv[2], argv[3], mode))
		exit(1);

	exit(0);
}