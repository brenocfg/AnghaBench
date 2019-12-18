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
struct sched_param {int sched_priority; } ;
struct rtprio {scalar_t__ prio; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  NTPD_PRIO ; 
 int /*<<< orphan*/  PRIO_PROCESS ; 
 int /*<<< orphan*/  RTP_PRIO_REALTIME ; 
 int /*<<< orphan*/  RTP_SET ; 
 int /*<<< orphan*/  SCHED_FIFO ; 
 int debug ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*,...) ; 
 int nice (int /*<<< orphan*/ ) ; 
 scalar_t__ priority_done ; 
 scalar_t__ rtprio (int /*<<< orphan*/ ,int,...) ; 
 int sched_get_priority_max (int /*<<< orphan*/ ) ; 
 int sched_get_priority_min (int /*<<< orphan*/ ) ; 
 int sched_setscheduler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sched_param*) ; 
 int setpriority (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_process_priority(void)
{

# ifdef DEBUG
	if (debug > 1)
		msyslog(LOG_DEBUG, "set_process_priority: %s: priority_done is <%d>",
			((priority_done)
			 ? "Leave priority alone"
			 : "Attempt to set priority"
				),
			priority_done);
# endif /* DEBUG */

# if defined(HAVE_SCHED_SETSCHEDULER)
	if (!priority_done) {
		extern int config_priority_override, config_priority;
		int pmax, pmin;
		struct sched_param sched;

		pmax = sched_get_priority_max(SCHED_FIFO);
		sched.sched_priority = pmax;
		if ( config_priority_override ) {
			pmin = sched_get_priority_min(SCHED_FIFO);
			if ( config_priority > pmax )
				sched.sched_priority = pmax;
			else if ( config_priority < pmin )
				sched.sched_priority = pmin;
			else
				sched.sched_priority = config_priority;
		}
		if ( sched_setscheduler(0, SCHED_FIFO, &sched) == -1 )
			msyslog(LOG_ERR, "sched_setscheduler(): %m");
		else
			++priority_done;
	}
# endif /* HAVE_SCHED_SETSCHEDULER */
# ifdef HAVE_RTPRIO
#  ifdef RTP_SET
	if (!priority_done) {
		struct rtprio srtp;

		srtp.type = RTP_PRIO_REALTIME;	/* was: RTP_PRIO_NORMAL */
		srtp.prio = 0;		/* 0 (hi) -> RTP_PRIO_MAX (31,lo) */

		if (rtprio(RTP_SET, getpid(), &srtp) < 0)
			msyslog(LOG_ERR, "rtprio() error: %m");
		else
			++priority_done;
	}
#  else	/* !RTP_SET follows */
	if (!priority_done) {
		if (rtprio(0, 120) < 0)
			msyslog(LOG_ERR, "rtprio() error: %m");
		else
			++priority_done;
	}
#  endif	/* !RTP_SET */
# endif	/* HAVE_RTPRIO */
# if defined(NTPD_PRIO) && NTPD_PRIO != 0
#  ifdef HAVE_ATT_NICE
	if (!priority_done) {
		errno = 0;
		if (-1 == nice (NTPD_PRIO) && errno != 0)
			msyslog(LOG_ERR, "nice() error: %m");
		else
			++priority_done;
	}
#  endif	/* HAVE_ATT_NICE */
#  ifdef HAVE_BSD_NICE
	if (!priority_done) {
		if (-1 == setpriority(PRIO_PROCESS, 0, NTPD_PRIO))
			msyslog(LOG_ERR, "setpriority() error: %m");
		else
			++priority_done;
	}
#  endif	/* HAVE_BSD_NICE */
# endif	/* NTPD_PRIO && NTPD_PRIO != 0 */
	if (!priority_done)
		msyslog(LOG_ERR, "set_process_priority: No way found to improve our priority");
}