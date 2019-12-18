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
typedef  int uint64_t ;
typedef  int u_int ;
struct timeval {int tv_sec; int tv_usec; } ;
struct pidfh {int dummy; } ;
typedef  int pid_t ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  curfreq ;

/* Variables and functions */
 int DEFAULT_ACTIVE_PERCENT ; 
 int DEFAULT_IDLE_PERCENT ; 
 int DEFAULT_POLL_INTERVAL ; 
 scalar_t__ EEXIST ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int EX_UNAVAILABLE ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int MODE_ADAPTIVE ; 
 int MODE_HIADAPTIVE ; 
 int MODE_MAX ; 
 int MODE_MIN ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
#define  SRC_AC 130 
#define  SRC_BATTERY 129 
#define  SRC_UNKNOWN 128 
 int /*<<< orphan*/  acline_init () ; 
 int /*<<< orphan*/  acline_read () ; 
 int acline_status ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  cp_times_mib ; 
 int cpu_idle_mark ; 
 int cpu_running_mark ; 
 scalar_t__ daemon (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devd_close () ; 
 int devd_pipe ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ exit_requested ; 
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/  freq_mib ; 
 int get_freq () ; 
 size_t get_freq_id (int,int*,int) ; 
 scalar_t__ geteuid () ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  handle_sigs ; 
 int /*<<< orphan*/  levels_mib ; 
 char** modes ; 
 char* optarg ; 
 int /*<<< orphan*/  parse_acline_mode (char*,int) ; 
 int /*<<< orphan*/  parse_mode (char*,int*,int) ; 
 struct pidfh* pidfile_open (char const*,int,int*) ; 
 int /*<<< orphan*/  pidfile_remove (struct pidfh*) ; 
 int /*<<< orphan*/  pidfile_write (struct pidfh*) ; 
 int poll_ival ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ read_freqs (int*,int**,int**,int,int) ; 
 scalar_t__ read_usage_times (int*) ; 
 int /*<<< orphan*/  select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 scalar_t__ set_freq (int) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sysctl (int /*<<< orphan*/ ,int,int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sysctlnametomib (char*,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  usage () ; 
 int vflag ; 
 int /*<<< orphan*/  warn (char*,...) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

int
main(int argc, char * argv[])
{
	struct timeval timeout;
	fd_set fdset;
	int nfds;
	struct pidfh *pfh = NULL;
	const char *pidfile = NULL;
	int freq, curfreq, initfreq, *freqs, i, j, *mwatts, numfreqs, load;
	int minfreq = -1, maxfreq = -1;
	int ch, mode, mode_ac, mode_battery, mode_none, idle, to;
	uint64_t mjoules_used;
	size_t len;

	/* Default mode for all AC states is adaptive. */
	mode_ac = mode_none = MODE_HIADAPTIVE;
	mode_battery = MODE_ADAPTIVE;
	cpu_running_mark = DEFAULT_ACTIVE_PERCENT;
	cpu_idle_mark = DEFAULT_IDLE_PERCENT;
	poll_ival = DEFAULT_POLL_INTERVAL;
	mjoules_used = 0;
	vflag = 0;

	/* User must be root to control frequencies. */
	if (geteuid() != 0)
		errx(1, "must be root to run");

	while ((ch = getopt(argc, argv, "a:b:i:m:M:n:p:P:r:s:v")) != -1)
		switch (ch) {
		case 'a':
			parse_mode(optarg, &mode_ac, ch);
			break;
		case 'b':
			parse_mode(optarg, &mode_battery, ch);
			break;
		case 's':
			parse_acline_mode(optarg, ch);
			break;
		case 'i':
			cpu_idle_mark = atoi(optarg);
			if (cpu_idle_mark < 0 || cpu_idle_mark > 100) {
				warnx("%d is not a valid percent",
				    cpu_idle_mark);
				usage();
			}
			break;
		case 'm':
			minfreq = atoi(optarg);
			if (minfreq < 0) {
				warnx("%d is not a valid CPU frequency",
				    minfreq);
				usage();
			}
			break;
		case 'M':
			maxfreq = atoi(optarg);
			if (maxfreq < 0) {
				warnx("%d is not a valid CPU frequency",
				    maxfreq);
				usage();
			}
			break;
		case 'n':
			parse_mode(optarg, &mode_none, ch);
			break;
		case 'p':
			poll_ival = atoi(optarg);
			if (poll_ival < 5) {
				warnx("poll interval is in units of ms");
				usage();
			}
			break;
		case 'P':
			pidfile = optarg;
			break;
		case 'r':
			cpu_running_mark = atoi(optarg);
			if (cpu_running_mark <= 0 || cpu_running_mark > 100) {
				warnx("%d is not a valid percent",
				    cpu_running_mark);
				usage();
			}
			break;
		case 'v':
			vflag = 1;
			break;
		default:
			usage();
		}

	mode = mode_none;

	/* Poll interval is in units of ms. */
	poll_ival *= 1000;

	/* Look up various sysctl MIBs. */
	len = 2;
	if (sysctlnametomib("kern.cp_times", cp_times_mib, &len))
		err(1, "lookup kern.cp_times");
	len = 4;
	if (sysctlnametomib("dev.cpu.0.freq", freq_mib, &len))
		err(EX_UNAVAILABLE, "no cpufreq(4) support -- aborting");
	len = 4;
	if (sysctlnametomib("dev.cpu.0.freq_levels", levels_mib, &len))
		err(1, "lookup freq_levels");

	/* Check if we can read the load and supported freqs. */
	if (read_usage_times(NULL))
		err(1, "read_usage_times");
	if (read_freqs(&numfreqs, &freqs, &mwatts, minfreq, maxfreq))
		err(1, "error reading supported CPU frequencies");
	if (numfreqs == 0)
		errx(1, "no CPU frequencies in user-specified range");

	/* Run in the background unless in verbose mode. */
	if (!vflag) {
		pid_t otherpid;

		pfh = pidfile_open(pidfile, 0600, &otherpid);
		if (pfh == NULL) {
			if (errno == EEXIST) {
				errx(1, "powerd already running, pid: %d",
				    otherpid);
			}
			warn("cannot open pid file");
		}
		if (daemon(0, 0) != 0) {
			warn("cannot enter daemon mode, exiting");
			pidfile_remove(pfh);
			exit(EXIT_FAILURE);

		}
		pidfile_write(pfh);
	}

	/* Decide whether to use ACPI or APM to read the AC line status. */
	acline_init();

	/*
	 * Exit cleanly on signals.
	 */
	signal(SIGINT, handle_sigs);
	signal(SIGTERM, handle_sigs);

	freq = initfreq = curfreq = get_freq();
	i = get_freq_id(curfreq, freqs, numfreqs);
	if (freq < 1)
		freq = 1;

	/*
	 * If we are in adaptive mode and the current frequency is outside the
	 * user-defined range, adjust it to be within the user-defined range.
	 */
	acline_read();
	if (acline_status > SRC_UNKNOWN)
		errx(1, "invalid AC line status %d", acline_status);
	if ((acline_status == SRC_AC &&
	    (mode_ac == MODE_ADAPTIVE || mode_ac == MODE_HIADAPTIVE)) ||
	    (acline_status == SRC_BATTERY &&
	    (mode_battery == MODE_ADAPTIVE || mode_battery == MODE_HIADAPTIVE)) ||
	    (acline_status == SRC_UNKNOWN &&
	    (mode_none == MODE_ADAPTIVE || mode_none == MODE_HIADAPTIVE))) {
		/* Read the current frequency. */
		len = sizeof(curfreq);
		if (sysctl(freq_mib, 4, &curfreq, &len, NULL, 0) != 0) {
			if (vflag)
				warn("error reading current CPU frequency");
		}
		if (curfreq < freqs[numfreqs - 1]) {
			if (vflag) {
				printf("CPU frequency is below user-defined "
				    "minimum; changing frequency to %d "
				    "MHz\n", freqs[numfreqs - 1]);
			}
			if (set_freq(freqs[numfreqs - 1]) != 0) {
				warn("error setting CPU freq %d",
				    freqs[numfreqs - 1]);
			}
		} else if (curfreq > freqs[0]) {
			if (vflag) {
				printf("CPU frequency is above user-defined "
				    "maximum; changing frequency to %d "
				    "MHz\n", freqs[0]);
			}
			if (set_freq(freqs[0]) != 0) {
				warn("error setting CPU freq %d",
				    freqs[0]);
			}
		}
	}

	idle = 0;
	/* Main loop. */
	for (;;) {
		FD_ZERO(&fdset);
		if (devd_pipe >= 0) {
			FD_SET(devd_pipe, &fdset);
			nfds = devd_pipe + 1;
		} else {
			nfds = 0;
		}
		if (mode == MODE_HIADAPTIVE || idle < 120)
			to = poll_ival;
		else if (idle < 360)
			to = poll_ival * 2;
		else
			to = poll_ival * 4;
		timeout.tv_sec = to / 1000000;
		timeout.tv_usec = to % 1000000;
		select(nfds, &fdset, NULL, &fdset, &timeout);

		/* If the user requested we quit, print some statistics. */
		if (exit_requested) {
			if (vflag && mjoules_used != 0)
				printf("total joules used: %u.%03u\n",
				    (u_int)(mjoules_used / 1000),
				    (int)mjoules_used % 1000);
			break;
		}

		/* Read the current AC status and record the mode. */
		acline_read();
		switch (acline_status) {
		case SRC_AC:
			mode = mode_ac;
			break;
		case SRC_BATTERY:
			mode = mode_battery;
			break;
		case SRC_UNKNOWN:
			mode = mode_none;
			break;
		default:
			errx(1, "invalid AC line status %d", acline_status);
		}

		/* Read the current frequency. */
		if (idle % 32 == 0) {
			if ((curfreq = get_freq()) == 0)
				continue;
			i = get_freq_id(curfreq, freqs, numfreqs);
		}
		idle++;
		if (vflag) {
			/* Keep a sum of all power actually used. */
			if (mwatts[i] != -1)
				mjoules_used +=
				    (mwatts[i] * (poll_ival / 1000)) / 1000;
		}

		/* Always switch to the lowest frequency in min mode. */
		if (mode == MODE_MIN) {
			freq = freqs[numfreqs - 1];
			if (curfreq != freq) {
				if (vflag) {
					printf("now operating on %s power; "
					    "changing frequency to %d MHz\n",
					    modes[acline_status], freq);
				}
				idle = 0;
				if (set_freq(freq) != 0) {
					warn("error setting CPU freq %d",
					    freq);
					continue;
				}
			}
			continue;
		}

		/* Always switch to the highest frequency in max mode. */
		if (mode == MODE_MAX) {
			freq = freqs[0];
			if (curfreq != freq) {
				if (vflag) {
					printf("now operating on %s power; "
					    "changing frequency to %d MHz\n",
					    modes[acline_status], freq);
				}
				idle = 0;
				if (set_freq(freq) != 0) {
					warn("error setting CPU freq %d",
					    freq);
					continue;
				}
			}
			continue;
		}

		/* Adaptive mode; get the current CPU usage times. */
		if (read_usage_times(&load)) {
			if (vflag)
				warn("read_usage_times() failed");
			continue;
		}

		if (mode == MODE_ADAPTIVE) {
			if (load > cpu_running_mark) {
				if (load > 95 || load > cpu_running_mark * 2)
					freq *= 2;
				else
					freq = freq * load / cpu_running_mark;
				if (freq > freqs[0])
					freq = freqs[0];
			} else if (load < cpu_idle_mark &&
			    curfreq * load < freqs[get_freq_id(
			    freq * 7 / 8, freqs, numfreqs)] *
			    cpu_running_mark) {
				freq = freq * 7 / 8;
				if (freq < freqs[numfreqs - 1])
					freq = freqs[numfreqs - 1];
			}
		} else { /* MODE_HIADAPTIVE */
			if (load > cpu_running_mark / 2) {
				if (load > 95 || load > cpu_running_mark)
					freq *= 4;
				else
					freq = freq * load * 2 / cpu_running_mark;
				if (freq > freqs[0] * 2)
					freq = freqs[0] * 2;
			} else if (load < cpu_idle_mark / 2 &&
			    curfreq * load < freqs[get_freq_id(
			    freq * 31 / 32, freqs, numfreqs)] *
			    cpu_running_mark / 2) {
				freq = freq * 31 / 32;
				if (freq < freqs[numfreqs - 1])
					freq = freqs[numfreqs - 1];
			}
		}
		if (vflag) {
		    printf("load %3d%%, current freq %4d MHz (%2d), wanted freq %4d MHz\n",
			load, curfreq, i, freq);
		}
		j = get_freq_id(freq, freqs, numfreqs);
		if (i != j) {
			if (vflag) {
				printf("changing clock"
				    " speed from %d MHz to %d MHz\n",
				    freqs[i], freqs[j]);
			}
			idle = 0;
			if (set_freq(freqs[j]))
				warn("error setting CPU frequency %d",
				    freqs[j]);
		}
	}
	if (set_freq(initfreq))
		warn("error setting CPU frequency %d", initfreq);
	free(freqs);
	free(mwatts);
	devd_close();
	if (!vflag)
		pidfile_remove(pfh);

	exit(0);
}