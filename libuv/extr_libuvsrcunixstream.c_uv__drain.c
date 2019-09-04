#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int flags; int /*<<< orphan*/  loop; TYPE_2__* shutdown_req; int /*<<< orphan*/  io_watcher; int /*<<< orphan*/  write_queue; } ;
typedef  TYPE_1__ uv_stream_t ;
struct TYPE_11__ {int /*<<< orphan*/  (* cb ) (TYPE_2__*,int) ;} ;
typedef  TYPE_2__ uv_shutdown_t ;

/* Variables and functions */
 int /*<<< orphan*/  POLLOUT ; 
 TYPE_2__* QUEUE_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHUT_WR ; 
 int UV_HANDLE_CLOSING ; 
 int UV_HANDLE_SHUT ; 
 int UV_HANDLE_SHUTTING ; 
 int UV__ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ shutdown (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int) ; 
 int /*<<< orphan*/  uv__io_stop (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv__req_unregister (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  uv__stream_fd (TYPE_1__*) ; 
 int /*<<< orphan*/  uv__stream_osx_interrupt_select (TYPE_1__*) ; 

__attribute__((used)) static void uv__drain(uv_stream_t* stream) {
  uv_shutdown_t* req;
  int err;

  assert(QUEUE_EMPTY(&stream->write_queue));
  uv__io_stop(stream->loop, &stream->io_watcher, POLLOUT);
  uv__stream_osx_interrupt_select(stream);

  /* Shutdown? */
  if ((stream->flags & UV_HANDLE_SHUTTING) &&
      !(stream->flags & UV_HANDLE_CLOSING) &&
      !(stream->flags & UV_HANDLE_SHUT)) {
    assert(stream->shutdown_req);

    req = stream->shutdown_req;
    stream->shutdown_req = NULL;
    stream->flags &= ~UV_HANDLE_SHUTTING;
    uv__req_unregister(stream->loop, req);

    err = 0;
    if (shutdown(uv__stream_fd(stream), SHUT_WR))
      err = UV__ERR(errno);

    if (err == 0)
      stream->flags |= UV_HANDLE_SHUT;

    if (req->cb != NULL)
      req->cb(req, err);
  }
}