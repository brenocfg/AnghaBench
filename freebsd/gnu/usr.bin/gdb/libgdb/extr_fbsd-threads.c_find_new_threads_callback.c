#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ ti_state; int /*<<< orphan*/  ti_tid; } ;
typedef  TYPE_1__ td_thrinfo_t ;
typedef  int /*<<< orphan*/  td_thrhandle_t ;
typedef  scalar_t__ td_err_e ;
typedef  int /*<<< orphan*/  ptid_t ;
struct TYPE_6__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_THREAD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TD_OK ; 
 scalar_t__ TD_THR_UNKNOWN ; 
 scalar_t__ TD_THR_ZOMBIE ; 
 int /*<<< orphan*/  attach_thread (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 TYPE_3__ proc_handle ; 
 scalar_t__ td_thr_get_info_p (int /*<<< orphan*/  const*,TYPE_1__*) ; 
 int /*<<< orphan*/  thread_db_err_str (scalar_t__) ; 

__attribute__((used)) static int
find_new_threads_callback (const td_thrhandle_t *th_p, void *data)
{
  td_thrinfo_t ti;
  td_err_e err;
  ptid_t ptid;

  err = td_thr_get_info_p (th_p, &ti);
  if (err != TD_OK)
    error ("Cannot get thread info: %s", thread_db_err_str (err));

  /* Ignore zombie */
  if (ti.ti_state == TD_THR_UNKNOWN || ti.ti_state == TD_THR_ZOMBIE)
    return 0;

  ptid = BUILD_THREAD (ti.ti_tid, proc_handle.pid);
  attach_thread (ptid, th_p, &ti, 1);
  return 0;
}