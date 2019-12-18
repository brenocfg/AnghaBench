#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ si_signo; scalar_t__ si_errno; int si_code; int /*<<< orphan*/  si_addr; int /*<<< orphan*/  si_status; int /*<<< orphan*/  si_uid; int /*<<< orphan*/  si_pid; } ;
struct TYPE_5__ {TYPE_1__ ti_siginfo; int /*<<< orphan*/  ti_pending; int /*<<< orphan*/  ti_sigmask; } ;
typedef  TYPE_2__ td_thrinfo_t ;
typedef  int /*<<< orphan*/  td_thrhandle_t ;
typedef  scalar_t__ td_err_e ;

/* Variables and functions */
 int /*<<< orphan*/  GET_THREAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_THREAD (int /*<<< orphan*/ ) ; 
#define  SI_ASYNCIO 134 
#define  SI_KERNEL 133 
#define  SI_MESGQ 132 
#define  SI_NOINFO 131 
#define  SI_QUEUE 130 
#define  SI_TIMER 129 
#define  SI_USER 128 
 scalar_t__ TD_OK ; 
 int /*<<< orphan*/  fbsd_print_sigset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fbsd_thread_active ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  printf_filtered (char*,...) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 scalar_t__ td_ta_map_id2thr_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ td_thr_get_info_p (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  thread_agent ; 

__attribute__((used)) static void
fbsd_thread_signal_cmd (char *exp, int from_tty)
{
  td_thrhandle_t th;
  td_thrinfo_t ti;
  td_err_e err;
  const char *code;

  if (!fbsd_thread_active || !IS_THREAD(inferior_ptid))
    return;

  err = td_ta_map_id2thr_p (thread_agent, GET_THREAD (inferior_ptid), &th);
  if (err != TD_OK)
    return;

  err = td_thr_get_info_p (&th, &ti);
  if (err != TD_OK)
    return;

  printf_filtered("signal mask:\n");
  fbsd_print_sigset(&ti.ti_sigmask);
  printf_filtered("signal pending:\n");
  fbsd_print_sigset(&ti.ti_pending);
  if (ti.ti_siginfo.si_signo != 0) {
   printf_filtered("si_signo %d si_errno %d", ti.ti_siginfo.si_signo,
     ti.ti_siginfo.si_errno);
   if (ti.ti_siginfo.si_errno != 0)
    printf_filtered(" (%s)", strerror(ti.ti_siginfo.si_errno));
   printf_filtered("\n");
   switch (ti.ti_siginfo.si_code) {
   case SI_NOINFO:
	code = "NOINFO";
	break;
    case SI_USER:
	code = "USER";
	break;
    case SI_QUEUE:
	code = "QUEUE";
	break;
    case SI_TIMER:
	code = "TIMER";
	break;
    case SI_ASYNCIO:
	code = "ASYNCIO";
	break;
    case SI_MESGQ:
	code = "MESGQ";
	break;
    case SI_KERNEL:
	code = "KERNEL";
	break;
    default:
	code = "UNKNOWN";
	break;
    }
    printf_filtered("si_code %s (%d) si_pid %d si_uid %d si_status %x "
      "si_addr %p\n",
      code, ti.ti_siginfo.si_code, ti.ti_siginfo.si_pid, ti.ti_siginfo.si_uid,
      ti.ti_siginfo.si_status, ti.ti_siginfo.si_addr);
  }
}