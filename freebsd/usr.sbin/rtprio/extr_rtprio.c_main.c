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
struct rtprio {int type; void* prio; } ;
typedef  void* pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  RTP_LOOKUP ; 
#define  RTP_PRIO_FIFO 131 
#define  RTP_PRIO_IDLE 130 
#define  RTP_PRIO_NORMAL 129 
#define  RTP_PRIO_REALTIME 128 
 int /*<<< orphan*/  RTP_SET ; 
 void* abs (void*) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  execvp (char*,char**) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 char* getprogname () ; 
 int /*<<< orphan*/  isdigit (char) ; 
 void* parseint (char*,char*) ; 
 int /*<<< orphan*/  rtprio (int /*<<< orphan*/ ,void*,struct rtprio*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

int
main(int argc, char *argv[])
{
	struct rtprio rtp;
	const char *progname;
	pid_t proc = 0;

	progname = getprogname();

	if (strcmp(progname, "rtprio") == 0)
		rtp.type = RTP_PRIO_REALTIME;
	else if (strcmp(progname, "idprio") == 0)
		rtp.type = RTP_PRIO_IDLE;
	else
		errx(1, "invalid progname");

	switch (argc) {
	case 2:
		proc = parseint(argv[1], "pid");
		proc = abs(proc);
		/* FALLTHROUGH */
	case 1:
		if (rtprio(RTP_LOOKUP, proc, &rtp) != 0)
			err(1, "RTP_LOOKUP");
		switch (rtp.type) {
		case RTP_PRIO_REALTIME:
		case RTP_PRIO_FIFO:
			warnx("realtime priority %d", rtp.prio);
			break;
		case RTP_PRIO_NORMAL:
			warnx("normal priority");
			break;
		case RTP_PRIO_IDLE:
			warnx("idle priority %d", rtp.prio);
			break;
		default:
			errx(1, "invalid priority type %d", rtp.type);
			break;
		}
		exit(0);
	default:
		if (argv[1][0] == '-' || isdigit(argv[1][0])) {
			if (argv[1][0] == '-') {
				if (strcmp(argv[1], "-t") == 0) {
					rtp.type = RTP_PRIO_NORMAL;
					rtp.prio = 0;
				} else {
					usage();
					break;
				}
			} else
				rtp.prio = parseint(argv[1], "priority");
		} else {
			usage();
			break;
		}

		if (argv[2][0] == '-') {
			proc = parseint(argv[2], "pid");
			proc = abs(proc);
		}

		if (rtprio(RTP_SET, proc, &rtp) != 0)
			err(1, "RTP_SET");

		if (proc == 0) {
			execvp(argv[2], &argv[2]);
			err(1, "execvp: %s", argv[2]);
		}
		exit(0);
	}
	/* NOTREACHED */
}