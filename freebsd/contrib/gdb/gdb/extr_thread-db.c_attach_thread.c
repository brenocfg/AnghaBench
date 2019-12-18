#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ ti_state; int /*<<< orphan*/  ti_lid; } ;
typedef  TYPE_1__ td_thrinfo_t ;
typedef  int /*<<< orphan*/  td_thrhandle_t ;
typedef  scalar_t__ td_err_e ;
struct thread_info {int /*<<< orphan*/  private; } ;
struct private_thread_info {int dummy; } ;
typedef  int /*<<< orphan*/  ptid_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATTACH_LWP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUILD_LWP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_PID (int /*<<< orphan*/ ) ; 
 scalar_t__ TD_OK ; 
 scalar_t__ TD_THR_UNKNOWN ; 
 scalar_t__ TD_THR_ZOMBIE ; 
 struct thread_info* add_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_thread_signals () ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf_unfiltered (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_pid_to_str (int /*<<< orphan*/ ) ; 
 scalar_t__ td_thr_event_enable_p (int /*<<< orphan*/  const*,int) ; 
 char* thread_db_err_str (scalar_t__) ; 
 int /*<<< orphan*/  xmalloc (int) ; 

__attribute__((used)) static void
attach_thread (ptid_t ptid, const td_thrhandle_t *th_p,
	       const td_thrinfo_t *ti_p, int verbose)
{
  struct thread_info *tp;
  td_err_e err;

  check_thread_signals ();

  /* Add the thread to GDB's thread list.  */
  tp = add_thread (ptid);
  tp->private = xmalloc (sizeof (struct private_thread_info));
  memset (tp->private, 0, sizeof (struct private_thread_info));

  if (verbose)
    printf_unfiltered ("[New %s]\n", target_pid_to_str (ptid));

  if (ti_p->ti_state == TD_THR_UNKNOWN || ti_p->ti_state == TD_THR_ZOMBIE)
    return;			/* A zombie thread -- do not attach.  */

  /* Under GNU/Linux, we have to attach to each and every thread.  */
#ifdef ATTACH_LWP
  ATTACH_LWP (BUILD_LWP (ti_p->ti_lid, GET_PID (ptid)), 0);
#endif

  /* Enable thread event reporting for this thread.  */
  err = td_thr_event_enable_p (th_p, 1);
  if (err != TD_OK)
    error ("Cannot enable thread event reporting for %s: %s",
	   target_pid_to_str (ptid), thread_db_err_str (err));
}