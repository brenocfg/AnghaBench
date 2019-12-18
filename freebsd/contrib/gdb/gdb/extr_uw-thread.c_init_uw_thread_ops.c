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
struct TYPE_2__ {char* to_shortname; char* to_longname; char* to_doc; int /*<<< orphan*/  to_magic; int /*<<< orphan*/  to_stratum; int /*<<< orphan*/  to_extra_thread_info; int /*<<< orphan*/  to_pid_to_str; int /*<<< orphan*/  to_find_new_threads; int /*<<< orphan*/  to_thread_alive; int /*<<< orphan*/  to_can_run; int /*<<< orphan*/  to_mourn_inferior; int /*<<< orphan*/  to_kill; int /*<<< orphan*/  to_create_inferior; int /*<<< orphan*/  to_prepare_to_store; int /*<<< orphan*/  to_store_registers; int /*<<< orphan*/  to_fetch_registers; int /*<<< orphan*/  to_wait; int /*<<< orphan*/  to_resume; int /*<<< orphan*/  to_detach; int /*<<< orphan*/  to_attach; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPS_MAGIC ; 
 int /*<<< orphan*/  thread_stratum ; 
 int /*<<< orphan*/  uw_extra_thread_info ; 
 int /*<<< orphan*/  uw_thread_alive ; 
 int /*<<< orphan*/  uw_thread_attach ; 
 int /*<<< orphan*/  uw_thread_can_run ; 
 int /*<<< orphan*/  uw_thread_create_inferior ; 
 int /*<<< orphan*/  uw_thread_detach ; 
 int /*<<< orphan*/  uw_thread_fetch_registers ; 
 int /*<<< orphan*/  uw_thread_find_new_threads ; 
 int /*<<< orphan*/  uw_thread_kill ; 
 int /*<<< orphan*/  uw_thread_mourn_inferior ; 
 TYPE_1__ uw_thread_ops ; 
 int /*<<< orphan*/  uw_thread_pid_to_str ; 
 int /*<<< orphan*/  uw_thread_prepare_to_store ; 
 int /*<<< orphan*/  uw_thread_resume ; 
 int /*<<< orphan*/  uw_thread_store_registers ; 
 int /*<<< orphan*/  uw_thread_wait ; 

__attribute__((used)) static void
init_uw_thread_ops (void)
{
  uw_thread_ops.to_shortname          = "unixware-threads";
  uw_thread_ops.to_longname           = "UnixWare threads and pthread.";
  uw_thread_ops.to_doc        = "UnixWare threads and pthread support.";
  uw_thread_ops.to_attach             = uw_thread_attach;
  uw_thread_ops.to_detach             = uw_thread_detach;
  uw_thread_ops.to_resume             = uw_thread_resume;
  uw_thread_ops.to_wait               = uw_thread_wait;
  uw_thread_ops.to_fetch_registers    = uw_thread_fetch_registers;
  uw_thread_ops.to_store_registers    = uw_thread_store_registers;
  uw_thread_ops.to_prepare_to_store   = uw_thread_prepare_to_store;
  uw_thread_ops.to_create_inferior    = uw_thread_create_inferior;
  uw_thread_ops.to_kill               = uw_thread_kill;
  uw_thread_ops.to_mourn_inferior     = uw_thread_mourn_inferior;
  uw_thread_ops.to_can_run            = uw_thread_can_run;
  uw_thread_ops.to_thread_alive       = uw_thread_alive;
  uw_thread_ops.to_find_new_threads   = uw_thread_find_new_threads;
  uw_thread_ops.to_pid_to_str         = uw_thread_pid_to_str;
  uw_thread_ops.to_extra_thread_info  = uw_extra_thread_info;
  uw_thread_ops.to_stratum            = thread_stratum;
  uw_thread_ops.to_magic              = OPS_MAGIC;
}