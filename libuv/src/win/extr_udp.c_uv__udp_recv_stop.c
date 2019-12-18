#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int flags; TYPE_1__* loop; } ;
typedef  TYPE_2__ uv_udp_t ;
struct TYPE_5__ {int /*<<< orphan*/  active_udp_streams; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECREASE_ACTIVE_COUNT (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int UV_HANDLE_READING ; 
 int /*<<< orphan*/  loop ; 

int uv__udp_recv_stop(uv_udp_t* handle) {
  if (handle->flags & UV_HANDLE_READING) {
    handle->flags &= ~UV_HANDLE_READING;
    handle->loop->active_udp_streams--;
    DECREASE_ACTIVE_COUNT(loop, handle);
  }

  return 0;
}