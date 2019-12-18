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
typedef  int op_mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
#define  FACTORY 130 
#define  NONE 129 
#define  SYSUPGRADE 128 
 int getopt (int,char**,char*) ; 
 char* optarg ; 
 int process_image (char*,char*,int) ; 
 int /*<<< orphan*/  usage (char*,int /*<<< orphan*/ ) ; 

int
main(int argc, char **argv)
{
	int 		opt;
	char 		*filename, *progname;
	op_mode_t	opmode = NONE;

	progname = argv[0];

	while ((opt = getopt(argc, argv,":s:f:h?")) != -1) {
		switch (opt) {
		case 's':
			opmode = SYSUPGRADE;
			filename = optarg;
			break;
		case 'f':
			opmode = FACTORY;
			filename = optarg;
			break;
		case 'h':
			opmode = NONE;
		default:
			usage(progname, EXIT_FAILURE);
			opmode = NONE;
		}
	}

	if(filename == NULL)
		opmode = NONE;

	switch (opmode) {
	case NONE:
		usage(progname, EXIT_FAILURE);
		break;
	case FACTORY:
	case SYSUPGRADE:
		return process_image(progname, filename, opmode);
		break;
	}

	return EXIT_SUCCESS;
}