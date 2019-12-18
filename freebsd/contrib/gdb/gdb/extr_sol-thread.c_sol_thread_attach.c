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
struct target_ops {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  ptid; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* to_attach ) (char*,int) ;} ;

/* Variables and functions */
 int PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOLIB_ADD (char*,int,struct target_ops*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  auto_solib_add ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  lwp_to_thread (int /*<<< orphan*/ ) ; 
 TYPE_2__ main_ph ; 
 int /*<<< orphan*/  printf_filtered (char*) ; 
 TYPE_1__ procfs_ops ; 
 int /*<<< orphan*/  push_target (int /*<<< orphan*/ *) ; 
 scalar_t__ sol_thread_active ; 
 int /*<<< orphan*/  sol_thread_ops ; 
 int /*<<< orphan*/  stub1 (char*,int) ; 

__attribute__((used)) static void
sol_thread_attach (char *args, int from_tty)
{
  procfs_ops.to_attach (args, from_tty);

  /* Must get symbols from solibs before libthread_db can run! */
  SOLIB_ADD ((char *) 0, from_tty, (struct target_ops *) 0, auto_solib_add);

  if (sol_thread_active)
    {
      printf_filtered ("sol-thread active.\n");
      main_ph.ptid = inferior_ptid;		/* Save for xfer_memory */
      push_target (&sol_thread_ops);
      inferior_ptid = lwp_to_thread (inferior_ptid);
      if (PIDGET (inferior_ptid) == -1)
	inferior_ptid = main_ph.ptid;
      else
	add_thread (inferior_ptid);
    }
  /* XXX - might want to iterate over all the threads and register them. */
}