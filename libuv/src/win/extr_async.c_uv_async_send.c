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
struct TYPE_3__ {scalar_t__ type; int flags; int /*<<< orphan*/  async_req; int /*<<< orphan*/  async_sent; int /*<<< orphan*/ * loop; } ;
typedef  TYPE_1__ uv_async_t ;

/* Variables and functions */
 int /*<<< orphan*/  POST_COMPLETION_FOR_REQ (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ UV_ASYNC ; 
 int UV_HANDLE_CLOSING ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  uv__atomic_exchange_set (int /*<<< orphan*/ *) ; 

int uv_async_send(uv_async_t* handle) {
  uv_loop_t* loop = handle->loop;

  if (handle->type != UV_ASYNC) {
    /* Can't set errno because that's not thread-safe. */
    return -1;
  }

  /* The user should make sure never to call uv_async_send to a closing or
   * closed handle. */
  assert(!(handle->flags & UV_HANDLE_CLOSING));

  if (!uv__atomic_exchange_set(&handle->async_sent)) {
    POST_COMPLETION_FOR_REQ(loop, &handle->async_req);
  }

  return 0;
}