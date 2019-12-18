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
 scalar_t__ ENOENT ; 
 scalar_t__ asprintf (char**,char*,char*) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  execvp (char*,char**) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ isdigit (unsigned char) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 scalar_t__ setfib (int) ; 
 long strtol (char*,char**,int) ; 
 int sysctlbyname (char*,int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warn (char*) ; 

int
main(int argc, char *argv[])
{
	long fib = 0;
	int ch;
	char *ep;
	int	numfibs;
	size_t intsize = sizeof(int);

        if (sysctlbyname("net.fibs", &numfibs, &intsize, NULL, 0) == -1)
		errx(1, "Multiple FIBS not supported");
	if (argc < 2)
		usage();
	ep = argv[1];
	/*
	 * convert -N or N to -FN. (N is a number)
	 */
	if (ep[0]== '-' && isdigit((unsigned char)ep[1]))
		ep++;
	if (isdigit((unsigned char)*ep))
               if (asprintf(&argv[1], "-F%s", ep) < 0)
                        err(1, "asprintf");

	while ((ch = getopt(argc, argv, "F:")) != -1) {
		switch (ch) {
		case 'F':
			errno = 0;
			fib = strtol(optarg, &ep, 10);
			if (ep == optarg || *ep != '\0' || errno ||
			    fib < 0 || fib >= numfibs)
				errx(1, "%s: invalid FIB (max %d)",
				    optarg, numfibs - 1);
			break;
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;

	if (argc == 0)
		usage();

	errno = 0;
	if (setfib((int)fib))
		warn("setfib");
	execvp(*argv, argv);
	err(errno == ENOENT ? 127 : 126, "%s", *argv);
}