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
struct TYPE_4__ {int /*<<< orphan*/  buf; int /*<<< orphan*/  req; } ;
typedef  TYPE_1__ write_req_t ;
typedef  int /*<<< orphan*/  uv_stream_t ;
typedef  int /*<<< orphan*/  uv_shutdown_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;
struct TYPE_5__ {char* base; } ;
typedef  TYPE_2__ uv_buf_t ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  FATAL (char*) ; 
 int UV_EOF ; 
 int /*<<< orphan*/  after_shutdown ; 
 int /*<<< orphan*/  after_write ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  on_close ; 
 int /*<<< orphan*/  on_server_close ; 
 int /*<<< orphan*/ * server ; 
 int server_closed ; 
 int /*<<< orphan*/  uv_buf_init (char*,int) ; 
 int /*<<< orphan*/  uv_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ uv_shutdown (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ uv_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void after_read(uv_stream_t* handle,
                       ssize_t nread,
                       const uv_buf_t* buf) {
  int i;
  write_req_t *wr;
  uv_shutdown_t* sreq;

  if (nread < 0) {
    /* Error or EOF */
    ASSERT(nread == UV_EOF);

    free(buf->base);
    sreq = malloc(sizeof* sreq);
    ASSERT(0 == uv_shutdown(sreq, handle, after_shutdown));
    return;
  }

  if (nread == 0) {
    /* Everything OK, but nothing read. */
    free(buf->base);
    return;
  }

  /*
   * Scan for the letter Q which signals that we should quit the server.
   * If we get QS it means close the stream.
   */
  if (!server_closed) {
    for (i = 0; i < nread; i++) {
      if (buf->base[i] == 'Q') {
        if (i + 1 < nread && buf->base[i + 1] == 'S') {
          free(buf->base);
          uv_close((uv_handle_t*)handle, on_close);
          return;
        } else {
          uv_close(server, on_server_close);
          server_closed = 1;
        }
      }
    }
  }

  wr = (write_req_t*) malloc(sizeof *wr);
  ASSERT(wr != NULL);
  wr->buf = uv_buf_init(buf->base, nread);

  if (uv_write(&wr->req, handle, &wr->buf, 1, after_write)) {
    FATAL("uv_write failed");
  }
}