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
typedef  int key_t ;

/* Variables and functions */
 int IPC_PRIVATE ; 
 int /*<<< orphan*/  IPC_TO_STR (int) ; 
 int /*<<< orphan*/  IPC_TO_STRING (int) ; 
 int /*<<< orphan*/  SIGSYS ; 
 int atoi (int /*<<< orphan*/ ) ; 
 int atol (int /*<<< orphan*/ ) ; 
 scalar_t__ errflg ; 
 int /*<<< orphan*/  exit (scalar_t__) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int getopt (int,char**,char*) ; 
 int msgrm (int,int) ; 
 int /*<<< orphan*/  not_configured ; 
 int /*<<< orphan*/  optarg ; 
 int optind ; 
 int optopt ; 
 int /*<<< orphan*/  rmverbose ; 
 int semrm (int,int) ; 
 int shmrm (int,int) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ signaled ; 
 int /*<<< orphan*/  stderr ; 
 int toupper (int) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  use_sysctl ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

int
main(int argc, char *argv[])
{
	int c, result, target_id;
	key_t target_key;

	while ((c = getopt(argc, argv, "q:m:s:Q:M:S:vWy")) != -1) {

		signaled = 0;
		switch (c) {
		case 'v':
			rmverbose++;
			break;
		case 'y':
			use_sysctl = 0;
			break;
		}
	}

	optind = 1;
	errflg = 0;
	signal(SIGSYS, not_configured);
	while ((c = getopt(argc, argv, "q:m:s:Q:M:S:vWy")) != -1) {

		signaled = 0;
		switch (c) {
		case 'q':
		case 'm':
		case 's':
			target_id = atoi(optarg);
			if (c == 'q')
				result = msgrm(0, target_id);
			else if (c == 'm')
				result = shmrm(0, target_id);
			else
				result = semrm(0, target_id);
			if (result < 0) {
				errflg++;
				if (!signaled)
					warn("%sid(%d): ",
					    IPC_TO_STR(toupper(c)), target_id);
				else
					warnx(
					    "%ss are not configured "
					    "in the running kernel",
					    IPC_TO_STRING(toupper(c)));
			}
			break;
		case 'Q':
		case 'M':
		case 'S':
			target_key = atol(optarg);
			if (target_key == IPC_PRIVATE) {
				warnx("can't remove private %ss",
				    IPC_TO_STRING(c));
				continue;
			}
			if (c == 'Q')
				result = msgrm(target_key, 0);
			else if (c == 'M')
				result = shmrm(target_key, 0);
			else
				result = semrm(target_key, 0);
			if (result < 0) {
				errflg++;
				if (!signaled)
					warn("%ss(%ld): ",
					    IPC_TO_STR(c), target_key);
				else
					warnx("%ss are not configured "
					    "in the running kernel",
					    IPC_TO_STRING(c));
			}
			break;
		case 'v':
		case 'y':
			/* Handled in other getopt() loop */
			break;
		case 'W':
			msgrm(-1, 0);
			shmrm(-1, 0);
			semrm(-1, 0);
			break;
		case ':':
			fprintf(stderr,
			    "option -%c requires an argument\n", optopt);
			usage();
		case '?':
			fprintf(stderr, "unrecognized option: -%c\n", optopt);
			usage();
		}
	}

	if (optind != argc) {
		fprintf(stderr, "unknown argument: %s\n", argv[optind]);
		usage();
	}
	exit(errflg);
}