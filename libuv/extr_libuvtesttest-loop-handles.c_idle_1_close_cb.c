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
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  idle_1_close_cb_called ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void idle_1_close_cb(uv_handle_t* handle) {
  fprintf(stderr, "%s", "IDLE_1_CLOSE_CB\n");
  fflush(stderr);

  ASSERT(handle != NULL);

  idle_1_close_cb_called++;
}