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
struct thread_info {TYPE_1__* private; } ;
typedef  int /*<<< orphan*/  ptid_t ;
struct TYPE_2__ {int /*<<< orphan*/  lwpid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG2 (char*) ; 
 int /*<<< orphan*/  ISTID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MKLID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbgpid (int /*<<< orphan*/ ) ; 
 struct thread_info* find_thread_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  null_ptid ; 
 int /*<<< orphan*/  pid ; 

__attribute__((used)) static ptid_t
thr_to_lwp (ptid_t ptid)
{
  struct thread_info *info;
  ptid_t lid;

  if (!ISTID (ptid))
    lid = ptid;
  else if (!(info = find_thread_pid (ptid)))
    lid = null_ptid;
  else if (!info->private->lwpid)
    lid = null_ptid;
  else
    lid = MKLID (PIDGET (ptid), info->private->lwpid);

  DBG2(("  thr_to_lwp(%s) = %s", dbgpid (pid), dbgpid (lid)));
  return lid;
}