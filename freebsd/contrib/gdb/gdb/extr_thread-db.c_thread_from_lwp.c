#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  td_thrhandle_t ;
typedef  scalar_t__ td_err_e ;
struct thread_info {TYPE_2__* private; } ;
typedef  int /*<<< orphan*/  ptid_t ;
struct TYPE_3__ {int /*<<< orphan*/  ti_tid; } ;
struct TYPE_4__ {TYPE_1__ ti; scalar_t__ ti_valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_LWP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUILD_THREAD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GET_LWP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_PID (int /*<<< orphan*/ ) ; 
 scalar_t__ TD_OK ; 
 int /*<<< orphan*/  error (char*,scalar_t__,char*) ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 int is_lwp (int /*<<< orphan*/ ) ; 
 scalar_t__ td_ta_map_lwp2thr_p (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_agent ; 
 char* thread_db_err_str (scalar_t__) ; 
 int /*<<< orphan*/  thread_get_info_callback (int /*<<< orphan*/ *,struct thread_info**) ; 

__attribute__((used)) static ptid_t
thread_from_lwp (ptid_t ptid)
{
  td_thrhandle_t th;
  td_err_e err;
  struct thread_info *thread_info;
  ptid_t thread_ptid;

  if (GET_LWP (ptid) == 0)
    ptid = BUILD_LWP (GET_PID (ptid), GET_PID (ptid));

  gdb_assert (is_lwp (ptid));

  err = td_ta_map_lwp2thr_p (thread_agent, GET_LWP (ptid), &th);
  if (err != TD_OK)
    error ("Cannot find user-level thread for LWP %ld: %s",
	   GET_LWP (ptid), thread_db_err_str (err));

  thread_info = NULL;
  thread_get_info_callback (&th, &thread_info);
  gdb_assert (thread_info && thread_info->private->ti_valid);

  return BUILD_THREAD (thread_info->private->ti.ti_tid, GET_PID (ptid));
}