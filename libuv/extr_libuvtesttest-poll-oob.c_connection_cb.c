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
typedef  int /*<<< orphan*/  uv_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  MSG_OOB ; 
 int UV_PRIORITIZED ; 
 int UV_READABLE ; 
 int UV_WRITABLE ; 
 int /*<<< orphan*/  client_fd ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  idle ; 
 int /*<<< orphan*/  idle_cb ; 
 int /*<<< orphan*/  peer_handle ; 
 int /*<<< orphan*/  poll_cb ; 
 int /*<<< orphan*/ * poll_req ; 
 int send (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  server_fd ; 
 scalar_t__ uv_accept (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_default_loop () ; 
 scalar_t__ uv_fileno (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ uv_idle_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ uv_poll_init_socket (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ uv_poll_start (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void connection_cb(uv_stream_t* handle, int status) {
  int r;

  ASSERT(0 == status);
  ASSERT(0 == uv_accept(handle, (uv_stream_t*) &peer_handle));
  ASSERT(0 == uv_fileno((uv_handle_t*) &peer_handle, &server_fd));
  ASSERT(0 == uv_poll_init_socket(uv_default_loop(), &poll_req[0], client_fd));
  ASSERT(0 == uv_poll_init_socket(uv_default_loop(), &poll_req[1], server_fd));
  ASSERT(0 == uv_poll_start(&poll_req[0],
                            UV_PRIORITIZED | UV_READABLE | UV_WRITABLE,
                            poll_cb));
  ASSERT(0 == uv_poll_start(&poll_req[1],
                            UV_READABLE,
                            poll_cb));
  do {
    r = send(server_fd, "hello", 5, MSG_OOB);
  } while (r < 0 && errno == EINTR);
  ASSERT(5 == r);

  do {
    r = send(server_fd, "world", 5, 0);
  } while (r < 0 && errno == EINTR);
  ASSERT(5 == r);

  ASSERT(0 == uv_idle_start(&idle, idle_cb));
}