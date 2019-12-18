#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int write_index; int nbufs; TYPE_3__* bufs; } ;
typedef  TYPE_1__ uv_write_t ;
struct TYPE_7__ {size_t write_queue_size; } ;
typedef  TYPE_2__ uv_stream_t ;
struct TYPE_8__ {size_t len; size_t base; } ;
typedef  TYPE_3__ uv_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int uv__write_req_update(uv_stream_t* stream,
                                uv_write_t* req,
                                size_t n) {
  uv_buf_t* buf;
  size_t len;

  assert(n <= stream->write_queue_size);
  stream->write_queue_size -= n;

  buf = req->bufs + req->write_index;

  do {
    len = n < buf->len ? n : buf->len;
    buf->base += len;
    buf->len -= len;
    buf += (buf->len == 0);  /* Advance to next buffer if this one is empty. */
    n -= len;
  } while (n > 0);

  req->write_index = buf - req->bufs;

  return req->write_index == req->nbufs;
}