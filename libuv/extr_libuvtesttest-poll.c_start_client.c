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
struct sockaddr {int dummy; } ;
struct TYPE_3__ {int events; int /*<<< orphan*/  poll_handle; } ;
typedef  TYPE_1__ connection_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  TEST_PORT ; 
 int UV_DISCONNECT ; 
 int UV_READABLE ; 
 int UV_WRITABLE ; 
 int connect (int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 int /*<<< orphan*/  connection_poll_cb ; 
 int /*<<< orphan*/  create_bound_socket (struct sockaddr_in) ; 
 TYPE_1__* create_connection_context (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ got_eagain () ; 
 scalar_t__ uv_ip4_addr (char*,int /*<<< orphan*/ ,struct sockaddr_in*) ; 
 int uv_poll_start (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void start_client(void) {
  uv_os_sock_t sock;
  connection_context_t* context;
  struct sockaddr_in server_addr;
  struct sockaddr_in addr;
  int r;

  ASSERT(0 == uv_ip4_addr("127.0.0.1", TEST_PORT, &server_addr));
  ASSERT(0 == uv_ip4_addr("0.0.0.0", 0, &addr));

  sock = create_bound_socket(addr);
  context = create_connection_context(sock, 0);

  context->events = UV_READABLE | UV_WRITABLE | UV_DISCONNECT;
  r = uv_poll_start(&context->poll_handle,
                    UV_READABLE | UV_WRITABLE | UV_DISCONNECT,
                    connection_poll_cb);
  ASSERT(r == 0);

  r = connect(sock, (struct sockaddr*) &server_addr, sizeof server_addr);
  ASSERT(r == 0 || got_eagain());
}