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

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int idle_cb_called ; 
 int /*<<< orphan*/  idle_handle ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void idle_cb(uv_idle_t* handle) {
  ASSERT(handle == &idle_handle);

  idle_cb_called++;
  fprintf(stderr, "idle_cb %d\n", idle_cb_called);
  fflush(stderr);
}