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

/* Variables and functions */
#define  CREATE 132 
#define  DESTROY 131 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  G_GATE_FLAG_READONLY ; 
 int /*<<< orphan*/  G_GATE_FLAG_WRITEONLY ; 
#define  LIST 130 
#define  RESCUE 129 
#define  UNSET 128 
 int action ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flags ; 
 int force ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  g_gate_close_device () ; 
 int /*<<< orphan*/  g_gate_destroy (int,int) ; 
 int /*<<< orphan*/  g_gate_list (int,int) ; 
 int /*<<< orphan*/  g_gate_load_module () ; 
 int /*<<< orphan*/  g_gate_open_device () ; 
 int g_gate_verbose ; 
 int /*<<< orphan*/  g_gatec_create () ; 
 int /*<<< orphan*/  g_gatec_rescue () ; 
 int getopt (int,char**,char*) ; 
 char* host ; 
 int /*<<< orphan*/  nagle ; 
 char* optarg ; 
 scalar_t__ optind ; 
 char* path ; 
 void* port ; 
 void* queue_size ; 
 void* rcvbuf ; 
 void* sectorsize ; 
 void* sndbuf ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 int strtol (char*,int /*<<< orphan*/ *,int) ; 
 void* strtoul (char*,int /*<<< orphan*/ *,int) ; 
 void* timeout ; 
 int unit ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{

	if (argc < 2)
		usage();
	if (strcasecmp(argv[1], "create") == 0)
		action = CREATE;
	else if (strcasecmp(argv[1], "destroy") == 0)
		action = DESTROY;
	else if (strcasecmp(argv[1], "list") == 0)
		action = LIST;
	else if (strcasecmp(argv[1], "rescue") == 0)
		action = RESCUE;
	else
		usage();
	argc -= 1;
	argv += 1;
	for (;;) {
		int ch;

		ch = getopt(argc, argv, "fno:p:q:R:S:s:t:u:v");
		if (ch == -1)
			break;
		switch (ch) {
		case 'f':
			if (action != DESTROY)
				usage();
			force = 1;
			break;
		case 'n':
			if (action != CREATE && action != RESCUE)
				usage();
			nagle = 0;
			break;
		case 'o':
			if (action != CREATE && action != RESCUE)
				usage();
			if (strcasecmp("ro", optarg) == 0)
				flags = G_GATE_FLAG_READONLY;
			else if (strcasecmp("wo", optarg) == 0)
				flags = G_GATE_FLAG_WRITEONLY;
			else if (strcasecmp("rw", optarg) == 0)
				flags = 0;
			else {
				errx(EXIT_FAILURE,
				    "Invalid argument for '-o' option.");
			}
			break;
		case 'p':
			if (action != CREATE && action != RESCUE)
				usage();
			errno = 0;
			port = strtoul(optarg, NULL, 10);
			if (port == 0 && errno != 0)
				errx(EXIT_FAILURE, "Invalid port.");
			break;
		case 'q':
			if (action != CREATE)
				usage();
			errno = 0;
			queue_size = strtoul(optarg, NULL, 10);
			if (queue_size == 0 && errno != 0)
				errx(EXIT_FAILURE, "Invalid queue_size.");
			break;
		case 'R':
			if (action != CREATE && action != RESCUE)
				usage();
			errno = 0;
			rcvbuf = strtoul(optarg, NULL, 10);
			if (rcvbuf == 0 && errno != 0)
				errx(EXIT_FAILURE, "Invalid rcvbuf.");
			break;
		case 'S':
			if (action != CREATE && action != RESCUE)
				usage();
			errno = 0;
			sndbuf = strtoul(optarg, NULL, 10);
			if (sndbuf == 0 && errno != 0)
				errx(EXIT_FAILURE, "Invalid sndbuf.");
			break;
		case 's':
			if (action != CREATE)
				usage();
			errno = 0;
			sectorsize = strtoul(optarg, NULL, 10);
			if (sectorsize == 0 && errno != 0)
				errx(EXIT_FAILURE, "Invalid sectorsize.");
			break;
		case 't':
			if (action != CREATE)
				usage();
			errno = 0;
			timeout = strtoul(optarg, NULL, 10);
			if (timeout == 0 && errno != 0)
				errx(EXIT_FAILURE, "Invalid timeout.");
			break;
		case 'u':
			errno = 0;
			unit = strtol(optarg, NULL, 10);
			if (unit == 0 && errno != 0)
				errx(EXIT_FAILURE, "Invalid unit number.");
			break;
		case 'v':
			if (action == DESTROY)
				usage();
			g_gate_verbose++;
			break;
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;

	switch (action) {
	case CREATE:
		if (argc != 2)
			usage();
		g_gate_load_module();
		g_gate_open_device();
		host = argv[0];
		path = argv[1];
		g_gatec_create();
		break;
	case DESTROY:
		if (unit == -1) {
			fprintf(stderr, "Required unit number.\n");
			usage();
		}
		g_gate_verbose = 1;
		g_gate_open_device();
		g_gate_destroy(unit, force);
		break;
	case LIST:
		g_gate_list(unit, g_gate_verbose);
		break;
	case RESCUE:
		if (argc != 2)
			usage();
		if (unit == -1) {
			fprintf(stderr, "Required unit number.\n");
			usage();
		}
		g_gate_open_device();
		host = argv[0];
		path = argv[1];
		g_gatec_rescue();
		break;
	case UNSET:
	default:
		usage();
	}
	g_gate_close_device();
	exit(EXIT_SUCCESS);
}