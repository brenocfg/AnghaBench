#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uv_tcp_t ;
struct TYPE_6__ {int /*<<< orphan*/ * loop; } ;
typedef  TYPE_1__ uv_stream_t ;
typedef  int /*<<< orphan*/  uv_loop_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;
typedef  int /*<<< orphan*/  uv_buf_t ;
struct sockaddr {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  addr ; 
 int /*<<< orphan*/  alloc_cb ; 
 int /*<<< orphan*/  close_cb ; 
 int /*<<< orphan*/  connect_cb ; 
 unsigned int got_connections ; 
 unsigned int pending_incoming ; 
 int /*<<< orphan*/  read_cb_called ; 
 int /*<<< orphan*/  tcp_check ; 
 int /*<<< orphan*/  tcp_check_req ; 
 int /*<<< orphan*/ * tcp_incoming ; 
 int /*<<< orphan*/  tcp_server ; 
 int /*<<< orphan*/  uv_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ uv_read_start (TYPE_1__*,int /*<<< orphan*/ ,void (*) (TYPE_1__*,int,int /*<<< orphan*/  const*)) ; 
 scalar_t__ uv_read_stop (TYPE_1__*) ; 
 scalar_t__ uv_tcp_connect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct sockaddr const*,int /*<<< orphan*/ ) ; 
 scalar_t__ uv_tcp_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void read_cb(uv_stream_t* stream, ssize_t nread, const uv_buf_t* buf) {
  uv_loop_t* loop;
  unsigned int i;

  pending_incoming = (uv_tcp_t*) stream - &tcp_incoming[0];
  ASSERT(pending_incoming < got_connections);
  ASSERT(0 == uv_read_stop(stream));
  ASSERT(1 == nread);

  loop = stream->loop;
  read_cb_called++;

  /* Close all active incomings, except current one */
  for (i = 0; i < got_connections; i++) {
    if (i != pending_incoming)
      uv_close((uv_handle_t*) &tcp_incoming[i], close_cb);
  }

  /* Close server, so no one will connect to it */
  uv_close((uv_handle_t*) &tcp_server, close_cb);

  /* Create new fd that should be one of the closed incomings */
  ASSERT(0 == uv_tcp_init(loop, &tcp_check));
  ASSERT(0 == uv_tcp_connect(&tcp_check_req,
                             &tcp_check,
                             (const struct sockaddr*) &addr,
                             connect_cb));
  ASSERT(0 == uv_read_start((uv_stream_t*) &tcp_check, alloc_cb, read_cb));
}