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
struct TYPE_4__ {int /*<<< orphan*/  ptid; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* to_create_inferior ) (char*,char*,char**) ;} ;

/* Variables and functions */
 int PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_thread_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  lwp_to_thread (int /*<<< orphan*/ ) ; 
 TYPE_2__ main_ph ; 
 int /*<<< orphan*/  null_ptid ; 
 TYPE_1__ procfs_ops ; 
 int /*<<< orphan*/  ptid_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_target (int /*<<< orphan*/ *) ; 
 scalar_t__ sol_thread_active ; 
 int /*<<< orphan*/  sol_thread_ops ; 
 int /*<<< orphan*/  stub1 (char*,char*,char**) ; 

__attribute__((used)) static void
sol_thread_create_inferior (char *exec_file, char *allargs, char **env)
{
  procfs_ops.to_create_inferior (exec_file, allargs, env);

  if (sol_thread_active && !ptid_equal (inferior_ptid, null_ptid))
    {
      main_ph.ptid = inferior_ptid;	/* Save for xfer_memory */

      push_target (&sol_thread_ops);

      inferior_ptid = lwp_to_thread (inferior_ptid);
      if (PIDGET (inferior_ptid) == -1)
	inferior_ptid = main_ph.ptid;

      if (!in_thread_list (inferior_ptid))
	add_thread (inferior_ptid);
    }
}