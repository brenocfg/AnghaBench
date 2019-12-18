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
 int EX_OK ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  ofw_close (int) ; 
 int /*<<< orphan*/  ofw_dump (int,char*,int,int,char*,int,int) ; 
 int ofw_open (int /*<<< orphan*/ ) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	int opt, i, fd;
	int aflag, pflag, rflag, Rflag, Sflag;
	char *Parg;

	aflag = pflag = rflag = Rflag = Sflag = 0;
	Parg = NULL;
	while ((opt = getopt(argc, argv, "-aprP:RS")) != -1) {
		if (opt == '-')
			break;
		switch (opt) {
		case 'a':
			aflag = 1;
			rflag = 1;
			break;
		case 'p':
			if (Parg != NULL)
				usage();
			pflag = 1;
			break;
		case 'r':
			rflag = 1;
			break;
		case 'P':
			if (pflag)
				usage();
			pflag = 1;
			Parg = optarg;
			break;
		case 'R':
			if (Sflag)
				usage();
			Rflag = 1;
			break;
		case 'S':
			if (Rflag)
				usage();
			Sflag = 1;
			break;
		case '?':
		default:
			usage();
			/* NOTREACHED */
		}
	}
	argc -= optind;
	argv += optind;

	fd = ofw_open(O_RDONLY);
	if (aflag) {
		if (argc != 0)
			usage();
		ofw_dump(fd, NULL, rflag, pflag, Parg, Rflag, Sflag);
	} else {
		/*
		 * For the sake of scripts, usage() is not called here if
		 * argc == 0.
		 */
		for (i = 0; i < argc; i++)
			ofw_dump(fd, argv[i], rflag, pflag, Parg, Rflag, Sflag);
	}
	ofw_close(fd);
	return (EX_OK);
}