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
typedef  int /*<<< orphan*/  uv_poll_t ;
typedef  int /*<<< orphan*/  uv_os_sock_t ;
typedef  int /*<<< orphan*/  uv_loop_t ;

/* Variables and functions */
 int uv_poll_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int uv_poll_init_socket(uv_loop_t* loop, uv_poll_t* handle,
    uv_os_sock_t socket) {
  return uv_poll_init(loop, handle, socket);
}