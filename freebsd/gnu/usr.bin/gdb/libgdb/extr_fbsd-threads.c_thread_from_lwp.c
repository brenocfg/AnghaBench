#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ti_tid; } ;
typedef  TYPE_1__ td_thrinfo_t ;
typedef  int /*<<< orphan*/  td_thrhandle_t ;
typedef  scalar_t__ td_err_e ;
typedef  int /*<<< orphan*/  ptid_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_LWP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUILD_THREAD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_LWP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_PID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_LWP (int /*<<< orphan*/ ) ; 
 scalar_t__ TD_OK ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ fbsd_thread_active ; 
 int /*<<< orphan*/  gdb_assert (int /*<<< orphan*/ ) ; 
 scalar_t__ td_ta_map_lwp2thr_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ td_thr_get_info_p (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  thread_agent ; 
 int /*<<< orphan*/  thread_db_err_str (scalar_t__) ; 

__attribute__((used)) static ptid_t
thread_from_lwp (ptid_t ptid, td_thrhandle_t *th, td_thrinfo_t *ti)
{
  td_err_e err;
 
  gdb_assert (IS_LWP (ptid));

  if (fbsd_thread_active)
    {
      err = td_ta_map_lwp2thr_p (thread_agent, GET_LWP (ptid), th);
      if (err == TD_OK)
        {
          err = td_thr_get_info_p (th, ti);
          if (err != TD_OK)
            error ("Cannot get thread info: %s", thread_db_err_str (err));
          return BUILD_THREAD (ti->ti_tid, GET_PID (ptid));
        }
    }

  /* the LWP is not mapped to user thread */  
  return BUILD_LWP (GET_LWP (ptid), GET_PID (ptid));
}