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
struct TYPE_2__ {char* to_shortname; char* to_longname; char* to_doc; int to_has_all_memory; int to_has_memory; int to_has_stack; int to_has_registers; int to_has_execution; int /*<<< orphan*/  to_magic; int /*<<< orphan*/  to_stratum; int /*<<< orphan*/  to_stop; int /*<<< orphan*/  to_pid_to_str; int /*<<< orphan*/  to_thread_alive; int /*<<< orphan*/  to_can_run; int /*<<< orphan*/  to_mourn_inferior; int /*<<< orphan*/  to_create_inferior; int /*<<< orphan*/  to_kill; int /*<<< orphan*/  to_terminal_info; int /*<<< orphan*/  to_terminal_save_ours; int /*<<< orphan*/  to_terminal_ours; int /*<<< orphan*/  to_terminal_ours_for_output; int /*<<< orphan*/  to_terminal_inferior; int /*<<< orphan*/  to_terminal_init; int /*<<< orphan*/  to_remove_breakpoint; int /*<<< orphan*/  to_insert_breakpoint; int /*<<< orphan*/  to_files_info; int /*<<< orphan*/  to_xfer_memory; int /*<<< orphan*/  to_prepare_to_store; int /*<<< orphan*/  to_store_registers; int /*<<< orphan*/  to_fetch_registers; int /*<<< orphan*/  to_wait; int /*<<< orphan*/  to_resume; int /*<<< orphan*/  to_detach; int /*<<< orphan*/  to_attach; int /*<<< orphan*/  to_close; int /*<<< orphan*/  to_open; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPS_MAGIC ; 
 int /*<<< orphan*/  child_attach ; 
 int /*<<< orphan*/  child_can_run ; 
 int /*<<< orphan*/  child_close ; 
 int /*<<< orphan*/  child_create_inferior ; 
 int /*<<< orphan*/  child_detach ; 
 int /*<<< orphan*/  child_fetch_inferior_registers ; 
 int /*<<< orphan*/  child_files_info ; 
 int /*<<< orphan*/  child_kill_inferior ; 
 int /*<<< orphan*/  child_mourn_inferior ; 
 int /*<<< orphan*/  child_open ; 
 TYPE_1__ child_ops ; 
 int /*<<< orphan*/  child_prepare_to_store ; 
 int /*<<< orphan*/  child_resume ; 
 int /*<<< orphan*/  child_stop ; 
 int /*<<< orphan*/  child_store_inferior_registers ; 
 int /*<<< orphan*/  child_terminal_info ; 
 int /*<<< orphan*/  child_wait ; 
 int /*<<< orphan*/  child_xfer_memory ; 
 int /*<<< orphan*/  cygwin_pid_to_str ; 
 int /*<<< orphan*/  memory_insert_breakpoint ; 
 int /*<<< orphan*/  memory_remove_breakpoint ; 
 int /*<<< orphan*/  process_stratum ; 
 int /*<<< orphan*/  terminal_inferior ; 
 int /*<<< orphan*/  terminal_init_inferior ; 
 int /*<<< orphan*/  terminal_ours ; 
 int /*<<< orphan*/  terminal_ours_for_output ; 
 int /*<<< orphan*/  terminal_save_ours ; 
 int /*<<< orphan*/  win32_child_thread_alive ; 

__attribute__((used)) static void
init_child_ops (void)
{
  child_ops.to_shortname = "child";
  child_ops.to_longname = "Win32 child process";
  child_ops.to_doc = "Win32 child process (started by the \"run\" command).";
  child_ops.to_open = child_open;
  child_ops.to_close = child_close;
  child_ops.to_attach = child_attach;
  child_ops.to_detach = child_detach;
  child_ops.to_resume = child_resume;
  child_ops.to_wait = child_wait;
  child_ops.to_fetch_registers = child_fetch_inferior_registers;
  child_ops.to_store_registers = child_store_inferior_registers;
  child_ops.to_prepare_to_store = child_prepare_to_store;
  child_ops.to_xfer_memory = child_xfer_memory;
  child_ops.to_files_info = child_files_info;
  child_ops.to_insert_breakpoint = memory_insert_breakpoint;
  child_ops.to_remove_breakpoint = memory_remove_breakpoint;
  child_ops.to_terminal_init = terminal_init_inferior;
  child_ops.to_terminal_inferior = terminal_inferior;
  child_ops.to_terminal_ours_for_output = terminal_ours_for_output;
  child_ops.to_terminal_ours = terminal_ours;
  child_ops.to_terminal_save_ours = terminal_save_ours;
  child_ops.to_terminal_info = child_terminal_info;
  child_ops.to_kill = child_kill_inferior;
  child_ops.to_create_inferior = child_create_inferior;
  child_ops.to_mourn_inferior = child_mourn_inferior;
  child_ops.to_can_run = child_can_run;
  child_ops.to_thread_alive = win32_child_thread_alive;
  child_ops.to_pid_to_str = cygwin_pid_to_str;
  child_ops.to_stop = child_stop;
  child_ops.to_stratum = process_stratum;
  child_ops.to_has_all_memory = 1;
  child_ops.to_has_memory = 1;
  child_ops.to_has_stack = 1;
  child_ops.to_has_registers = 1;
  child_ops.to_has_execution = 1;
  child_ops.to_magic = OPS_MAGIC;
}