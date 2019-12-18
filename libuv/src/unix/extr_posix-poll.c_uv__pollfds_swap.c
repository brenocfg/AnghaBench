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
struct TYPE_3__ {struct pollfd* poll_fds; } ;
typedef  TYPE_1__ uv_loop_t ;
struct pollfd {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void uv__pollfds_swap(uv_loop_t* loop, size_t l, size_t r) {
  struct pollfd pfd;
  pfd = loop->poll_fds[l];
  loop->poll_fds[l] = loop->poll_fds[r];
  loop->poll_fds[r] = pfd;
}