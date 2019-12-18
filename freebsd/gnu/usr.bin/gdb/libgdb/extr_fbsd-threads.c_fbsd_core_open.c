#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  core_pid; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* to_open ) (char*,int) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int TD_OK ; 
 int /*<<< orphan*/  core_bfd ; 
 TYPE_4__* elf_tdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fbsd_thread_activate () ; 
 int fbsd_thread_core ; 
 scalar_t__ fbsd_thread_present ; 
 TYPE_3__ orig_core_ops ; 
 TYPE_1__ proc_handle ; 
 int /*<<< orphan*/  stub1 (char*,int) ; 
 int td_ta_new_p (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_agent ; 
 int /*<<< orphan*/  thread_db_err_str (int) ; 

__attribute__((used)) static void
fbsd_core_open (char *filename, int from_tty)
{
  int err;

  fbsd_thread_core = 1;

  orig_core_ops.to_open (filename, from_tty);

  if (fbsd_thread_present)
    {
      err = td_ta_new_p (&proc_handle, &thread_agent);
      if (err == TD_OK)
        {
          proc_handle.pid = elf_tdata (core_bfd)->core_pid;
          fbsd_thread_activate ();
        }
      else
        error ("fbsd_core_open: td_ta_new: %s", thread_db_err_str (err));
    }
}