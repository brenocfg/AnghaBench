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
typedef  int /*<<< orphan*/  uv_idle_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  idle_2_cb_called ; 
 int /*<<< orphan*/  idle_2_close_cb ; 
 int /*<<< orphan*/  idle_2_handle ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  uv_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void idle_2_cb(uv_idle_t* handle) {
  fprintf(stderr, "%s", "IDLE_2_CB\n");
  fflush(stderr);

  ASSERT(handle == &idle_2_handle);

  idle_2_cb_called++;

  uv_close((uv_handle_t*)handle, idle_2_close_cb);
}