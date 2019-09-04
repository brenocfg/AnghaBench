#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int flags; scalar_t__ write_queue_size; TYPE_5__* shutdown_req; int /*<<< orphan*/  loop; TYPE_5__* connect_req; int /*<<< orphan*/  io_watcher; } ;
typedef  TYPE_1__ uv_stream_t ;
struct TYPE_9__ {int /*<<< orphan*/  (* cb ) (TYPE_5__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int POLLIN ; 
 int POLLOUT ; 
 int /*<<< orphan*/  UV_ECANCELED ; 
 int UV_HANDLE_CLOSED ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv__io_active (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  uv__req_unregister (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  uv__stream_flush_write_queue (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv__write_callbacks (TYPE_1__*) ; 

void uv__stream_destroy(uv_stream_t* stream) {
  assert(!uv__io_active(&stream->io_watcher, POLLIN | POLLOUT));
  assert(stream->flags & UV_HANDLE_CLOSED);

  if (stream->connect_req) {
    uv__req_unregister(stream->loop, stream->connect_req);
    stream->connect_req->cb(stream->connect_req, UV_ECANCELED);
    stream->connect_req = NULL;
  }

  uv__stream_flush_write_queue(stream, UV_ECANCELED);
  uv__write_callbacks(stream);

  if (stream->shutdown_req) {
    /* The ECANCELED error code is a lie, the shutdown(2) syscall is a
     * fait accompli at this point. Maybe we should revisit this in v0.11.
     * A possible reason for leaving it unchanged is that it informs the
     * callee that the handle has been destroyed.
     */
    uv__req_unregister(stream->loop, stream->shutdown_req);
    stream->shutdown_req->cb(stream->shutdown_req, UV_ECANCELED);
    stream->shutdown_req = NULL;
  }

  assert(stream->write_queue_size == 0);
}