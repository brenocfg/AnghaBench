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
typedef  int /*<<< orphan*/  uv_loop_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;
struct TYPE_3__ {int /*<<< orphan*/ * poll_ctx; } ;
typedef  TYPE_1__ uv_fs_poll_t ;

/* Variables and functions */
 int /*<<< orphan*/  UV_FS_POLL ; 
 int /*<<< orphan*/  uv__handle_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int uv_fs_poll_init(uv_loop_t* loop, uv_fs_poll_t* handle) {
  uv__handle_init(loop, (uv_handle_t*)handle, UV_FS_POLL);
  handle->poll_ctx = NULL;
  return 0;
}