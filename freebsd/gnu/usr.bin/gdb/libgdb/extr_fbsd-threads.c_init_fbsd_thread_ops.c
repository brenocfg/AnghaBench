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
struct TYPE_2__ {char* to_shortname; char* to_longname; char* to_doc; int to_has_all_memory; int to_has_memory; int to_has_stack; int to_has_registers; int to_has_execution; int /*<<< orphan*/  to_magic; int /*<<< orphan*/  to_get_thread_local_address; int /*<<< orphan*/  to_remove_breakpoint; int /*<<< orphan*/  to_insert_breakpoint; int /*<<< orphan*/  to_has_thread_control; int /*<<< orphan*/  to_stratum; int /*<<< orphan*/  to_pid_to_str; int /*<<< orphan*/  to_find_new_threads; int /*<<< orphan*/  to_thread_alive; int /*<<< orphan*/  to_can_run; int /*<<< orphan*/  to_mourn_inferior; int /*<<< orphan*/  to_post_startup_inferior; int /*<<< orphan*/  to_create_inferior; int /*<<< orphan*/  to_kill; int /*<<< orphan*/  to_files_info; int /*<<< orphan*/  to_xfer_memory; int /*<<< orphan*/  to_store_registers; int /*<<< orphan*/  to_fetch_registers; int /*<<< orphan*/  to_wait; int /*<<< orphan*/  to_resume; int /*<<< orphan*/  to_post_attach; int /*<<< orphan*/  to_detach; int /*<<< orphan*/  to_attach; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPS_MAGIC ; 
 int /*<<< orphan*/  fbsd_thread_alive ; 
 int /*<<< orphan*/  fbsd_thread_attach ; 
 int /*<<< orphan*/  fbsd_thread_can_run ; 
 int /*<<< orphan*/  fbsd_thread_create_inferior ; 
 int /*<<< orphan*/  fbsd_thread_detach ; 
 int /*<<< orphan*/  fbsd_thread_fetch_registers ; 
 int /*<<< orphan*/  fbsd_thread_files_info ; 
 int /*<<< orphan*/  fbsd_thread_find_new_threads ; 
 int /*<<< orphan*/  fbsd_thread_get_local_address ; 
 int /*<<< orphan*/  fbsd_thread_kill ; 
 int /*<<< orphan*/  fbsd_thread_mourn_inferior ; 
 TYPE_1__ fbsd_thread_ops ; 
 int /*<<< orphan*/  fbsd_thread_pid_to_str ; 
 int /*<<< orphan*/  fbsd_thread_post_attach ; 
 int /*<<< orphan*/  fbsd_thread_post_startup_inferior ; 
 int /*<<< orphan*/  fbsd_thread_resume ; 
 int /*<<< orphan*/  fbsd_thread_store_registers ; 
 int /*<<< orphan*/  fbsd_thread_wait ; 
 int /*<<< orphan*/  fbsd_thread_xfer_memory ; 
 int /*<<< orphan*/  memory_insert_breakpoint ; 
 int /*<<< orphan*/  memory_remove_breakpoint ; 
 int /*<<< orphan*/  tc_none ; 
 int /*<<< orphan*/  thread_stratum ; 

__attribute__((used)) static void
init_fbsd_thread_ops (void)
{
  fbsd_thread_ops.to_shortname = "freebsd-threads";
  fbsd_thread_ops.to_longname = "FreeBSD multithreaded child process.";
  fbsd_thread_ops.to_doc = "FreeBSD threads support.";
  fbsd_thread_ops.to_attach = fbsd_thread_attach;
  fbsd_thread_ops.to_detach = fbsd_thread_detach;
  fbsd_thread_ops.to_post_attach = fbsd_thread_post_attach;
  fbsd_thread_ops.to_resume = fbsd_thread_resume;
  fbsd_thread_ops.to_wait = fbsd_thread_wait;
  fbsd_thread_ops.to_fetch_registers = fbsd_thread_fetch_registers;
  fbsd_thread_ops.to_store_registers = fbsd_thread_store_registers;
  fbsd_thread_ops.to_xfer_memory = fbsd_thread_xfer_memory;
  fbsd_thread_ops.to_files_info = fbsd_thread_files_info;
  fbsd_thread_ops.to_kill = fbsd_thread_kill;
  fbsd_thread_ops.to_create_inferior = fbsd_thread_create_inferior;
  fbsd_thread_ops.to_post_startup_inferior = fbsd_thread_post_startup_inferior;
  fbsd_thread_ops.to_mourn_inferior = fbsd_thread_mourn_inferior;
  fbsd_thread_ops.to_can_run = fbsd_thread_can_run;
  fbsd_thread_ops.to_thread_alive = fbsd_thread_alive;
  fbsd_thread_ops.to_find_new_threads = fbsd_thread_find_new_threads;
  fbsd_thread_ops.to_pid_to_str = fbsd_thread_pid_to_str;
  fbsd_thread_ops.to_stratum = thread_stratum;
  fbsd_thread_ops.to_has_thread_control = tc_none;
  fbsd_thread_ops.to_has_all_memory = 1;
  fbsd_thread_ops.to_has_memory = 1;
  fbsd_thread_ops.to_has_stack = 1;
  fbsd_thread_ops.to_has_registers = 1;
  fbsd_thread_ops.to_has_execution = 1;
  fbsd_thread_ops.to_insert_breakpoint = memory_insert_breakpoint;
  fbsd_thread_ops.to_remove_breakpoint = memory_remove_breakpoint;
  fbsd_thread_ops.to_get_thread_local_address = fbsd_thread_get_local_address;
  fbsd_thread_ops.to_magic = OPS_MAGIC;
}