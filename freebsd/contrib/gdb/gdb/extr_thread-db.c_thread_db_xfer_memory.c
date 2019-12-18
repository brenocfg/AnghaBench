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
struct target_ops {int dummy; } ;
struct mem_attrib {int dummy; } ;
struct cleanup {int dummy; } ;
struct TYPE_2__ {int (* to_xfer_memory ) (int /*<<< orphan*/ ,char*,int,int,struct mem_attrib*,struct target_ops*) ;} ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  GET_PID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 scalar_t__ is_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lwp_from_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pid_to_ptid (int /*<<< orphan*/ ) ; 
 struct cleanup* save_inferior_ptid () ; 
 int stub1 (int /*<<< orphan*/ ,char*,int,int,struct mem_attrib*,struct target_ops*) ; 
 TYPE_1__* target_beneath ; 
 int /*<<< orphan*/  target_thread_alive (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
thread_db_xfer_memory (CORE_ADDR memaddr, char *myaddr, int len, int write,
		       struct mem_attrib *attrib, struct target_ops *target)
{
  struct cleanup *old_chain = save_inferior_ptid ();
  int xfer;

  if (is_thread (inferior_ptid))
    {
      /* FIXME: This seems to be necessary to make sure breakpoints
         are removed.  */
      if (!target_thread_alive (inferior_ptid))
	inferior_ptid = pid_to_ptid (GET_PID (inferior_ptid));
      else
	inferior_ptid = lwp_from_thread (inferior_ptid);
    }

  xfer =
    target_beneath->to_xfer_memory (memaddr, myaddr, len, write, attrib,
				    target);

  do_cleanups (old_chain);
  return xfer;
}