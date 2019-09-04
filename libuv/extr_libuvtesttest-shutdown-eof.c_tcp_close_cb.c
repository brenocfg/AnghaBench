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
typedef  int /*<<< orphan*/  uv_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int called_connect_cb ; 
 int /*<<< orphan*/  called_tcp_close_cb ; 
 int called_timer_cb ; 
 int got_eof ; 
 int got_q ; 
 int /*<<< orphan*/  tcp ; 

__attribute__((used)) static void tcp_close_cb(uv_handle_t* handle) {
  ASSERT(handle == (uv_handle_t*) &tcp);

  ASSERT(called_connect_cb == 1);
  ASSERT(got_q);
  ASSERT(got_eof);
  ASSERT(called_timer_cb == 1);

  called_tcp_close_cb++;
}