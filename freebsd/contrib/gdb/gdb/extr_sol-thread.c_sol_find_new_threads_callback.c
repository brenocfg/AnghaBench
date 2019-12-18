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
typedef  int /*<<< orphan*/  td_err_e ;
typedef  int /*<<< orphan*/  ptid_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_THREAD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TD_OK ; 
 int /*<<< orphan*/  add_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_thread_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  p_td_thr_get_info (int /*<<< orphan*/  const*,TYPE_1__*) ; 

__attribute__((used)) static int
sol_find_new_threads_callback (const td_thrhandle_t *th, void *ignored)
{
  td_err_e retval;
  td_thrinfo_t ti;
  ptid_t ptid;

  if ((retval = p_td_thr_get_info (th, &ti)) != TD_OK)
    {
      return -1;
    }
  ptid = BUILD_THREAD (ti.ti_tid, PIDGET (inferior_ptid));
  if (!in_thread_list (ptid))
    add_thread (ptid);

  return 0;
}