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
typedef  int /*<<< orphan*/  ptid_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_LWP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_THREAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIDGET (int /*<<< orphan*/ ) ; 
 scalar_t__ TD_NOTHR ; 
 scalar_t__ TD_OK ; 
 scalar_t__ TD_THR_ACTIVE ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_lwp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  main_ta ; 
 scalar_t__ p_td_ta_map_id2thr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ p_td_thr_get_info (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  pid_to_ptid (int) ; 
 int /*<<< orphan*/  td_err_string (scalar_t__) ; 
 int /*<<< orphan*/  td_state_string (scalar_t__) ; 

__attribute__((used)) static ptid_t
thread_to_lwp (ptid_t thread_id, int default_lwp)
{
  td_thrinfo_t ti;
  td_thrhandle_t th;
  td_err_e val;

  if (is_lwp (thread_id))
    return thread_id;		/* It's already an LWP id */

  /* It's a thread.  Convert to lwp */

  val = p_td_ta_map_id2thr (main_ta, GET_THREAD (thread_id), &th);
  if (val == TD_NOTHR)
    return pid_to_ptid (-1);		/* thread must have terminated */
  else if (val != TD_OK)
    error ("thread_to_lwp: td_ta_map_id2thr %s", td_err_string (val));

  val = p_td_thr_get_info (&th, &ti);
  if (val == TD_NOTHR)
    return pid_to_ptid (-1);		/* thread must have terminated */
  else if (val != TD_OK)
    error ("thread_to_lwp: td_thr_get_info: %s", td_err_string (val));

  if (ti.ti_state != TD_THR_ACTIVE)
    {
      if (default_lwp != -1)
	return pid_to_ptid (default_lwp);
      error ("thread_to_lwp: thread state not active: %s",
	     td_state_string (ti.ti_state));
    }

  return BUILD_LWP (ti.ti_lid, PIDGET (thread_id));
}