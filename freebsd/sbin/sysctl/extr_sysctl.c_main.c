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
 int /*<<< orphan*/  Bflag ; 
 int /*<<< orphan*/  LC_NUMERIC ; 
 int Nflag ; 
 int Tflag ; 
 int Wflag ; 
 int aflag ; 
 int bflag ; 
 int /*<<< orphan*/ * conffile ; 
 int dflag ; 
 int eflag ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 int hflag ; 
 int iflag ; 
 int nflag ; 
 int oflag ; 
 int /*<<< orphan*/ * optarg ; 
 scalar_t__ optind ; 
 scalar_t__ parse (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ parsefile (int /*<<< orphan*/ *) ; 
 int qflag ; 
 int /*<<< orphan*/  setbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strtol (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysctl_all (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tflag ; 
 int /*<<< orphan*/  usage () ; 
 int xflag ; 

int
main(int argc, char **argv)
{
	int ch;
	int warncount = 0;

	setlocale(LC_NUMERIC, "");
	setbuf(stdout,0);
	setbuf(stderr,0);

	while ((ch = getopt(argc, argv, "AabB:def:hiNnoqtTwWxX")) != -1) {
		switch (ch) {
		case 'A':
			/* compatibility */
			aflag = oflag = 1;
			break;
		case 'a':
			aflag = 1;
			break;
		case 'b':
			bflag = 1;
			break;
		case 'B':
			Bflag = strtol(optarg, NULL, 0);
			break;
		case 'd':
			dflag = 1;
			break;
		case 'e':
			eflag = 1;
			break;
		case 'f':
			conffile = optarg;
			break;
		case 'h':
			hflag = 1;
			break;
		case 'i':
			iflag = 1;
			break;
		case 'N':
			Nflag = 1;
			break;
		case 'n':
			nflag = 1;
			break;
		case 'o':
			oflag = 1;
			break;
		case 'q':
			qflag = 1;
			break;
		case 't':
			tflag = 1;
			break;
		case 'T':
			Tflag = 1;
			break;
		case 'w':
			/* compatibility */
			/* ignored */
			break;
		case 'W':
			Wflag = 1;
			break;
		case 'X':
			/* compatibility */
			aflag = xflag = 1;
			break;
		case 'x':
			xflag = 1;
			break;
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;

	if (Nflag && nflag)
		usage();
	if (aflag && argc == 0)
		exit(sysctl_all(0, 0));
	if (argc == 0 && conffile == NULL)
		usage();

	warncount = 0;
	if (conffile != NULL)
		warncount += parsefile(conffile);

	while (argc-- > 0)
		warncount += parse(*argv++, 0);

	return (warncount);
}