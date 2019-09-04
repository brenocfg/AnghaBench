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
typedef  scalar_t__ mode_t ;

/* Variables and functions */
 scalar_t__ chmod (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  kprintf (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  work_dir ; 

void restore_work_dir_perms (int change_extract_dir_perms_during_replay_log, mode_t old_mode) {
  if (change_extract_dir_perms_during_replay_log) {
    if (chmod (work_dir, old_mode) < 0) {
      kprintf ("chmod 0%o \"%s\" fail. %m\n", (int) old_mode, work_dir);
    }
  }
}