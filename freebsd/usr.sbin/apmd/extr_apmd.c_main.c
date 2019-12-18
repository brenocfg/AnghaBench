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
 int APM_CTL_DEVICEFILE ; 
 int APM_NORM_DEVICEFILE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  F_SETFD ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  LOG_DAEMON ; 
 int LOG_NDELAY ; 
 int /*<<< orphan*/  LOG_NOTICE ; 
 int LOG_PERROR ; 
 int LOG_PID ; 
 int /*<<< orphan*/  NICE_INCR ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  O_RDWR ; 
 int apmctl_fd ; 
 int /*<<< orphan*/  apmd_configfile ; 
 int apmnorm_fd ; 
 int /*<<< orphan*/  daemon (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_level ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  event_loop () ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int fcntl (int,int /*<<< orphan*/ ,int) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  nice (int /*<<< orphan*/ ) ; 
 int open (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  openlog (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ pipe (int*) ; 
 int /*<<< orphan*/  restart () ; 
 int* signal_fd ; 
 int soft_power_state_change ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 
 int verbose ; 
 int /*<<< orphan*/  write_pid () ; 

int
main(int ac, char* av[])
{
	int	ch;
	int	daemonize = 1;
	char	*prog;
	int	logopt = LOG_NDELAY | LOG_PID;

	while ((ch = getopt(ac, av, "df:sv")) != -1) {
		switch (ch) {
		case 'd':
			daemonize = 0;
			debug_level++;
			break;
		case 'f':
			apmd_configfile = optarg;
			break;
		case 's':
			soft_power_state_change = 1;
			break;
		case 'v':
			verbose = 1;
			break;
		default:
			err(1, "unknown option `%c'", ch);
		}
	}

	if (daemonize)
		daemon(0, 0);

#ifdef NICE_INCR
	nice(NICE_INCR);
#endif

	if (!daemonize)
		logopt |= LOG_PERROR;

	prog = strrchr(av[0], '/');
	openlog(prog ? prog+1 : av[0], logopt, LOG_DAEMON);

	syslog(LOG_NOTICE, "start");

	if (pipe(signal_fd) < 0)
		err(1, "pipe");
	if (fcntl(signal_fd[0], F_SETFL, O_NONBLOCK) < 0)
		err(1, "fcntl");

	if ((apmnorm_fd = open(APM_NORM_DEVICEFILE, O_RDWR)) == -1) {
		err(1, "cannot open device file `%s'", APM_NORM_DEVICEFILE);
	}

	if (fcntl(apmnorm_fd, F_SETFD, 1) == -1) {
		err(1, "cannot set close-on-exec flag for device file '%s'", APM_NORM_DEVICEFILE);
	}

	if ((apmctl_fd = open(APM_CTL_DEVICEFILE, O_RDWR)) == -1) {
		err(1, "cannot open device file `%s'", APM_CTL_DEVICEFILE);
	}

	if (fcntl(apmctl_fd, F_SETFD, 1) == -1) {
		err(1, "cannot set close-on-exec flag for device file '%s'", APM_CTL_DEVICEFILE);
	}

	restart();
	write_pid();
	event_loop();
	exit(EXIT_SUCCESS);
}