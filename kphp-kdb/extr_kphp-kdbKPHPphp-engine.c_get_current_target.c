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
 scalar_t__ lease_state ; 
 scalar_t__ lst_off ; 
 scalar_t__ lst_on ; 
 int rpc_lease_target ; 
 int rpc_main_target ; 

int get_current_target (void) {
  if (lease_state == lst_off) {
    return rpc_main_target;
  }
  if (lease_state == lst_on) {
    return rpc_lease_target;
  }
  return -1;
}