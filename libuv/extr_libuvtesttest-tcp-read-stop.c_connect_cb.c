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
typedef  int /*<<< orphan*/  uv_stream_t ;
typedef  int /*<<< orphan*/  uv_read_cb ;
typedef  int /*<<< orphan*/  uv_connect_t ;
typedef  int /*<<< orphan*/  uv_alloc_cb ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ fail_cb ; 
 int /*<<< orphan*/  tcp_handle ; 
 int /*<<< orphan*/  timer_cb ; 
 int /*<<< orphan*/  timer_handle ; 
 scalar_t__ uv_read_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ uv_timer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void connect_cb(uv_connect_t* req, int status) {
  ASSERT(0 == status);
  ASSERT(0 == uv_timer_start(&timer_handle, timer_cb, 50, 0));
  ASSERT(0 == uv_read_start((uv_stream_t*) &tcp_handle,
                            (uv_alloc_cb) fail_cb,
                            (uv_read_cb) fail_cb));
}