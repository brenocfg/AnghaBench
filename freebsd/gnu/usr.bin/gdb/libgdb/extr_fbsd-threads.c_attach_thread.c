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
struct TYPE_3__ {scalar_t__ ti_state; } ;
typedef  TYPE_1__ td_thrinfo_t ;
typedef  int /*<<< orphan*/  td_thrhandle_t ;
typedef  scalar_t__ td_err_e ;
typedef  int /*<<< orphan*/  ptid_t ;

/* Variables and functions */
 int /*<<< orphan*/  IS_THREAD (int /*<<< orphan*/ ) ; 
 scalar_t__ TD_OK ; 
 scalar_t__ TD_THR_UNKNOWN ; 
 scalar_t__ TD_THR_ZOMBIE ; 
 int /*<<< orphan*/  add_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ fbsd_thread_core ; 
 int /*<<< orphan*/  in_thread_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf_unfiltered (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_pid_to_str (int /*<<< orphan*/ ) ; 
 scalar_t__ td_thr_event_enable_p (int /*<<< orphan*/  const*,int) ; 
 char* thread_db_err_str (scalar_t__) ; 

__attribute__((used)) static void
attach_thread (ptid_t ptid, const td_thrhandle_t *th_p,
               const td_thrinfo_t *ti_p, int verbose)
{
  td_err_e err;

  /* Add the thread to GDB's thread list.  */
  if (!in_thread_list (ptid)) {
    add_thread (ptid);
    if (verbose)
      printf_unfiltered ("[New %s]\n", target_pid_to_str (ptid));
  }

  if (ti_p->ti_state == TD_THR_UNKNOWN || ti_p->ti_state == TD_THR_ZOMBIE)
    return;                     /* A zombie thread -- do not attach.  */

  if (! IS_THREAD(ptid))
    return;
  if (fbsd_thread_core != 0)
    return;
  /* Enable thread event reporting for this thread. */
  err = td_thr_event_enable_p (th_p, 1);
  if (err != TD_OK)
    error ("Cannot enable thread event reporting for %s: %s",
           target_pid_to_str (ptid), thread_db_err_str (err));
}