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
struct TYPE_3__ {int /*<<< orphan*/  ti_tid; } ;
typedef  TYPE_1__ td_thrinfo_t ;
typedef  int /*<<< orphan*/  td_thrhandle_t ;
typedef  scalar_t__ td_err_e ;
typedef  int /*<<< orphan*/  ptid_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_THREAD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_LWP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIDGET (int /*<<< orphan*/ ) ; 
 scalar_t__ TD_NOTHR ; 
 scalar_t__ TD_OK ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  main_ta ; 
 scalar_t__ p_td_ta_map_lwp2thr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ p_td_thr_get_info (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ p_td_thr_validate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pid_to_ptid (int) ; 
 int /*<<< orphan*/  sol_thread_alive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  td_err_string (scalar_t__) ; 

__attribute__((used)) static ptid_t
lwp_to_thread (ptid_t lwp)
{
  td_thrinfo_t ti;
  td_thrhandle_t th;
  td_err_e val;

  if (is_thread (lwp))
    return lwp;			/* It's already a thread id */

  /* It's an lwp.  Convert it to a thread id.  */

  if (!sol_thread_alive (lwp))
    return pid_to_ptid (-1);	/* defunct lwp */

  val = p_td_ta_map_lwp2thr (main_ta, GET_LWP (lwp), &th);
  if (val == TD_NOTHR)
    return pid_to_ptid (-1);	/* thread must have terminated */
  else if (val != TD_OK)
    error ("lwp_to_thread: td_ta_map_lwp2thr: %s.", td_err_string (val));

  val = p_td_thr_validate (&th);
  if (val == TD_NOTHR)
    return lwp;			/* libthread doesn't know about it;
				   just return lwp */
  else if (val != TD_OK)
    error ("lwp_to_thread: td_thr_validate: %s.", td_err_string (val));

  val = p_td_thr_get_info (&th, &ti);
  if (val == TD_NOTHR)
    return pid_to_ptid (-1);	/* thread must have terminated */
  else if (val != TD_OK)
    error ("lwp_to_thread: td_thr_get_info: %s.", td_err_string (val));

  return BUILD_THREAD (ti.ti_tid, PIDGET (lwp));
}