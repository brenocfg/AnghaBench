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
struct sigaction {int /*<<< orphan*/  sa_handler; } ;
typedef  int speed_t ;
typedef  int /*<<< orphan*/  sa ;
typedef  int /*<<< orphan*/  p ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int FILENAME_MAX ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int LOG_NDELAY ; 
 int LOG_PID ; 
 int /*<<< orphan*/  LOG_USER ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  closelog () ; 
 scalar_t__ daemon (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  done ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int) ; 
 int getopt (int,char**,char*) ; 
 int getpid () ; 
 char* hcseriald ; 
 int /*<<< orphan*/  memset (struct sigaction*,int /*<<< orphan*/ ,int) ; 
 int open_device (char*,int,char*) ; 
 int /*<<< orphan*/  openlog (char*,int,int /*<<< orphan*/ ) ; 
 char* optarg ; 
 int /*<<< orphan*/  select (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sighandler ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int /*<<< orphan*/  usage (char*) ; 

int
main(int argc, char *argv[])
{
	char			*device = NULL, *name = NULL;
	speed_t			 speed = 115200;
	int			 n, detach = 1;
	char			 p[FILENAME_MAX];
	FILE			*f = NULL;
	struct sigaction	 sa;

	/* Process command line arguments */
	while ((n = getopt(argc, argv, "df:n:s:h")) != -1) {
		switch (n) {
		case 'd':
			detach = 0;
			break;

		case 'f':
			device = optarg;
			break;

		case 'n':
			name = optarg;
			break;

		case 's':
			speed = atoi(optarg);
			if (speed < 0)
				usage(argv[0]);
			break;

		case 'h':
		default:
			usage(argv[0]);
			break;
		}
	}

	if (device == NULL || name == NULL)
		usage(argv[0]);

	openlog(hcseriald, LOG_PID | LOG_NDELAY, LOG_USER);

	/* Open device */
	n = open_device(device, speed, name);

	if (detach && daemon(0, 0) < 0) {
		syslog(LOG_ERR, "Could not daemon(0, 0). %s (%d)",
			strerror(errno), errno);
		exit(1);
	}

	/* Write PID file */
	snprintf(p, sizeof(p), "/var/run/%s.%s.pid", hcseriald, name);
	f = fopen(p, "w");
	if (f == NULL) {
		syslog(LOG_ERR, "Could not fopen(%s). %s (%d)",
			p, strerror(errno), errno);
		exit(1);
	}
	fprintf(f, "%d", getpid());
	fclose(f);

	/* Install signal handler */
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = sighandler;

	if (sigaction(SIGTERM, &sa, NULL) < 0) {
		syslog(LOG_ERR, "Could not sigaction(SIGTERM). %s (%d)",
			strerror(errno), errno);
		exit(1);
	}

	if (sigaction(SIGHUP, &sa, NULL) < 0) {
		syslog(LOG_ERR, "Could not sigaction(SIGHUP). %s (%d)",
			strerror(errno), errno);
		exit(1);
	}

	if (sigaction(SIGINT, &sa, NULL) < 0) {
		syslog(LOG_ERR, "Could not sigaction(SIGINT). %s (%d)",
			strerror(errno), errno);
		exit(1);
	}

	/* Keep running */
	while (!done)
		select(0, NULL, NULL, NULL, NULL);

	/* Remove PID file and close device */
	unlink(p);
	close(n);
	closelog();

	return (0);
}