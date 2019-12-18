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
struct TYPE_4__ {int /*<<< orphan*/  (* to_post_attach ) (int) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_PID (int /*<<< orphan*/ ) ; 
 TYPE_2__ child_ops ; 
 int /*<<< orphan*/  fbsd_thread_activate () ; 
 int /*<<< orphan*/  fbsd_thread_active ; 
 scalar_t__ fbsd_thread_present ; 
 int /*<<< orphan*/  inferior_ptid ; 
 TYPE_1__ proc_handle ; 
 int /*<<< orphan*/  stub1 (int) ; 

__attribute__((used)) static void
fbsd_thread_post_attach (int pid)
{
  child_ops.to_post_attach (pid);

  if (fbsd_thread_present && !fbsd_thread_active)
    {
      proc_handle.pid = GET_PID (inferior_ptid);
      fbsd_thread_activate ();
    }
}