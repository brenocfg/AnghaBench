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
struct TYPE_2__ {char* to_shortname; char* to_longname; char* to_doc; int to_has_all_memory; int to_has_memory; int to_has_stack; int to_has_registers; int to_has_execution; int /*<<< orphan*/  to_magic; int /*<<< orphan*/  to_make_corefile_notes; int /*<<< orphan*/  to_find_memory_regions; int /*<<< orphan*/  to_has_thread_control; int /*<<< orphan*/  to_stratum; int /*<<< orphan*/  to_stop; int /*<<< orphan*/  to_find_new_threads; int /*<<< orphan*/  to_pid_to_str; int /*<<< orphan*/  to_thread_alive; int /*<<< orphan*/  to_notice_signals; int /*<<< orphan*/  to_can_run; int /*<<< orphan*/  to_mourn_inferior; int /*<<< orphan*/  to_create_inferior; int /*<<< orphan*/  to_kill; int /*<<< orphan*/  to_terminal_info; int /*<<< orphan*/  to_terminal_save_ours; int /*<<< orphan*/  to_terminal_ours; int /*<<< orphan*/  to_terminal_ours_for_output; int /*<<< orphan*/  to_terminal_inferior; int /*<<< orphan*/  to_terminal_init; int /*<<< orphan*/  to_remove_breakpoint; int /*<<< orphan*/  to_insert_breakpoint; int /*<<< orphan*/  to_files_info; int /*<<< orphan*/  to_xfer_partial; int /*<<< orphan*/  to_xfer_memory; int /*<<< orphan*/  to_prepare_to_store; int /*<<< orphan*/  to_store_registers; int /*<<< orphan*/  to_fetch_registers; int /*<<< orphan*/  to_wait; int /*<<< orphan*/  to_resume; int /*<<< orphan*/  to_detach; int /*<<< orphan*/  to_attach; int /*<<< orphan*/  to_open; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPS_MAGIC ; 
 int /*<<< orphan*/  child_terminal_info ; 
 int /*<<< orphan*/  memory_insert_breakpoint ; 
 int /*<<< orphan*/  memory_remove_breakpoint ; 
 int /*<<< orphan*/  process_stratum ; 
 int /*<<< orphan*/  sol_find_memory_regions ; 
 int /*<<< orphan*/  sol_find_new_threads ; 
 int /*<<< orphan*/  sol_make_note_section ; 
 int /*<<< orphan*/  sol_thread_alive ; 
 int /*<<< orphan*/  sol_thread_attach ; 
 int /*<<< orphan*/  sol_thread_can_run ; 
 int /*<<< orphan*/  sol_thread_create_inferior ; 
 int /*<<< orphan*/  sol_thread_detach ; 
 int /*<<< orphan*/  sol_thread_fetch_registers ; 
 int /*<<< orphan*/  sol_thread_files_info ; 
 int /*<<< orphan*/  sol_thread_kill_inferior ; 
 int /*<<< orphan*/  sol_thread_mourn_inferior ; 
 int /*<<< orphan*/  sol_thread_notice_signals ; 
 int /*<<< orphan*/  sol_thread_open ; 
 TYPE_1__ sol_thread_ops ; 
 int /*<<< orphan*/  sol_thread_prepare_to_store ; 
 int /*<<< orphan*/  sol_thread_resume ; 
 int /*<<< orphan*/  sol_thread_stop ; 
 int /*<<< orphan*/  sol_thread_store_registers ; 
 int /*<<< orphan*/  sol_thread_wait ; 
 int /*<<< orphan*/  sol_thread_xfer_memory ; 
 int /*<<< orphan*/  sol_thread_xfer_partial ; 
 int /*<<< orphan*/  solaris_pid_to_str ; 
 int /*<<< orphan*/  tc_none ; 
 int /*<<< orphan*/  terminal_inferior ; 
 int /*<<< orphan*/  terminal_init_inferior ; 
 int /*<<< orphan*/  terminal_ours ; 
 int /*<<< orphan*/  terminal_ours_for_output ; 
 int /*<<< orphan*/  terminal_save_ours ; 

__attribute__((used)) static void
init_sol_thread_ops (void)
{
  sol_thread_ops.to_shortname = "solaris-threads";
  sol_thread_ops.to_longname = "Solaris threads and pthread.";
  sol_thread_ops.to_doc = "Solaris threads and pthread support.";
  sol_thread_ops.to_open = sol_thread_open;
  sol_thread_ops.to_attach = sol_thread_attach;
  sol_thread_ops.to_detach = sol_thread_detach;
  sol_thread_ops.to_resume = sol_thread_resume;
  sol_thread_ops.to_wait = sol_thread_wait;
  sol_thread_ops.to_fetch_registers = sol_thread_fetch_registers;
  sol_thread_ops.to_store_registers = sol_thread_store_registers;
  sol_thread_ops.to_prepare_to_store = sol_thread_prepare_to_store;
  sol_thread_ops.to_xfer_memory = sol_thread_xfer_memory;
  sol_thread_ops.to_xfer_partial = sol_thread_xfer_partial;
  sol_thread_ops.to_files_info = sol_thread_files_info;
  sol_thread_ops.to_insert_breakpoint = memory_insert_breakpoint;
  sol_thread_ops.to_remove_breakpoint = memory_remove_breakpoint;
  sol_thread_ops.to_terminal_init = terminal_init_inferior;
  sol_thread_ops.to_terminal_inferior = terminal_inferior;
  sol_thread_ops.to_terminal_ours_for_output = terminal_ours_for_output;
  sol_thread_ops.to_terminal_ours = terminal_ours;
  sol_thread_ops.to_terminal_save_ours = terminal_save_ours;
  sol_thread_ops.to_terminal_info = child_terminal_info;
  sol_thread_ops.to_kill = sol_thread_kill_inferior;
  sol_thread_ops.to_create_inferior = sol_thread_create_inferior;
  sol_thread_ops.to_mourn_inferior = sol_thread_mourn_inferior;
  sol_thread_ops.to_can_run = sol_thread_can_run;
  sol_thread_ops.to_notice_signals = sol_thread_notice_signals;
  sol_thread_ops.to_thread_alive = sol_thread_alive;
  sol_thread_ops.to_pid_to_str = solaris_pid_to_str;
  sol_thread_ops.to_find_new_threads = sol_find_new_threads;
  sol_thread_ops.to_stop = sol_thread_stop;
  sol_thread_ops.to_stratum = process_stratum;
  sol_thread_ops.to_has_all_memory = 1;
  sol_thread_ops.to_has_memory = 1;
  sol_thread_ops.to_has_stack = 1;
  sol_thread_ops.to_has_registers = 1;
  sol_thread_ops.to_has_execution = 1;
  sol_thread_ops.to_has_thread_control = tc_none;
  sol_thread_ops.to_find_memory_regions = sol_find_memory_regions;
  sol_thread_ops.to_make_corefile_notes = sol_make_note_section;
  sol_thread_ops.to_magic = OPS_MAGIC;
}