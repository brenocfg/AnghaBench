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
typedef  int /*<<< orphan*/  uv_tcp_t ;
typedef  int /*<<< orphan*/  uv_stream_t ;
typedef  int /*<<< orphan*/  uv_pipe_t ;
typedef  int uv_os_fd_t ;
typedef  scalar_t__ uv_handle_type ;
typedef  int /*<<< orphan*/  uv_handle_t ;
typedef  int /*<<< orphan*/  uv_buf_t ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ UV_EOF ; 
 scalar_t__ UV_TCP ; 
 int /*<<< orphan*/  alloc_buffer ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  echo_read ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int getpid () ; 
 int /*<<< orphan*/  loop ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ uv_accept (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* uv_err_name (scalar_t__) ; 
 int /*<<< orphan*/  uv_fileno (int /*<<< orphan*/  const*,int*) ; 
 int /*<<< orphan*/  uv_pipe_pending_count (int /*<<< orphan*/ *) ; 
 scalar_t__ uv_pipe_pending_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_read_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_tcp_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void on_new_connection(uv_stream_t *q, ssize_t nread, const uv_buf_t *buf) {
    if (nread < 0) {
        if (nread != UV_EOF)
            fprintf(stderr, "Read error %s\n", uv_err_name(nread));
        uv_close((uv_handle_t*) q, NULL);
        return;
    }

    uv_pipe_t *pipe = (uv_pipe_t*) q;
    if (!uv_pipe_pending_count(pipe)) {
        fprintf(stderr, "No pending count\n");
        return;
    }

    uv_handle_type pending = uv_pipe_pending_type(pipe);
    assert(pending == UV_TCP);

    uv_tcp_t *client = (uv_tcp_t*) malloc(sizeof(uv_tcp_t));
    uv_tcp_init(loop, client);
    if (uv_accept(q, (uv_stream_t*) client) == 0) {
        uv_os_fd_t fd;
        uv_fileno((const uv_handle_t*) client, &fd);
        fprintf(stderr, "Worker %d: Accepted fd %d\n", getpid(), fd);
        uv_read_start((uv_stream_t*) client, alloc_buffer, echo_read);
    }
    else {
        uv_close((uv_handle_t*) client, NULL);
    }
}