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
 int /*<<< orphan*/  PIPE ; 
 int TARGET_CONNECTIONS ; 
 int /*<<< orphan*/  UV_RUN_DEFAULT ; 
 int /*<<< orphan*/  loop ; 
 int /*<<< orphan*/  maybe_connect_some () ; 
 int /*<<< orphan*/  type ; 
 int /*<<< orphan*/  uv_default_loop () ; 
 int /*<<< orphan*/  uv_run (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pipe_pump(int n) {
  ASSERT(n <= MAX_WRITE_HANDLES);
  TARGET_CONNECTIONS = n;
  type = PIPE;

  loop = uv_default_loop();

  /* Start making connections */
  maybe_connect_some();

  uv_run(loop, UV_RUN_DEFAULT);

  MAKE_VALGRIND_HAPPY();
}