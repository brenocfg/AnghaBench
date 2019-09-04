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
typedef  int /*<<< orphan*/  uv_timer_t ;
typedef  int /*<<< orphan*/  uv_stream_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  FATAL (char*) ; 
 int /*<<< orphan*/  alloc_cb ; 
 int /*<<< orphan*/  client ; 
 int /*<<< orphan*/  close_cb ; 
 scalar_t__ nested ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  read_cb ; 
 int /*<<< orphan*/  timer ; 
 int /*<<< orphan*/  timer_cb_called ; 
 int /*<<< orphan*/  uv_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ uv_read_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void timer_cb(uv_timer_t* handle) {
  ASSERT(handle == &timer);
  ASSERT(nested == 0 && "timer_cb must be called from a fresh stack");

  puts("Timeout complete. Now read data...");

  nested++;
  if (uv_read_start((uv_stream_t*)&client, alloc_cb, read_cb)) {
    FATAL("uv_read_start failed");
  }
  nested--;

  timer_cb_called++;

  uv_close((uv_handle_t*)handle, close_cb);
}