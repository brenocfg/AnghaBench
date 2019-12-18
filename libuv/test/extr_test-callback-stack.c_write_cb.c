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
typedef  int /*<<< orphan*/  uv_write_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ nested ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  timer ; 
 int /*<<< orphan*/  timer_cb ; 
 int /*<<< orphan*/  uv_default_loop () ; 
 int uv_timer_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int uv_timer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_cb_called ; 

__attribute__((used)) static void write_cb(uv_write_t* req, int status) {
  int r;

  ASSERT(status == 0);
  ASSERT(nested == 0 && "write_cb must be called from a fresh stack");

  puts("Data written. 500ms timeout...");

  /* After the data has been sent, we're going to wait for a while, then start
   * reading. This makes us certain that the message has been echoed back to
   * our receive buffer when we start reading. This maximizes the temptation
   * for the backend to use dirty stack for calling read_cb. */
  nested++;
  r = uv_timer_init(uv_default_loop(), &timer);
  ASSERT(r == 0);
  r = uv_timer_start(&timer, timer_cb, 500, 0);
  ASSERT(r == 0);
  nested--;

  write_cb_called++;
}