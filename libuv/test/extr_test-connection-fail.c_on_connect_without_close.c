#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uv_connect_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int UV_ECONNREFUSED ; 
 scalar_t__ close_cb_calls ; 
 int /*<<< orphan*/  connect_cb_calls ; 
 int /*<<< orphan*/  timer ; 
 int /*<<< orphan*/  timer_cb ; 
 int /*<<< orphan*/  uv_timer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void on_connect_without_close(uv_connect_t *req, int status) {
  ASSERT(status == UV_ECONNREFUSED);
  connect_cb_calls++;

  uv_timer_start(&timer, timer_cb, 100, 0);

  ASSERT(close_cb_calls == 0);
}