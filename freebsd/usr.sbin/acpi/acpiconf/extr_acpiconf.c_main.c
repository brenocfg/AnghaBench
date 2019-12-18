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
 int /*<<< orphan*/  EX_USAGE ; 
 int /*<<< orphan*/  acpi_battinfo (int) ; 
 int /*<<< orphan*/  acpi_init () ; 
 int /*<<< orphan*/  acpi_sleep (int) ; 
 int /*<<< orphan*/  acpi_sleep_ack (int) ; 
 int /*<<< orphan*/  acpifd ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 size_t strlen (char*) ; 
 int strtol (char*,char**,int) ; 
 int /*<<< orphan*/  usage (char*) ; 

int
main(int argc, char *argv[])
{
	char	*prog, *end;
	int	c, sleep_type, battery, ack;
	int	iflag = 0, kflag = 0, sflag = 0;

	prog = argv[0];
	if (argc < 2)
		usage(prog);
		/* NOTREACHED */

	sleep_type = -1;
	acpi_init();
	while ((c = getopt(argc, argv, "hi:k:s:")) != -1) {
		switch (c) {
		case 'i':
			iflag = 1;
			battery = strtol(optarg, &end, 10);
			if ((size_t)(end - optarg) != strlen(optarg))
			    errx(EX_USAGE, "invalid battery");
			break;
		case 'k':
			kflag = 1;
			ack = strtol(optarg, &end, 10);
			if ((size_t)(end - optarg) != strlen(optarg))
			    errx(EX_USAGE, "invalid ack argument");
			break;
		case 's':
			sflag = 1;
			if (optarg[0] == 'S')
				optarg++;
			sleep_type = strtol(optarg, &end, 10);
			if ((size_t)(end - optarg) != strlen(optarg))
			    errx(EX_USAGE, "invalid sleep type");
			if (sleep_type < 1 || sleep_type > 4)
				errx(EX_USAGE, "invalid sleep type (%d)",
				     sleep_type);
			break;
		case 'h':
		default:
			usage(prog);
			/* NOTREACHED */
		}
	}
	argc -= optind;
	argv += optind;

	if (iflag != 0 && kflag != 0 && sflag != 0)
			errx(EX_USAGE, "-i, -k and -s are mutually exclusive");

	if (iflag  != 0) {
		if (kflag != 0)
			errx(EX_USAGE, "-i and -k are mutually exclusive");
		if (sflag != 0)
			errx(EX_USAGE, "-i and -s are mutually exclusive");
		acpi_battinfo(battery);
	}

	if (kflag != 0) {
		if (sflag != 0)
			errx(EX_USAGE, "-k and -s are mutually exclusive");
		acpi_sleep_ack(ack);
	}


	if (sflag != 0)
		acpi_sleep(sleep_type);

	close(acpifd);
	exit (0);
}