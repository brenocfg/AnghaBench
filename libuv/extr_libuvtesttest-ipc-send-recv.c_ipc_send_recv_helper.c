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
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  MAKE_VALGRIND_HAPPY () ; 
 int run_ipc_send_recv_helper (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_default_loop () ; 

int ipc_send_recv_helper(void) {
  int r;

  r = run_ipc_send_recv_helper(uv_default_loop(), 0);
  ASSERT(r == 0);

  MAKE_VALGRIND_HAPPY();
  return 0;
}