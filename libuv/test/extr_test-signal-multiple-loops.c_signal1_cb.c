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
typedef  int /*<<< orphan*/  uv_signal_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int SIGUSR1 ; 
 int /*<<< orphan*/  increment_counter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal1_cb_counter ; 
 int /*<<< orphan*/  uv_signal_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void signal1_cb(uv_signal_t* handle, int signum) {
  ASSERT(signum == SIGUSR1);
  increment_counter(&signal1_cb_counter);
  uv_signal_stop(handle);
}