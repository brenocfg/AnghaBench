#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  aux_binlog_check_updates () ; 
 int /*<<< orphan*/  flush_binlog () ; 
 int /*<<< orphan*/  interrupted_by_signal () ; 
 int /*<<< orphan*/  transaction_check_auto_status () ; 
 int /*<<< orphan*/  transaction_check_child_status () ; 

void cron (void) {
  flush_binlog ();
  //dyn_garbage_collector ();
  if (!interrupted_by_signal ()) {
    aux_binlog_check_updates ();
  }
  transaction_check_child_status ();
  transaction_check_auto_status ();
}