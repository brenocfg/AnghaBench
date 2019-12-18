#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* to_shortname; char* to_longname; char* to_doc; int to_has_memory; int to_has_registers; int to_has_stack; void* to_remove_breakpoint; void* to_insert_breakpoint; int /*<<< orphan*/  to_xfer_memory; int /*<<< orphan*/  to_thread_alive; int /*<<< orphan*/  to_store_registers; int /*<<< orphan*/  to_pid_to_str; int /*<<< orphan*/  to_find_new_threads; int /*<<< orphan*/  to_files_info; int /*<<< orphan*/  to_fetch_registers; int /*<<< orphan*/  to_extra_thread_info; int /*<<< orphan*/  to_detach; int /*<<< orphan*/  to_attach; int /*<<< orphan*/  to_close; int /*<<< orphan*/  to_open; int /*<<< orphan*/  to_stratum; int /*<<< orphan*/  to_magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPS_MAGIC ; 
 int /*<<< orphan*/  add_com (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  add_target (TYPE_1__*) ; 
 int /*<<< orphan*/  class_obscure ; 
 int /*<<< orphan*/  core_stratum ; 
 int /*<<< orphan*/  find_default_attach ; 
 int /*<<< orphan*/  kgdb_set_proc_cmd ; 
 int /*<<< orphan*/  kgdb_set_tid_cmd ; 
 int /*<<< orphan*/  kgdb_trgt_close ; 
 int /*<<< orphan*/  kgdb_trgt_detach ; 
 int /*<<< orphan*/  kgdb_trgt_extra_thread_info ; 
 int /*<<< orphan*/  kgdb_trgt_fetch_registers ; 
 int /*<<< orphan*/  kgdb_trgt_files_info ; 
 int /*<<< orphan*/  kgdb_trgt_find_new_threads ; 
 void* kgdb_trgt_ignore_breakpoints ; 
 int /*<<< orphan*/  kgdb_trgt_open ; 
 TYPE_1__ kgdb_trgt_ops ; 
 int /*<<< orphan*/  kgdb_trgt_pid_to_str ; 
 int /*<<< orphan*/  kgdb_trgt_store_registers ; 
 int /*<<< orphan*/  kgdb_trgt_thread_alive ; 
 int /*<<< orphan*/  kgdb_trgt_xfer_memory ; 

void
initialize_kgdb_target(void)
{

	kgdb_trgt_ops.to_magic = OPS_MAGIC;
	kgdb_trgt_ops.to_shortname = "kernel";
	kgdb_trgt_ops.to_longname = "kernel core dump file";
	kgdb_trgt_ops.to_doc = 
    "Use a vmcore file as a target.  Specify the filename of the vmcore file.";
	kgdb_trgt_ops.to_stratum = core_stratum;
	kgdb_trgt_ops.to_has_memory = 1;
	kgdb_trgt_ops.to_has_registers = 1;
	kgdb_trgt_ops.to_has_stack = 1;

	kgdb_trgt_ops.to_open = kgdb_trgt_open;
	kgdb_trgt_ops.to_close = kgdb_trgt_close;
	kgdb_trgt_ops.to_attach = find_default_attach;
	kgdb_trgt_ops.to_detach = kgdb_trgt_detach;
	kgdb_trgt_ops.to_extra_thread_info = kgdb_trgt_extra_thread_info;
	kgdb_trgt_ops.to_fetch_registers = kgdb_trgt_fetch_registers;
	kgdb_trgt_ops.to_files_info = kgdb_trgt_files_info;
	kgdb_trgt_ops.to_find_new_threads = kgdb_trgt_find_new_threads;
	kgdb_trgt_ops.to_pid_to_str = kgdb_trgt_pid_to_str;
	kgdb_trgt_ops.to_store_registers = kgdb_trgt_store_registers;
	kgdb_trgt_ops.to_thread_alive = kgdb_trgt_thread_alive;
	kgdb_trgt_ops.to_xfer_memory = kgdb_trgt_xfer_memory;
	kgdb_trgt_ops.to_insert_breakpoint = kgdb_trgt_ignore_breakpoints;
	kgdb_trgt_ops.to_remove_breakpoint = kgdb_trgt_ignore_breakpoints;

	add_target(&kgdb_trgt_ops);

	add_com ("proc", class_obscure, kgdb_set_proc_cmd,
	   "Set current process context");
	add_com ("tid", class_obscure, kgdb_set_tid_cmd,
	   "Set current thread context");
}