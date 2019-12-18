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
struct timespec {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;
typedef  int /*<<< orphan*/  sigset_t ;
struct TYPE_2__ {int /*<<< orphan*/  hc_controlconn; } ;

/* Variables and functions */
 int /*<<< orphan*/  EX_OK ; 
 int /*<<< orphan*/  PJDLOG_ABORT (char*,int) ; 
 int /*<<< orphan*/  PJDLOG_VERIFY (int) ; 
#define  SIGCHLD 131 
#define  SIGHUP 130 
#define  SIGINT 129 
#define  SIGTERM 128 
 TYPE_1__* cfg ; 
 int /*<<< orphan*/  child_exit () ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hastd_reload () ; 
 int /*<<< orphan*/  proto_close (int /*<<< orphan*/ ) ; 
 scalar_t__ sigaddset (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sigemptyset (int /*<<< orphan*/ *) ; 
 int sigexit_received ; 
 int sigtimedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timespec*) ; 
 int /*<<< orphan*/  terminate_workers () ; 

__attribute__((used)) static void
check_signals(void)
{
	struct timespec sigtimeout;
	sigset_t mask;
	int signo;

	sigtimeout.tv_sec = 0;
	sigtimeout.tv_nsec = 0;

	PJDLOG_VERIFY(sigemptyset(&mask) == 0);
	PJDLOG_VERIFY(sigaddset(&mask, SIGHUP) == 0);
	PJDLOG_VERIFY(sigaddset(&mask, SIGINT) == 0);
	PJDLOG_VERIFY(sigaddset(&mask, SIGTERM) == 0);
	PJDLOG_VERIFY(sigaddset(&mask, SIGCHLD) == 0);

	while ((signo = sigtimedwait(&mask, NULL, &sigtimeout)) != -1) {
		switch (signo) {
		case SIGINT:
		case SIGTERM:
			sigexit_received = true;
			terminate_workers();
			proto_close(cfg->hc_controlconn);
			exit(EX_OK);
			break;
		case SIGCHLD:
			child_exit();
			break;
		case SIGHUP:
			hastd_reload();
			break;
		default:
			PJDLOG_ABORT("Unexpected signal (%d).", signo);
		}
	}
}