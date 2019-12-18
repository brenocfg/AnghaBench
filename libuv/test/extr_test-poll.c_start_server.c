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
typedef  int /*<<< orphan*/  uv_os_sock_t ;
struct sockaddr_in {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  poll_handle; } ;
typedef  TYPE_1__ server_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  TEST_PORT ; 
 int /*<<< orphan*/  UV_READABLE ; 
 int /*<<< orphan*/  create_bound_socket (struct sockaddr_in) ; 
 TYPE_1__* create_server_context (int /*<<< orphan*/ ) ; 
 int listen (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  server_poll_cb ; 
 scalar_t__ uv_ip4_addr (char*,int /*<<< orphan*/ ,struct sockaddr_in*) ; 
 int uv_poll_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void start_server(void) {
  server_context_t* context;
  struct sockaddr_in addr;
  uv_os_sock_t sock;
  int r;

  ASSERT(0 == uv_ip4_addr("127.0.0.1", TEST_PORT, &addr));
  sock = create_bound_socket(addr);
  context = create_server_context(sock);

  r = listen(sock, 100);
  ASSERT(r == 0);

  r = uv_poll_start(&context->poll_handle, UV_READABLE, server_poll_cb);
  ASSERT(r == 0);
}