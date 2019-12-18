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
struct TYPE_2__ {char* to_shortname; char* to_longname; char* to_doc; int /*<<< orphan*/  to_magic; int /*<<< orphan*/  to_get_thread_local_address; int /*<<< orphan*/  to_has_thread_control; int /*<<< orphan*/  to_stratum; int /*<<< orphan*/  to_pid_to_str; int /*<<< orphan*/  to_find_new_threads; int /*<<< orphan*/  to_thread_alive; int /*<<< orphan*/  to_mourn_inferior; int /*<<< orphan*/  to_post_startup_inferior; int /*<<< orphan*/  to_create_inferior; int /*<<< orphan*/  to_kill; int /*<<< orphan*/  to_xfer_memory; int /*<<< orphan*/  to_store_registers; int /*<<< orphan*/  to_fetch_registers; int /*<<< orphan*/  to_wait; int /*<<< orphan*/  to_resume; int /*<<< orphan*/  to_detach; int /*<<< orphan*/  to_attach; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPS_MAGIC ; 
 int /*<<< orphan*/  tc_schedlock ; 
 int /*<<< orphan*/  thread_db_attach ; 
 int /*<<< orphan*/  thread_db_create_inferior ; 
 int /*<<< orphan*/  thread_db_detach ; 
 int /*<<< orphan*/  thread_db_fetch_registers ; 
 int /*<<< orphan*/  thread_db_find_new_threads ; 
 int /*<<< orphan*/  thread_db_get_thread_local_address ; 
 int /*<<< orphan*/  thread_db_kill ; 
 int /*<<< orphan*/  thread_db_mourn_inferior ; 
 TYPE_1__ thread_db_ops ; 
 int /*<<< orphan*/  thread_db_pid_to_str ; 
 int /*<<< orphan*/  thread_db_post_startup_inferior ; 
 int /*<<< orphan*/  thread_db_resume ; 
 int /*<<< orphan*/  thread_db_store_registers ; 
 int /*<<< orphan*/  thread_db_thread_alive ; 
 int /*<<< orphan*/  thread_db_wait ; 
 int /*<<< orphan*/  thread_db_xfer_memory ; 
 int /*<<< orphan*/  thread_stratum ; 

__attribute__((used)) static void
init_thread_db_ops (void)
{
  thread_db_ops.to_shortname = "multi-thread";
  thread_db_ops.to_longname = "multi-threaded child process.";
  thread_db_ops.to_doc = "Threads and pthreads support.";
  thread_db_ops.to_attach = thread_db_attach;
  thread_db_ops.to_detach = thread_db_detach;
  thread_db_ops.to_resume = thread_db_resume;
  thread_db_ops.to_wait = thread_db_wait;
  thread_db_ops.to_fetch_registers = thread_db_fetch_registers;
  thread_db_ops.to_store_registers = thread_db_store_registers;
  thread_db_ops.to_xfer_memory = thread_db_xfer_memory;
  thread_db_ops.to_kill = thread_db_kill;
  thread_db_ops.to_create_inferior = thread_db_create_inferior;
  thread_db_ops.to_post_startup_inferior = thread_db_post_startup_inferior;
  thread_db_ops.to_mourn_inferior = thread_db_mourn_inferior;
  thread_db_ops.to_thread_alive = thread_db_thread_alive;
  thread_db_ops.to_find_new_threads = thread_db_find_new_threads;
  thread_db_ops.to_pid_to_str = thread_db_pid_to_str;
  thread_db_ops.to_stratum = thread_stratum;
  thread_db_ops.to_has_thread_control = tc_schedlock;
  thread_db_ops.to_get_thread_local_address
    = thread_db_get_thread_local_address;
  thread_db_ops.to_magic = OPS_MAGIC;
}