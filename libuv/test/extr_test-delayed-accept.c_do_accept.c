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
struct TYPE_3__ {scalar_t__ data; } ;
typedef  TYPE_1__ uv_timer_t ;
typedef  int /*<<< orphan*/  uv_tcp_t ;
typedef  int /*<<< orphan*/  uv_stream_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  close_cb ; 
 int do_accept_called ; 
 scalar_t__ malloc (int) ; 
 int uv_accept (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_default_loop () ; 
 int uv_tcp_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void do_accept(uv_timer_t* timer_handle) {
  uv_tcp_t* server;
  uv_tcp_t* accepted_handle = (uv_tcp_t*)malloc(sizeof *accepted_handle);
  int r;

  ASSERT(timer_handle != NULL);
  ASSERT(accepted_handle != NULL);

  r = uv_tcp_init(uv_default_loop(), accepted_handle);
  ASSERT(r == 0);

  server = (uv_tcp_t*)timer_handle->data;
  r = uv_accept((uv_stream_t*)server, (uv_stream_t*)accepted_handle);
  ASSERT(r == 0);

  do_accept_called++;

  /* Immediately close the accepted handle. */
  uv_close((uv_handle_t*)accepted_handle, close_cb);

  /* After accepting the two clients close the server handle */
  if (do_accept_called == 2) {
    uv_close((uv_handle_t*)server, close_cb);
  }

  /* Dispose the timer. */
  uv_close((uv_handle_t*)timer_handle, close_cb);
}