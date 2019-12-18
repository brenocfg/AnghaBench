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
 int /*<<< orphan*/  fs_event ; 
 scalar_t__ timer_cb_exact_called ; 
 int /*<<< orphan*/  touch_file (char*) ; 
 int /*<<< orphan*/  uv_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int uv_fs_event_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void timer_cb_exact(uv_timer_t* handle) {
  int r;

  if (timer_cb_exact_called == 0) {
    touch_file("watch_dir/file.js");
  } else {
    uv_close((uv_handle_t*)handle, NULL);
    r = uv_fs_event_stop(&fs_event);
    ASSERT(r == 0);
    uv_close((uv_handle_t*) &fs_event, NULL);
  }

  ++timer_cb_exact_called;
}