#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  async_handles; } ;
typedef  TYPE_1__ uv_loop_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;
struct TYPE_9__ {int /*<<< orphan*/  queue; scalar_t__ pending; int /*<<< orphan*/  async_cb; } ;
typedef  TYPE_2__ uv_async_t ;
typedef  int /*<<< orphan*/  uv_async_cb ;

/* Variables and functions */
 int /*<<< orphan*/  QUEUE_INSERT_TAIL (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UV_ASYNC ; 
 int uv__async_start (TYPE_1__*) ; 
 int /*<<< orphan*/  uv__handle_init (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv__handle_start (TYPE_2__*) ; 

int uv_async_init(uv_loop_t* loop, uv_async_t* handle, uv_async_cb async_cb) {
  int err;

  err = uv__async_start(loop);
  if (err)
    return err;

  uv__handle_init(loop, (uv_handle_t*)handle, UV_ASYNC);
  handle->async_cb = async_cb;
  handle->pending = 0;

  QUEUE_INSERT_TAIL(&loop->async_handles, &handle->queue);
  uv__handle_start(handle);

  return 0;
}