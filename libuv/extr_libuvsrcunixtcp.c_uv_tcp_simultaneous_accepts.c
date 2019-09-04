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
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ uv_tcp_t ;

/* Variables and functions */
 int /*<<< orphan*/  UV_HANDLE_TCP_SINGLE_ACCEPT ; 

int uv_tcp_simultaneous_accepts(uv_tcp_t* handle, int enable) {
  if (enable)
    handle->flags &= ~UV_HANDLE_TCP_SINGLE_ACCEPT;
  else
    handle->flags |= UV_HANDLE_TCP_SINGLE_ACCEPT;
  return 0;
}