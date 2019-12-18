#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ error; int /*<<< orphan*/ * bufs; int /*<<< orphan*/ * bufsml; int /*<<< orphan*/  queue; } ;
typedef  TYPE_1__ uv_write_t ;
struct TYPE_10__ {scalar_t__ write_queue_size; int /*<<< orphan*/  io_watcher; int /*<<< orphan*/  loop; int /*<<< orphan*/ * connect_req; } ;
typedef  TYPE_2__ uv_stream_t ;
typedef  int /*<<< orphan*/  uv_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  POLLOUT ; 
 int /*<<< orphan*/  QUEUE_REMOVE (int /*<<< orphan*/ *) ; 
 int UV_EAGAIN ; 
 size_t uv__count_bufs (int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  uv__free (int /*<<< orphan*/ *) ; 
 int uv__io_active (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv__io_stop (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv__req_unregister (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  uv__stream_osx_interrupt_select (TYPE_2__*) ; 
 size_t uv__write_req_size (TYPE_1__*) ; 
 int /*<<< orphan*/  uv_try_write_cb ; 
 int uv_write (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ ) ; 

int uv_try_write(uv_stream_t* stream,
                 const uv_buf_t bufs[],
                 unsigned int nbufs) {
  int r;
  int has_pollout;
  size_t written;
  size_t req_size;
  uv_write_t req;

  /* Connecting or already writing some data */
  if (stream->connect_req != NULL || stream->write_queue_size != 0)
    return UV_EAGAIN;

  has_pollout = uv__io_active(&stream->io_watcher, POLLOUT);

  r = uv_write(&req, stream, bufs, nbufs, uv_try_write_cb);
  if (r != 0)
    return r;

  /* Remove not written bytes from write queue size */
  written = uv__count_bufs(bufs, nbufs);
  if (req.bufs != NULL)
    req_size = uv__write_req_size(&req);
  else
    req_size = 0;
  written -= req_size;
  stream->write_queue_size -= req_size;

  /* Unqueue request, regardless of immediateness */
  QUEUE_REMOVE(&req.queue);
  uv__req_unregister(stream->loop, &req);
  if (req.bufs != req.bufsml)
    uv__free(req.bufs);
  req.bufs = NULL;

  /* Do not poll for writable, if we wasn't before calling this */
  if (!has_pollout) {
    uv__io_stop(stream->loop, &stream->io_watcher, POLLOUT);
    uv__stream_osx_interrupt_select(stream);
  }

  if (written == 0 && req_size != 0)
    return req.error < 0 ? req.error : UV_EAGAIN;
  else
    return written;
}