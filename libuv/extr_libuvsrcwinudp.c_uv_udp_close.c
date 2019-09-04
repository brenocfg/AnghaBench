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
struct TYPE_5__ {scalar_t__ reqs_pending; int /*<<< orphan*/  socket; } ;
typedef  TYPE_1__ uv_udp_t ;
typedef  int /*<<< orphan*/  uv_loop_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  INVALID_SOCKET ; 
 int /*<<< orphan*/  closesocket (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv__handle_closing (TYPE_1__*) ; 
 int /*<<< orphan*/  uv_udp_recv_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  uv_want_endgame (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void uv_udp_close(uv_loop_t* loop, uv_udp_t* handle) {
  uv_udp_recv_stop(handle);
  closesocket(handle->socket);
  handle->socket = INVALID_SOCKET;

  uv__handle_closing(handle);

  if (handle->reqs_pending == 0) {
    uv_want_endgame(loop, (uv_handle_t*) handle);
  }
}