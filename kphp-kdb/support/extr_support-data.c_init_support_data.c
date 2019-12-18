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
 int /*<<< orphan*/  replay_logevent ; 
 int /*<<< orphan*/  support_replay_logevent ; 

int init_support_data (int schema) {
  replay_logevent = support_replay_logevent;
  return 0;
}