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
typedef  scalar_t__ lease_state_t ;

/* Variables and functions */
 scalar_t__ lease_ready_flag ; 
 scalar_t__ lease_state ; 

void lease_change_state (lease_state_t new_state) {
  if (lease_state != new_state) {
    lease_state = new_state;
    lease_ready_flag = 0;
  }
}