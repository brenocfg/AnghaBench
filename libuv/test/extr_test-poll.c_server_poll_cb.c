#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ data; } ;
typedef  TYPE_1__ uv_poll_t ;
typedef  scalar_t__ uv_os_sock_t ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
struct TYPE_8__ {scalar_t__ connections; int /*<<< orphan*/  sock; } ;
typedef  TYPE_2__ server_context_t ;
struct TYPE_9__ {int events; int /*<<< orphan*/  poll_handle; } ;
typedef  TYPE_3__ connection_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ INVALID_SOCKET ; 
 scalar_t__ NUM_CLIENTS ; 
 int UV_DISCONNECT ; 
 int UV_READABLE ; 
 int UV_WRITABLE ; 
 scalar_t__ accept (int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  close_socket (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  connection_poll_cb ; 
 TYPE_3__* create_connection_context (scalar_t__,int) ; 
 int /*<<< orphan*/  destroy_server_context (TYPE_2__*) ; 
 int uv_poll_start (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void server_poll_cb(uv_poll_t* handle, int status, int events) {
  server_context_t* server_context = (server_context_t*)
                                          handle->data;
  connection_context_t* connection_context;
  struct sockaddr_in addr;
  socklen_t addr_len;
  uv_os_sock_t sock;
  int r;

  addr_len = sizeof addr;
  sock = accept(server_context->sock, (struct sockaddr*) &addr, &addr_len);
#ifdef _WIN32
  ASSERT(sock != INVALID_SOCKET);
#else
  ASSERT(sock >= 0);
#endif

  connection_context = create_connection_context(sock, 1);
  connection_context->events = UV_READABLE | UV_WRITABLE | UV_DISCONNECT;
  r = uv_poll_start(&connection_context->poll_handle,
                    UV_READABLE | UV_WRITABLE | UV_DISCONNECT,
                    connection_poll_cb);
  ASSERT(r == 0);

  if (++server_context->connections == NUM_CLIENTS) {
    close_socket(server_context->sock);
    destroy_server_context(server_context);
  }
}