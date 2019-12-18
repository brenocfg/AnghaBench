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
typedef  int /*<<< orphan*/  uv_stream_t ;
typedef  int /*<<< orphan*/  uv_pipe_t ;
typedef  scalar_t__ uv_handle_type ;
typedef  int /*<<< orphan*/  uv_handle_t ;
struct TYPE_5__ {scalar_t__ base; } ;
typedef  TYPE_1__ uv_buf_t ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  BACKLOG ; 
 scalar_t__ UV_EOF ; 
 scalar_t__ UV_TCP ; 
 scalar_t__ UV_UNKNOWN_HANDLE ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  channel ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  make_many_connections () ; 
 scalar_t__ memcmp (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  on_connection ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  read_cb_called ; 
 int remote_conn_accepted ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  tcp_server ; 
 int tcp_server_listening ; 
 int uv_accept (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__ uv_buf_init (char*,int) ; 
 int /*<<< orphan*/  uv_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_default_loop () ; 
 int uv_listen (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int uv_pipe_pending_count (int /*<<< orphan*/ *) ; 
 scalar_t__ uv_pipe_pending_type (int /*<<< orphan*/ *) ; 
 char* uv_strerror (scalar_t__) ; 
 int uv_tcp_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int uv_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_req ; 

__attribute__((used)) static void on_read(uv_stream_t* handle,
                    ssize_t nread,
                    const uv_buf_t* buf) {
  int r;
  uv_pipe_t* pipe;
  uv_handle_type pending;
  uv_buf_t outbuf;

  pipe = (uv_pipe_t*) handle;

  if (nread == 0) {
    /* Everything OK, but nothing read. */
    free(buf->base);
    return;
  }

  if (nread < 0) {
    if (nread == UV_EOF) {
      free(buf->base);
      return;
    }

    printf("error recving on channel: %s\n", uv_strerror(nread));
    abort();
  }

  fprintf(stderr, "got %d bytes\n", (int)nread);

  pending = uv_pipe_pending_type(pipe);
  if (!tcp_server_listening) {
    ASSERT(1 == uv_pipe_pending_count(pipe));
    ASSERT(nread > 0 && buf->base && pending != UV_UNKNOWN_HANDLE);
    read_cb_called++;

    /* Accept the pending TCP server, and start listening on it. */
    ASSERT(pending == UV_TCP);
    r = uv_tcp_init(uv_default_loop(), &tcp_server);
    ASSERT(r == 0);

    r = uv_accept((uv_stream_t*)pipe, (uv_stream_t*)&tcp_server);
    ASSERT(r == 0);

    r = uv_listen((uv_stream_t*)&tcp_server, BACKLOG, on_connection);
    ASSERT(r == 0);

    tcp_server_listening = 1;

    /* Make sure that the expected data is correctly multiplexed. */
    ASSERT(memcmp("hello\n", buf->base, nread) == 0);

    outbuf = uv_buf_init("world\n", 6);
    r = uv_write(&write_req, (uv_stream_t*)pipe, &outbuf, 1, NULL);
    ASSERT(r == 0);

    /* Create a bunch of connections to get both servers to accept. */
    make_many_connections();
  } else if (memcmp("accepted_connection\n", buf->base, nread) == 0) {
    /* Remote server has accepted a connection.  Close the channel. */
    ASSERT(0 == uv_pipe_pending_count(pipe));
    ASSERT(pending == UV_UNKNOWN_HANDLE);
    remote_conn_accepted = 1;
    uv_close((uv_handle_t*)&channel, NULL);
  }

  free(buf->base);
}