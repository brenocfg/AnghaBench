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
typedef  int /*<<< orphan*/  volume_t ;

/* Variables and functions */
 int /*<<< orphan*/ ** Volumes ; 
 scalar_t__ active_gathers ; 
 int child_pid ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ force_write_index ; 
 int fork () ; 
 int /*<<< orphan*/  kprintf (char*) ; 
 scalar_t__ save_index (int /*<<< orphan*/ *) ; 
 int save_index_process ; 
 int /*<<< orphan*/  vkprintf (int,char*,int) ; 
 int volumes ; 

void fork_write_index (void) {
  if (child_pid) {
    vkprintf (1, "process with pid %d already generates index, skipping\n", child_pid);
    return;
  }
  if (active_gathers > 0) {
    vkprintf (1, "active_gathers = %d, skipping(waiting) generating index\n", active_gathers);
    return;
  }
  //flush_binlog_ts ();
  int res = fork ();
  if (res < 0) {
    kprintf ("fork: %m\n");
  } else if (!res) {
    int i, res = 0;
    //binlogname = 0;
    save_index_process = 1;
    for (i = 0; i < volumes; i++) {
      volume_t *V = Volumes[i];
      if (save_index (V)) {
        res |= 1;
      }
    }
    exit (res);
  } else {
    vkprintf (1, "created child process pid = %d\n", res);
    child_pid = res;
  }
  force_write_index = 0;
}