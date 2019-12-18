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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  EDIT 133 
 int /*<<< orphan*/  O_RDONLY ; 
#define  READ 132 
#define  RESTORE 131 
#define  UNSPEC 130 
#define  WRITE 129 
#define  WRITEBOOT 128 
 int allfields ; 
 int bbsize ; 
 int checklabel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int) ; 
 int disable_write ; 
 int /*<<< orphan*/  display (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int edit () ; 
 int /*<<< orphan*/  err (int,char*,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fixlabel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 char* g_device_path (char*) ; 
 int /*<<< orphan*/ * g_providername (int) ; 
 int /*<<< orphan*/  getasciilabel (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ installboot ; 
 int is_file ; 
 int /*<<< orphan*/  lab ; 
 scalar_t__ labeloffset ; 
 scalar_t__ labelsoffset ; 
 int /*<<< orphan*/  makelabel (char const*,int /*<<< orphan*/ *) ; 
 int op ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/ * pname ; 
 int /*<<< orphan*/  readlabel (int) ; 
 char* specname ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warn (char*,char*) ; 
 int writelabel () ; 
 int /*<<< orphan*/  xxboot ; 

int
main(int argc, char *argv[])
{
	FILE *t;
	int ch, error, fd;
	const char *name;
	
	error = 0;
	name = NULL;

	while ((ch = getopt(argc, argv, "ABb:efm:nRrw")) != -1)
		switch (ch) {
			case 'A':
				allfields = 1;
				break;
			case 'B':
				++installboot;
				break;
			case 'b':
				xxboot = optarg;
				break;
			case 'f':
				is_file=1;
				break;
			case 'm':
				if (!strcmp(optarg, "i386") ||
				    !strcmp(optarg, "amd64")) {
					labelsoffset = 1;
					labeloffset = 0;
					bbsize = 8192;
				} else {
					errx(1, "Unsupported architecture");
				}
				break;
			case 'n':
				disable_write = 1;
				break;
			case 'R':
				if (op != UNSPEC)
					usage();
				op = RESTORE;
				break;
			case 'e':
				if (op != UNSPEC)
					usage();
				op = EDIT;
				break;
			case 'r':
				/*
				 * We accept and ignore -r for compatibility with
				 * historical disklabel usage.
				 */
				break;
			case 'w':
				if (op != UNSPEC)
					usage();
				op = WRITE;
				break;
			case '?':
			default:
				usage();
		}
	argc -= optind;
	argv += optind;

	if (argc < 1)
		usage();
	if (labelsoffset < 0 || labeloffset < 0)
		errx(1, "a -m <architecture> option must be specified");

	/* Figure out the names of the thing we're working on */
	if (is_file) {
		specname = argv[0];
	} else {
		specname = g_device_path(argv[0]);
		if (specname == NULL) {
			warn("unable to get correct path for %s", argv[0]);
			return(1);
		}
		fd = open(specname, O_RDONLY);
		if (fd < 0) {
			warn("error opening %s", specname);
			return(1);
		}
		pname = g_providername(fd);
		if (pname == NULL) {
			warn("error getting providername for %s", specname);
			close(fd);
			return(1);
		}
		close(fd);
	}

	if (installboot && op == UNSPEC)
		op = WRITEBOOT;
	else if (op == UNSPEC)
		op = READ;

	switch(op) {

	case UNSPEC:
		break;

	case EDIT:
		if (argc != 1)
			usage();
		readlabel(1);
		fixlabel(&lab);
		error = edit();
		break;

	case READ:
		if (argc != 1)
			usage();
		readlabel(1);
		display(stdout, NULL);
		error = checklabel(NULL);
		break;

	case RESTORE:
		if (argc != 2)
			usage();
		if (!(t = fopen(argv[1], "r")))
			err(4, "fopen %s", argv[1]);
		readlabel(0);
		if (!getasciilabel(t, &lab))
			exit(1);
		error = writelabel();
		break;

	case WRITE:
		if (argc == 2)
			name = argv[1];
		else if (argc == 1)
			name = "auto";
		else
			usage();
		readlabel(0);
		makelabel(name, &lab);
		fixlabel(&lab);
		if (checklabel(NULL) == 0)
			error = writelabel();
		break;

	case WRITEBOOT:

		readlabel(1);
		fixlabel(&lab);
		if (argc == 2)
			makelabel(argv[1], &lab);
		if (checklabel(NULL) == 0)
			error = writelabel();
		break;
	}
	exit(error);
}