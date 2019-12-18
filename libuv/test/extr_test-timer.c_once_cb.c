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
typedef  int /*<<< orphan*/  uv_timer_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int once_cb_called ; 
 int /*<<< orphan*/  once_close_cb ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  uv_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_default_loop () ; 
 scalar_t__ uv_is_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_update_time (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void once_cb(uv_timer_t* handle) {
  printf("ONCE_CB %d\n", once_cb_called);

  ASSERT(handle != NULL);
  ASSERT(0 == uv_is_active((uv_handle_t*) handle));

  once_cb_called++;

  uv_close((uv_handle_t*)handle, once_close_cb);

  /* Just call this randomly for the code coverage. */
  uv_update_time(uv_default_loop());
}