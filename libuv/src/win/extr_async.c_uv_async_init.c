#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* data; } ;
typedef  TYPE_1__ uv_req_t ;
typedef  int /*<<< orphan*/  uv_loop_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;
struct TYPE_7__ {TYPE_1__ async_req; int /*<<< orphan*/  async_cb; scalar_t__ async_sent; } ;
typedef  TYPE_2__ uv_async_t ;
typedef  int /*<<< orphan*/  uv_async_cb ;

/* Variables and functions */
 int /*<<< orphan*/  UV_ASYNC ; 
 int /*<<< orphan*/  UV_REQ_INIT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UV_WAKEUP ; 
 int /*<<< orphan*/  uv__handle_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv__handle_start (TYPE_2__*) ; 

int uv_async_init(uv_loop_t* loop, uv_async_t* handle, uv_async_cb async_cb) {
  uv_req_t* req;

  uv__handle_init(loop, (uv_handle_t*) handle, UV_ASYNC);
  handle->async_sent = 0;
  handle->async_cb = async_cb;

  req = &handle->async_req;
  UV_REQ_INIT(req, UV_WAKEUP);
  req->data = handle;

  uv__handle_start(handle);

  return 0;
}