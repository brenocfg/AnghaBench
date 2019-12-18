#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  sival_ptr; int /*<<< orphan*/  sival_int; } ;
struct TYPE_7__ {int si_code; TYPE_1__ si_value; int /*<<< orphan*/  si_uid; int /*<<< orphan*/  si_pid; int /*<<< orphan*/  si_addr; void* si_status; int /*<<< orphan*/  si_band; int /*<<< orphan*/  si_timerid; } ;
typedef  TYPE_2__ siginfo_t ;
struct TYPE_8__ {void* lsi_ptr; int /*<<< orphan*/  lsi_int; int /*<<< orphan*/  lsi_uid; int /*<<< orphan*/  lsi_pid; void* lsi_addr; void* lsi_status; int /*<<< orphan*/  lsi_errno; int /*<<< orphan*/  lsi_band; int /*<<< orphan*/  lsi_tid; int /*<<< orphan*/  lsi_code; int /*<<< orphan*/  lsi_signo; } ;
typedef  TYPE_3__ l_siginfo_t ;
typedef  int /*<<< orphan*/  l_int ;

/* Variables and functions */
 int CLD_CONTINUED ; 
 int CLD_STOPPED ; 
#define  LINUX_SIGBUS 137 
#define  LINUX_SIGCHLD 136 
#define  LINUX_SIGFPE 135 
#define  LINUX_SIGILL 134 
#define  LINUX_SIGPOLL 133 
 int /*<<< orphan*/  LINUX_SIGRTMIN ; 
#define  LINUX_SIGSEGV 132 
 void* PTROUT (int /*<<< orphan*/ ) ; 
 void* SIGCONT ; 
#define  SI_ASYNCIO 131 
#define  SI_LWP 130 
#define  SI_QUEUE 129 
#define  SI_TIMER 128 
 void* bsd_to_linux_signal (void*) ; 
 int /*<<< orphan*/  sicode_to_lsicode (int,int /*<<< orphan*/ *) ; 

void
siginfo_to_lsiginfo(const siginfo_t *si, l_siginfo_t *lsi, l_int sig)
{

	/* sig alredy converted */
	lsi->lsi_signo = sig;
	sicode_to_lsicode(si->si_code, &lsi->lsi_code);

	switch (si->si_code) {
	case SI_LWP:
		lsi->lsi_pid = si->si_pid;
		lsi->lsi_uid = si->si_uid;
		break;

	case SI_TIMER:
		lsi->lsi_int = si->si_value.sival_int;
		lsi->lsi_ptr = PTROUT(si->si_value.sival_ptr);
		lsi->lsi_tid = si->si_timerid;
		break;

	case SI_QUEUE:
		lsi->lsi_pid = si->si_pid;
		lsi->lsi_uid = si->si_uid;
		lsi->lsi_ptr = PTROUT(si->si_value.sival_ptr);
		break;

	case SI_ASYNCIO:
		lsi->lsi_int = si->si_value.sival_int;
		lsi->lsi_ptr = PTROUT(si->si_value.sival_ptr);
		break;

	default:
		switch (sig) {
		case LINUX_SIGPOLL:
			/* XXX si_fd? */
			lsi->lsi_band = si->si_band;
			break;

		case LINUX_SIGCHLD:
			lsi->lsi_errno = 0;
			lsi->lsi_pid = si->si_pid;
			lsi->lsi_uid = si->si_uid;

			if (si->si_code == CLD_STOPPED)
				lsi->lsi_status = bsd_to_linux_signal(si->si_status);
			else if (si->si_code == CLD_CONTINUED)
				lsi->lsi_status = bsd_to_linux_signal(SIGCONT);
			else
				lsi->lsi_status = si->si_status;
			break;

		case LINUX_SIGBUS:
		case LINUX_SIGILL:
		case LINUX_SIGFPE:
		case LINUX_SIGSEGV:
			lsi->lsi_addr = PTROUT(si->si_addr);
			break;

		default:
			lsi->lsi_pid = si->si_pid;
			lsi->lsi_uid = si->si_uid;
			if (sig >= LINUX_SIGRTMIN) {
				lsi->lsi_int = si->si_value.sival_int;
				lsi->lsi_ptr = PTROUT(si->si_value.sival_ptr);
			}
			break;
		}
		break;
	}
}