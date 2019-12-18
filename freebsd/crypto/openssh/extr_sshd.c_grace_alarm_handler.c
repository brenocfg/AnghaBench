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
struct TYPE_2__ {scalar_t__ m_pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLACKLIST_AUTH_FAIL ; 
 int /*<<< orphan*/  BLACKLIST_NOTIFY (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  active_state ; 
 scalar_t__ getpgid (int /*<<< orphan*/ ) ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  kill (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__* pmonitor ; 
 int /*<<< orphan*/  sigdie (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssh_remote_ipaddr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssh_remote_port (int /*<<< orphan*/ ) ; 
 scalar_t__ use_privsep ; 

__attribute__((used)) static void
grace_alarm_handler(int sig)
{
	if (use_privsep && pmonitor != NULL && pmonitor->m_pid > 0)
		kill(pmonitor->m_pid, SIGALRM);

	/*
	 * Try to kill any processes that we have spawned, E.g. authorized
	 * keys command helpers.
	 */
	if (getpgid(0) == getpid()) {
		signal(SIGTERM, SIG_IGN);
		kill(0, SIGTERM);
	}

	BLACKLIST_NOTIFY(BLACKLIST_AUTH_FAIL, "ssh");

	/* Log error and exit. */
	sigdie("Timeout before authentication for %s port %d",
	    ssh_remote_ipaddr(active_state), ssh_remote_port(active_state));
}