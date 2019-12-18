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
struct TYPE_2__ {int /*<<< orphan*/  thrid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG2 (char*) ; 
 scalar_t__ ISTID (int /*<<< orphan*/ ) ; 
 int LIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MKTID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbgpid (int /*<<< orphan*/ ) ; 
 struct thread_info* find_thread_lwp (int) ; 

__attribute__((used)) static ptid_t
lwp_to_thr (ptid_t ptid)
{
  struct thread_info *info;
  int lwpid;
  ptid_t tid = ptid;

  if (ISTID (ptid))
    goto done;
  if (!(lwpid = LIDGET (ptid)))
    goto done;
  if (!(info = find_thread_lwp (lwpid)))
    goto done;
  tid = MKTID (PIDGET (ptid), info->private->thrid);

 done:
  DBG2((ISTID (tid) ? NULL : "lwp_to_thr: no thr for %s", dbgpid (ptid)));
  return tid;
}