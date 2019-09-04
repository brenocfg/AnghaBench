#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct proc_data {TYPE_1__* uinfo; } ;
struct TYPE_5__ {int rescan_binlog_table; scalar_t__ rescan_pid_table; } ;
struct TYPE_6__ {TYPE_2__ e_hdr; } ;
struct TYPE_4__ {int pid; scalar_t__ start_utime; int flags; } ;

/* Variables and functions */
 int CDATA_PIDS ; 
 int CD_ZOMBIE ; 
 TYPE_3__* CData ; 
 int* active_pids ; 
 int active_pnum ; 
 scalar_t__ am_monitor ; 
 int /*<<< orphan*/  assert (struct proc_data*) ; 
 struct proc_data* get_proc_status (int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int* prev_active_pids ; 
 int /*<<< orphan*/  vkprintf (int,char*,int) ; 

int rescan_pid_table (void) {
  int i, j = 0, k = 0;
  if (!CData) {
    return -1;
  }
  if (am_monitor) {
    CData->e_hdr.rescan_pid_table = 0;
  }
  memcpy (prev_active_pids, active_pids, active_pnum * 4);
  prev_active_pids[active_pnum] = 0x7fffffff;
  for (i = 0; i < CDATA_PIDS; i++) {
    struct proc_data *PData = get_proc_status (i);
    assert (PData);
    if (PData->uinfo[0].pid == i && PData->uinfo[1].pid == i && PData->uinfo[0].start_utime > 0 && PData->uinfo[1].start_utime == PData->uinfo[0].start_utime && !(PData->uinfo[0].flags & CD_ZOMBIE) && !(PData->uinfo[1].flags & CD_ZOMBIE)) {
      // i is a good process
      while (prev_active_pids[j] < i) {
	vkprintf (1, "monitor: process %d deleted\n", prev_active_pids[j]);
	j++;
	CData->e_hdr.rescan_binlog_table = 1;
      }
      if (prev_active_pids[j] == i) {
	j++;
      } else {
	vkprintf (1, "monitor: found new process %d\n", i);
      }
      active_pids[k++] = i;
    }
  }
  while (prev_active_pids[j] < 0x7fffffff) {
    vkprintf (1, "monitor: process %d deleted\n", prev_active_pids[j]);
    j++;
    CData->e_hdr.rescan_binlog_table = 1;
  }
  active_pnum = k;
  active_pids[k] = 0x7fffffff;
  return k;
}