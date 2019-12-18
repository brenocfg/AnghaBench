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
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 int mflag ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  regress () ; 
 int rflag ; 
 int sflag ; 
 int tflag ; 
 int /*<<< orphan*/  timetest () ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char **argv)
{
	int ch;

	while ((ch = getopt(argc, argv, "mrst")) != -1)
		switch (ch) {
		case 'm':
			mflag = 1;
			break;
		case 'r':
			rflag = 1;
			break;
		case 's':
			sflag = 1;
			break;
		case 't':
			tflag = 1;
			break;
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;
	if (argc > 0)
		usage();

	if (!(mflag || sflag))
		mflag = 1;

	if ((mflag ^ sflag) != 1)
		usage();

	if ((tflag ^ rflag) != 1)
		usage();

	if (tflag)
		timetest();

	if (rflag)
		regress();
	
	exit(0);
	
}