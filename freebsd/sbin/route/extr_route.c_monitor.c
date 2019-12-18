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
typedef  int /*<<< orphan*/  time_t ;
struct rt_msghdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EX_USAGE ; 
#define  K_FIB 128 
 char* ctime (int /*<<< orphan*/ *) ; 
 scalar_t__ debugonly ; 
 int defaultfib ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  interfaces () ; 
 int keyword (char*) ; 
 int numfibs ; 
 int /*<<< orphan*/  print_rtmsg (struct rt_msghdr*,int) ; 
 int /*<<< orphan*/  printf (char*,int,char*) ; 
 int read (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  s ; 
 int set_sofib (int) ; 
 int strtol (char*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usage (char*) ; 
 int verbose ; 

__attribute__((used)) static void
monitor(int argc, char *argv[])
{
	int n, fib, error;
	char msg[2048], *endptr;

	fib = defaultfib;
	while (argc > 1) {
		argc--;
		argv++;
		if (**argv != '-')
			usage(*argv);
		switch (keyword(*argv + 1)) {
		case K_FIB:
			if (!--argc)
				usage(*argv);
			errno = 0;
			fib = strtol(*++argv, &endptr, 0);
			if (errno == 0) {
				if (*endptr != '\0' ||
				    fib < 0 ||
				    (numfibs != -1 && fib > numfibs - 1))
					errno = EINVAL;
			}
			if (errno)
				errx(EX_USAGE, "invalid fib number: %s", *argv);
			break;
		default:
			usage(*argv);
		}
	}
	error = set_sofib(fib);
	if (error)
		errx(EX_USAGE, "invalid fib number: %d", fib);

	verbose = 1;
	if (debugonly) {
		interfaces();
		exit(0);
	}
	for (;;) {
		time_t now;
		n = read(s, msg, 2048);
		now = time(NULL);
		(void)printf("\ngot message of size %d on %s", n, ctime(&now));
		print_rtmsg((struct rt_msghdr *)(void *)msg, n);
	}
}