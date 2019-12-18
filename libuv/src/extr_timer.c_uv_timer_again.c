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
struct TYPE_5__ {scalar_t__ repeat; int /*<<< orphan*/ * timer_cb; } ;
typedef  TYPE_1__ uv_timer_t ;

/* Variables and functions */
 int UV_EINVAL ; 
 int /*<<< orphan*/  uv_timer_start (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  uv_timer_stop (TYPE_1__*) ; 

int uv_timer_again(uv_timer_t* handle) {
  if (handle->timer_cb == NULL)
    return UV_EINVAL;

  if (handle->repeat) {
    uv_timer_stop(handle);
    uv_timer_start(handle, handle->timer_cb, handle->repeat, handle->repeat);
  }

  return 0;
}