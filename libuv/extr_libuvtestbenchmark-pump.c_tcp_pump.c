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
 int MAX_WRITE_HANDLES ; 
 int TARGET_CONNECTIONS ; 
 int /*<<< orphan*/  TCP ; 
 int /*<<< orphan*/  TEST_PORT ; 
 int /*<<< orphan*/  UV_RUN_DEFAULT ; 
 int /*<<< orphan*/  connect_addr ; 
 int /*<<< orphan*/  loop ; 
 int /*<<< orphan*/  maybe_connect_some () ; 
 int /*<<< orphan*/  type ; 
 int /*<<< orphan*/  uv_default_loop () ; 
 scalar_t__ uv_ip4_addr (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_run (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tcp_pump(int n) {
  ASSERT(n <= MAX_WRITE_HANDLES);
  TARGET_CONNECTIONS = n;
  type = TCP;

  loop = uv_default_loop();

  ASSERT(0 == uv_ip4_addr("127.0.0.1", TEST_PORT, &connect_addr));

  /* Start making connections */
  maybe_connect_some();

  uv_run(loop, UV_RUN_DEFAULT);

  MAKE_VALGRIND_HAPPY();
}