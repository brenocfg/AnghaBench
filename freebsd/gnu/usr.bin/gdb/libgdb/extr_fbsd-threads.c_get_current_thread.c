#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  td_thrinfo_t ;
typedef  int /*<<< orphan*/  td_thrhandle_t ;
typedef  int /*<<< orphan*/  ptid_t ;
struct TYPE_2__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_LWP (long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  attach_thread (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 long get_current_lwp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_thread_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 TYPE_1__ proc_handle ; 
 int /*<<< orphan*/  thread_from_lwp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
get_current_thread ()
{
  td_thrhandle_t th;
  td_thrinfo_t ti;
  long lwp;
  ptid_t tmp, ptid;

  lwp = get_current_lwp (proc_handle.pid);
  tmp = BUILD_LWP (lwp, proc_handle.pid);
  ptid = thread_from_lwp (tmp, &th, &ti);
  if (!in_thread_list (ptid))
    {
      attach_thread (ptid, &th, &ti, 1);
    }
  inferior_ptid = ptid;
}