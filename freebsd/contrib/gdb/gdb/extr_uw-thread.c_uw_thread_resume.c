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
typedef  int /*<<< orphan*/  ptid_t ;
typedef  enum target_signal { ____Placeholder_target_signal } target_signal ;
struct TYPE_2__ {int /*<<< orphan*/  (* to_resume ) (int /*<<< orphan*/ ,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CALL_BASE (int /*<<< orphan*/ ) ; 
 scalar_t__ PIDGET (int /*<<< orphan*/ ) ; 
 TYPE_1__ base_ops ; 
 int /*<<< orphan*/  null_ptid ; 
 int /*<<< orphan*/  pid_to_ptid (int) ; 
 scalar_t__ ptid_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  thr_to_lwp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
uw_thread_resume (ptid_t ptid, int step, enum target_signal signo)
{
  if (PIDGET (ptid) > 0)
    {
      ptid = thr_to_lwp (ptid);
      if (ptid_equal (ptid, null_ptid))
	ptid = pid_to_ptid (-1);
    }

  CALL_BASE (base_ops.to_resume (ptid, step, signo));
}