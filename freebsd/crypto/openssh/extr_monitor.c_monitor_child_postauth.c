#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct monitor {int m_recvfd; int /*<<< orphan*/  m_pid; } ;
struct TYPE_2__ {scalar_t__ permit_pty_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  MONITOR_REQ_MODULI ; 
 int /*<<< orphan*/  MONITOR_REQ_PTY ; 
 int /*<<< orphan*/  MONITOR_REQ_PTYCLEANUP ; 
 int /*<<< orphan*/  MONITOR_REQ_SIGN ; 
 int /*<<< orphan*/  MONITOR_REQ_TERM ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIGXFSZ ; 
 int /*<<< orphan*/ * SIG_IGN ; 
 TYPE_1__* auth_opts ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  mon_dispatch ; 
 int /*<<< orphan*/  mon_dispatch_postauth20 ; 
 int /*<<< orphan*/  monitor_child_handler ; 
 int /*<<< orphan*/  monitor_permit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  monitor_read (struct monitor*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  monitor_set_child_handler (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
monitor_child_postauth(struct monitor *pmonitor)
{
	close(pmonitor->m_recvfd);
	pmonitor->m_recvfd = -1;

	monitor_set_child_handler(pmonitor->m_pid);
	signal(SIGHUP, &monitor_child_handler);
	signal(SIGTERM, &monitor_child_handler);
	signal(SIGINT, &monitor_child_handler);
#ifdef SIGXFSZ
	signal(SIGXFSZ, SIG_IGN);
#endif

	mon_dispatch = mon_dispatch_postauth20;

	/* Permit requests for moduli and signatures */
	monitor_permit(mon_dispatch, MONITOR_REQ_MODULI, 1);
	monitor_permit(mon_dispatch, MONITOR_REQ_SIGN, 1);
	monitor_permit(mon_dispatch, MONITOR_REQ_TERM, 1);

	if (auth_opts->permit_pty_flag) {
		monitor_permit(mon_dispatch, MONITOR_REQ_PTY, 1);
		monitor_permit(mon_dispatch, MONITOR_REQ_PTYCLEANUP, 1);
	}

	for (;;)
		monitor_read(pmonitor, mon_dispatch, NULL);
}