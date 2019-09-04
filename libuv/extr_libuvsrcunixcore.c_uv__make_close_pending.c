#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flags; TYPE_1__* loop; struct TYPE_5__* next_closing; } ;
typedef  TYPE_2__ uv_handle_t ;
struct TYPE_4__ {TYPE_2__* closing_handles; } ;

/* Variables and functions */
 int UV_HANDLE_CLOSED ; 
 int UV_HANDLE_CLOSING ; 
 int /*<<< orphan*/  assert (int) ; 

void uv__make_close_pending(uv_handle_t* handle) {
  assert(handle->flags & UV_HANDLE_CLOSING);
  assert(!(handle->flags & UV_HANDLE_CLOSED));
  handle->next_closing = handle->loop->closing_handles;
  handle->loop->closing_handles = handle;
}