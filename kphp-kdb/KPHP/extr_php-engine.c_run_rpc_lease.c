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
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int lease_finish () ; 
 int lease_off () ; 
 int lease_on () ; 
 int lease_start () ; 
 int lease_state ; 
#define  lst_finish 131 
#define  lst_off 130 
#define  lst_on 129 
#define  lst_start 128 

void run_rpc_lease (void) {
  int run_flag = 1;
  while (run_flag) {
    run_flag = 0;
    switch (lease_state) {
      case lst_off:
        run_flag = lease_off();
        break;
      case lst_start:
        run_flag = lease_start();
        break;
      case lst_on:
        run_flag = lease_on();
        break;
      case lst_finish:
        run_flag = lease_finish();
        break;
      default:
        assert (0);
    }
  }
}