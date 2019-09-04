#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uv_stream_t ;
typedef  int /*<<< orphan*/  uv_shutdown_t ;
struct TYPE_4__ {scalar_t__ base; } ;
typedef  TYPE_1__ uv_buf_t ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ UV_EOF ; 
 int /*<<< orphan*/  after_shutdown ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  process_req (int /*<<< orphan*/ *,scalar_t__,TYPE_1__ const*) ; 
 int /*<<< orphan*/  uv_shutdown (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void after_read(uv_stream_t* handle,
                       ssize_t nread,
                       const uv_buf_t* buf) {
  uv_shutdown_t* req;

  if (nread < 0) {
    /* Error or EOF */
    ASSERT(nread == UV_EOF);

    if (buf->base) {
      free(buf->base);
    }

    req = malloc(sizeof *req);
    uv_shutdown(req, handle, after_shutdown);

    return;
  }

  if (nread == 0) {
    /* Everything OK, but nothing read. */
    free(buf->base);
    return;
  }
  /* process requests and send responses */
  process_req(handle, nread, buf);
}