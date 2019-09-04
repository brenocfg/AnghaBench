#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uv_loop_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;
struct TYPE_5__ {int /*<<< orphan*/  req_pending; } ;
typedef  TYPE_1__ uv_fs_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  uv__handle_closing (TYPE_1__*) ; 
 int /*<<< orphan*/  uv_fs_event_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  uv_want_endgame (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void uv_fs_event_close(uv_loop_t* loop, uv_fs_event_t* handle) {
  uv_fs_event_stop(handle);

  uv__handle_closing(handle);

  if (!handle->req_pending) {
    uv_want_endgame(loop, (uv_handle_t*)handle);
  }

}