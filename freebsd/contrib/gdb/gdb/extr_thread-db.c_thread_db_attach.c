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
struct TYPE_4__ {int /*<<< orphan*/  pid; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* to_attach ) (char*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GET_PID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_thread_event_reporting () ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  init_thread_list () ; 
 TYPE_2__ proc_handle ; 
 int /*<<< orphan*/  stub1 (char*,int) ; 
 TYPE_1__* target_beneath ; 
 int /*<<< orphan*/  thread_db_find_new_threads () ; 

__attribute__((used)) static void
thread_db_attach (char *args, int from_tty)
{
  target_beneath->to_attach (args, from_tty);

  /* Destroy thread info; it's no longer valid.  */
  init_thread_list ();

  /* The child process is now the actual multi-threaded
     program.  Snatch its process ID...  */
  proc_handle.pid = GET_PID (inferior_ptid);

  /* ...and perform the remaining initialization steps.  */
  enable_thread_event_reporting ();
  thread_db_find_new_threads ();
}