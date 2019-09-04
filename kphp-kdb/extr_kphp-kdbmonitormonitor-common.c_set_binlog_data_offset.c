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
struct proc_monitor_info {long long updated_at; int binlog_data_offset; } ;
struct proc_data {struct proc_monitor_info* minfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct proc_data*) ; 
 int /*<<< orphan*/  begin_update_monitor_data (struct proc_monitor_info*) ; 
 int /*<<< orphan*/  end_update_monitor_data (struct proc_monitor_info*) ; 
 long long get_precise_time (int) ; 

int set_binlog_data_offset (struct proc_data *PData, int binlog_data_offset) {
  assert (PData);

  long long updated_at = get_precise_time (1000000);

  int i;
  for (i = 0; i < 2; i++) {
    struct proc_monitor_info *S = PData->minfo + i;
    begin_update_monitor_data (S);
    S->updated_at = updated_at;
    S->binlog_data_offset = binlog_data_offset;
    end_update_monitor_data (S);
  }

  return 0;
}