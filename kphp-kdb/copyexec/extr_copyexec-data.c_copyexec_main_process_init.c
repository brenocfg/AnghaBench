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
 int get_process_creation_time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  main_pid ; 
 int main_process_creation_time ; 
 int /*<<< orphan*/  running_lists_init () ; 
 int time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vkprintf (int,char*) ; 

void copyexec_main_process_init (void) {
  main_pid = getpid ();
  main_process_creation_time = get_process_creation_time (main_pid);
  int t = time (NULL) - main_process_creation_time;
  if (!(t > -10 && t < 10)) {
    vkprintf (1, "copyexec_main_process_init: |time (NULL) - get_process_creation_time (getpid ())| >= 10\n");
  }
  running_lists_init ();
}