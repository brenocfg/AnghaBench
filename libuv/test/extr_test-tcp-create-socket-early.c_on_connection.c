#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uv_tcp_t ;
struct TYPE_5__ {int /*<<< orphan*/  loop; } ;
typedef  TYPE_1__ uv_stream_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;
typedef  int /*<<< orphan*/ * uv_close_cb ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  ASSERT (int) ; 
 int UV_EBUSY ; 
 scalar_t__ free ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int uv_accept (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  uv_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int uv_tcp_init_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void on_connection(uv_stream_t* server, int status) {
  uv_tcp_t* handle;
  int r;

  ASSERT(status == 0);

  handle = malloc(sizeof(*handle));
  ASSERT(handle != NULL);

  r = uv_tcp_init_ex(server->loop, handle, AF_INET);
  ASSERT(r == 0);

  r = uv_accept(server, (uv_stream_t*)handle);
  ASSERT(r == UV_EBUSY);

  uv_close((uv_handle_t*) server, NULL);
  uv_close((uv_handle_t*) handle, (uv_close_cb)free);
}