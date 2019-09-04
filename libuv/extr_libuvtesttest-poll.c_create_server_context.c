#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uv_os_sock_t ;
struct TYPE_5__ {TYPE_1__* data; } ;
struct TYPE_4__ {TYPE_2__ poll_handle; scalar_t__ connections; int /*<<< orphan*/  sock; } ;
typedef  TYPE_1__ server_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  uv_default_loop () ; 
 int uv_poll_init_socket (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static server_context_t* create_server_context(
    uv_os_sock_t sock) {
  int r;
  server_context_t* context;

  context = (server_context_t*) malloc(sizeof *context);
  ASSERT(context != NULL);

  context->sock = sock;
  context->connections = 0;

  r = uv_poll_init_socket(uv_default_loop(), &context->poll_handle, sock);
  context->poll_handle.data = context;
  ASSERT(r == 0);

  return context;
}