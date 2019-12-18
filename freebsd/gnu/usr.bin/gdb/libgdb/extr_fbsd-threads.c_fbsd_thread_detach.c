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
struct TYPE_4__ {int /*<<< orphan*/  (* to_detach ) (char*,int) ;} ;
struct TYPE_3__ {scalar_t__ pid; } ;

/* Variables and functions */
 TYPE_2__ child_ops ; 
 int /*<<< orphan*/  clear_solib () ; 
 int /*<<< orphan*/  fbsd_thread_deactivate () ; 
 int /*<<< orphan*/  fbsd_thread_ops ; 
 TYPE_1__ proc_handle ; 
 int /*<<< orphan*/  stub1 (char*,int) ; 
 int /*<<< orphan*/  symbol_file_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unpush_target (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
fbsd_thread_detach (char *args, int from_tty)
{
  fbsd_thread_deactivate ();
  unpush_target (&fbsd_thread_ops);

  /* Clear gdb solib information and symbol file
     cache, so that after detach and re-attach, new_objfile
     hook will be called */

  clear_solib();
  symbol_file_clear(0);
  proc_handle.pid = 0;
  child_ops.to_detach (args, from_tty);
}