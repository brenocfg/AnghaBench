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
typedef  int /*<<< orphan*/  uv_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  idle_2_close_cb_called ; 
 int /*<<< orphan*/  idle_2_handle ; 
 int idle_2_is_active ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void idle_2_close_cb(uv_handle_t* handle) {
  fprintf(stderr, "%s", "IDLE_2_CLOSE_CB\n");
  fflush(stderr);

  ASSERT(handle == (uv_handle_t*)&idle_2_handle);

  ASSERT(idle_2_is_active);

  idle_2_close_cb_called++;
  idle_2_is_active = 0;
}