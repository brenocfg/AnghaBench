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
struct cleanup {int dummy; } ;
typedef  int /*<<< orphan*/  ptid_t ;
typedef  enum target_signal { ____Placeholder_target_signal } target_signal ;
struct TYPE_2__ {int /*<<< orphan*/  (* to_resume ) (int /*<<< orphan*/ ,int,int) ;} ;

/* Variables and functions */
 int GET_PID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_lwpid_callback ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 scalar_t__ is_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iterate_over_threads (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lwp_from_thread (int /*<<< orphan*/ ) ; 
 struct cleanup* save_inferior_ptid () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int) ; 
 TYPE_1__* target_beneath ; 

__attribute__((used)) static void
thread_db_resume (ptid_t ptid, int step, enum target_signal signo)
{
  struct cleanup *old_chain = save_inferior_ptid ();

  if (GET_PID (ptid) == -1)
    inferior_ptid = lwp_from_thread (inferior_ptid);
  else if (is_thread (ptid))
    ptid = lwp_from_thread (ptid);

  /* Clear cached data which may not be valid after the resume.  */
  iterate_over_threads (clear_lwpid_callback, NULL);

  target_beneath->to_resume (ptid, step, signo);

  do_cleanups (old_chain);
}