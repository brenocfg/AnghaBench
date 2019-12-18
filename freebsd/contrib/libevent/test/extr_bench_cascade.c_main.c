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
struct timeval {long tv_sec; int tv_usec; } ;
struct rlimit {int rlim_cur; int rlim_max; } ;
typedef  int /*<<< orphan*/  WSADATA ;

/* Variables and functions */
 int /*<<< orphan*/  RLIMIT_NOFILE ; 
 int /*<<< orphan*/  WSACleanup () ; 
 int /*<<< orphan*/  WSAStartup (int,int /*<<< orphan*/ *) ; 
 int atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_init () ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  perror (char*) ; 
 struct timeval* run_once (int) ; 
 int setrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

int
main(int argc, char **argv)
{
#ifdef HAVE_SETRLIMIT
	struct rlimit rl;
#endif
	int i, c;
	struct timeval *tv;

	int num_pipes = 100;
#ifdef _WIN32
	WSADATA WSAData;
	WSAStartup(0x101, &WSAData);
#endif

	while ((c = getopt(argc, argv, "n:")) != -1) {
		switch (c) {
		case 'n':
			num_pipes = atoi(optarg);
			break;
		default:
			fprintf(stderr, "Illegal argument \"%c\"\n", c);
			exit(1);
		}
	}

#ifdef HAVE_SETRLIMIT 
	rl.rlim_cur = rl.rlim_max = num_pipes * 2 + 50;
	if (setrlimit(RLIMIT_NOFILE, &rl) == -1) {
		perror("setrlimit");
		exit(1);
	}
#endif

	event_init();

	for (i = 0; i < 25; i++) {
		tv = run_once(num_pipes);
		if (tv == NULL)
			exit(1);
		fprintf(stdout, "%ld\n",
			tv->tv_sec * 1000000L + tv->tv_usec);
	}

#ifdef _WIN32
	WSACleanup();
#endif

	exit(0);
}