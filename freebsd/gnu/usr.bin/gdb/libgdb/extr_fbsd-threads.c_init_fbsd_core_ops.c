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
struct TYPE_2__ {char* to_shortname; char* to_longname; char* to_doc; int to_has_memory; int to_has_stack; int to_has_registers; int /*<<< orphan*/  to_magic; scalar_t__ to_sections_end; scalar_t__ to_sections; int /*<<< orphan*/  to_find_new_threads; int /*<<< orphan*/  to_pid_to_str; int /*<<< orphan*/  to_thread_alive; int /*<<< orphan*/  to_has_thread_control; scalar_t__ to_has_execution; scalar_t__ to_has_all_memory; int /*<<< orphan*/  to_stratum; int /*<<< orphan*/  to_create_inferior; void* to_remove_breakpoint; void* to_insert_breakpoint; int /*<<< orphan*/  to_files_info; int /*<<< orphan*/  to_xfer_memory; int /*<<< orphan*/  to_fetch_registers; int /*<<< orphan*/  to_detach; scalar_t__ to_post_attach; scalar_t__ to_attach; int /*<<< orphan*/  to_close; int /*<<< orphan*/  to_open; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPS_MAGIC ; 
 int /*<<< orphan*/  core_stratum ; 
 int /*<<< orphan*/  fbsd_core_close ; 
 int /*<<< orphan*/  fbsd_core_detach ; 
 int /*<<< orphan*/  fbsd_core_files_info ; 
 int /*<<< orphan*/  fbsd_core_open ; 
 TYPE_1__ fbsd_core_ops ; 
 int /*<<< orphan*/  fbsd_thread_alive ; 
 int /*<<< orphan*/  fbsd_thread_create_inferior ; 
 int /*<<< orphan*/  fbsd_thread_fetch_registers ; 
 int /*<<< orphan*/  fbsd_thread_find_new_threads ; 
 int /*<<< orphan*/  fbsd_thread_pid_to_str ; 
 int /*<<< orphan*/  fbsd_thread_xfer_memory ; 
 void* ignore ; 
 int /*<<< orphan*/  tc_none ; 

__attribute__((used)) static void
init_fbsd_core_ops (void)
{
  fbsd_core_ops.to_shortname = "FreeBSD-core";
  fbsd_core_ops.to_longname = "FreeBSD multithreaded core dump file";
  fbsd_core_ops.to_doc =
    "Use a core file as a target.  Specify the filename of the core file.";
  fbsd_core_ops.to_open = fbsd_core_open;
  fbsd_core_ops.to_close = fbsd_core_close;
  fbsd_core_ops.to_attach = 0;
  fbsd_core_ops.to_post_attach = 0;
  fbsd_core_ops.to_detach = fbsd_core_detach;
  /* fbsd_core_ops.to_resume  = 0; */
  /* fbsd_core_ops.to_wait  = 0;  */
  fbsd_core_ops.to_fetch_registers = fbsd_thread_fetch_registers;
  /* fbsd_core_ops.to_store_registers  = 0; */
  /* fbsd_core_ops.to_prepare_to_store  = 0; */
  fbsd_core_ops.to_xfer_memory = fbsd_thread_xfer_memory;
  fbsd_core_ops.to_files_info = fbsd_core_files_info;
  fbsd_core_ops.to_insert_breakpoint = ignore;
  fbsd_core_ops.to_remove_breakpoint = ignore;
  /* fbsd_core_ops.to_lookup_symbol  = 0; */
  fbsd_core_ops.to_create_inferior = fbsd_thread_create_inferior;
  fbsd_core_ops.to_stratum = core_stratum;
  fbsd_core_ops.to_has_all_memory = 0;
  fbsd_core_ops.to_has_memory = 1;
  fbsd_core_ops.to_has_stack = 1;
  fbsd_core_ops.to_has_registers = 1;
  fbsd_core_ops.to_has_execution = 0;
  fbsd_core_ops.to_has_thread_control = tc_none;
  fbsd_core_ops.to_thread_alive = fbsd_thread_alive;
  fbsd_core_ops.to_pid_to_str = fbsd_thread_pid_to_str;
  fbsd_core_ops.to_find_new_threads = fbsd_thread_find_new_threads;
  fbsd_core_ops.to_sections = 0;
  fbsd_core_ops.to_sections_end = 0;
  fbsd_core_ops.to_magic = OPS_MAGIC;
}