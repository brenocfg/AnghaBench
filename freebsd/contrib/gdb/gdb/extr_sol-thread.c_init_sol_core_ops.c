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
struct TYPE_2__ {char* to_shortname; char* to_longname; char* to_doc; int to_has_memory; int to_has_stack; int to_has_registers; int /*<<< orphan*/  to_magic; int /*<<< orphan*/  to_pid_to_str; int /*<<< orphan*/  to_thread_alive; int /*<<< orphan*/  to_has_thread_control; int /*<<< orphan*/  to_stratum; int /*<<< orphan*/  to_create_inferior; void* to_remove_breakpoint; void* to_insert_breakpoint; int /*<<< orphan*/  to_files_info; int /*<<< orphan*/  to_xfer_partial; int /*<<< orphan*/  to_xfer_memory; int /*<<< orphan*/  to_fetch_registers; int /*<<< orphan*/  to_detach; int /*<<< orphan*/  to_attach; int /*<<< orphan*/  to_close; int /*<<< orphan*/  to_open; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPS_MAGIC ; 
 int /*<<< orphan*/  core_stratum ; 
 void* ignore ; 
 int /*<<< orphan*/  sol_core_close ; 
 int /*<<< orphan*/  sol_core_detach ; 
 int /*<<< orphan*/  sol_core_files_info ; 
 int /*<<< orphan*/  sol_core_open ; 
 TYPE_1__ sol_core_ops ; 
 int /*<<< orphan*/  sol_thread_alive ; 
 int /*<<< orphan*/  sol_thread_attach ; 
 int /*<<< orphan*/  sol_thread_create_inferior ; 
 int /*<<< orphan*/  sol_thread_fetch_registers ; 
 int /*<<< orphan*/  sol_thread_xfer_memory ; 
 int /*<<< orphan*/  sol_thread_xfer_partial ; 
 int /*<<< orphan*/  solaris_pid_to_str ; 
 int /*<<< orphan*/  tc_none ; 

__attribute__((used)) static void
init_sol_core_ops (void)
{
  sol_core_ops.to_shortname = "solaris-core";
  sol_core_ops.to_longname = "Solaris core threads and pthread.";
  sol_core_ops.to_doc = "Solaris threads and pthread support for core files.";
  sol_core_ops.to_open = sol_core_open;
  sol_core_ops.to_close = sol_core_close;
  sol_core_ops.to_attach = sol_thread_attach;
  sol_core_ops.to_detach = sol_core_detach;
  sol_core_ops.to_fetch_registers = sol_thread_fetch_registers;
  sol_core_ops.to_xfer_memory = sol_thread_xfer_memory;
  sol_core_ops.to_xfer_partial = sol_thread_xfer_partial;
  sol_core_ops.to_files_info = sol_core_files_info;
  sol_core_ops.to_insert_breakpoint = ignore;
  sol_core_ops.to_remove_breakpoint = ignore;
  sol_core_ops.to_create_inferior = sol_thread_create_inferior;
  sol_core_ops.to_stratum = core_stratum;
  sol_core_ops.to_has_memory = 1;
  sol_core_ops.to_has_stack = 1;
  sol_core_ops.to_has_registers = 1;
  sol_core_ops.to_has_thread_control = tc_none;
  sol_core_ops.to_thread_alive = sol_thread_alive;
  sol_core_ops.to_pid_to_str = solaris_pid_to_str;
  /* On Solaris/x86, when debugging a threaded core file from process <n>,
     the following causes "info threads" to produce "procfs: couldn't find pid
     <n> in procinfo list" where <n> is the pid of the process that produced
     the core file.  Disable it for now. */
  /* sol_core_ops.to_find_new_threads = sol_find_new_threads; */
  sol_core_ops.to_magic = OPS_MAGIC;
}