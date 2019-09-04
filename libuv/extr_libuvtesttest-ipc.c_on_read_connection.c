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
struct TYPE_5__ {scalar_t__ base; } ;
typedef  TYPE_1__ uv_buf_t ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ UV_EOF ; 
 scalar_t__ UV_TCP ; 
 scalar_t__ UV_UNKNOWN_HANDLE ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 scalar_t__ memcmp (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  on_read_alloc ; 
 int /*<<< orphan*/  on_tcp_read ; 
 int /*<<< orphan*/  on_tcp_write ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  read_cb_called ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  tcp_connection ; 
 int uv_accept (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__ uv_buf_init (char*,int) ; 
 int /*<<< orphan*/  uv_default_loop () ; 
 int uv_pipe_pending_count (int /*<<< orphan*/ *) ; 
 scalar_t__ uv_pipe_pending_type (int /*<<< orphan*/ *) ; 
 int uv_read_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* uv_strerror (scalar_t__) ; 
 int uv_tcp_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int uv_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_req ; 

__attribute__((used)) static void on_read_connection(uv_stream_t* handle,
                               ssize_t nread,
                               const uv_buf_t* buf) {
  int r;
  uv_buf_t outbuf;
  uv_pipe_t* pipe;
  uv_handle_type pending;

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

  ASSERT(1 == uv_pipe_pending_count(pipe));
  pending = uv_pipe_pending_type(pipe);

  ASSERT(nread > 0 && buf->base && pending != UV_UNKNOWN_HANDLE);
  read_cb_called++;

  /* Accept the pending TCP connection */
  ASSERT(pending == UV_TCP);
  r = uv_tcp_init(uv_default_loop(), &tcp_connection);
  ASSERT(r == 0);

  r = uv_accept(handle, (uv_stream_t*)&tcp_connection);
  ASSERT(r == 0);

  /* Make sure that the expected data is correctly multiplexed. */
  ASSERT(memcmp("hello\n", buf->base, nread) == 0);

  /* Write/read to/from the connection */
  outbuf = uv_buf_init("world\n", 6);
  r = uv_write(&write_req, (uv_stream_t*)&tcp_connection, &outbuf, 1,
    on_tcp_write);
  ASSERT(r == 0);

  r = uv_read_start((uv_stream_t*)&tcp_connection, on_read_alloc, on_tcp_read);
  ASSERT(r == 0);

  free(buf->base);
}