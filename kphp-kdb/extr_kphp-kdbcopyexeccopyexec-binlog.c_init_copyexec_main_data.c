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
 int /*<<< orphan*/  dump_copyexec_main_replay_logevent ; 
 int /*<<< orphan*/  replay_logevent ; 
 int /*<<< orphan*/  vkprintf (int,char*) ; 

int init_copyexec_main_data (int schema) {
  vkprintf (1, "init_copyexe_main_data\n");
  replay_logevent = dump_copyexec_main_replay_logevent;
  return 0;
}