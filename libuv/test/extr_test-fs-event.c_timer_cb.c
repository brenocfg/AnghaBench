#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  loop; } ;
typedef  TYPE_1__ uv_timer_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  close_cb ; 
 int /*<<< orphan*/  fs_event ; 
 int /*<<< orphan*/  fs_event_fail ; 
 int /*<<< orphan*/  uv_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int uv_fs_event_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int uv_fs_event_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void timer_cb(uv_timer_t* handle) {
  int r;

  r = uv_fs_event_init(handle->loop, &fs_event);
  ASSERT(r == 0);
  r = uv_fs_event_start(&fs_event, fs_event_fail, ".", 0);
  ASSERT(r == 0);

  uv_close((uv_handle_t*)&fs_event, close_cb);
  uv_close((uv_handle_t*)handle, close_cb);
}