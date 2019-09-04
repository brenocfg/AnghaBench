#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uv_loop_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;
struct TYPE_4__ {int /*<<< orphan*/  async_sent; } ;
typedef  TYPE_1__ uv_async_t ;

/* Variables and functions */
 int /*<<< orphan*/  uv__handle_closing (TYPE_1__*) ; 
 int /*<<< orphan*/  uv_want_endgame (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void uv_async_close(uv_loop_t* loop, uv_async_t* handle) {
  if (!((uv_async_t*)handle)->async_sent) {
    uv_want_endgame(loop, (uv_handle_t*) handle);
  }

  uv__handle_closing(handle);
}