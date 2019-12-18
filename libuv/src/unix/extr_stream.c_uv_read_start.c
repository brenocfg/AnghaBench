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
struct TYPE_6__ {scalar_t__ type; int flags; int alloc_cb; int /*<<< orphan*/  io_watcher; int /*<<< orphan*/  loop; int /*<<< orphan*/  read_cb; } ;
typedef  TYPE_1__ uv_stream_t ;
typedef  int /*<<< orphan*/  uv_read_cb ;
typedef  int uv_alloc_cb ;

/* Variables and functions */
 int /*<<< orphan*/  POLLIN ; 
 int UV_EINVAL ; 
 int UV_ENOTCONN ; 
 int UV_HANDLE_CLOSING ; 
 int UV_HANDLE_READABLE ; 
 int UV_HANDLE_READING ; 
 scalar_t__ UV_NAMED_PIPE ; 
 scalar_t__ UV_TCP ; 
 scalar_t__ UV_TTY ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  uv__handle_start (TYPE_1__*) ; 
 int /*<<< orphan*/  uv__io_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ uv__stream_fd (TYPE_1__*) ; 
 int /*<<< orphan*/  uv__stream_osx_interrupt_select (TYPE_1__*) ; 

int uv_read_start(uv_stream_t* stream,
                  uv_alloc_cb alloc_cb,
                  uv_read_cb read_cb) {
  assert(stream->type == UV_TCP || stream->type == UV_NAMED_PIPE ||
      stream->type == UV_TTY);

  if (stream->flags & UV_HANDLE_CLOSING)
    return UV_EINVAL;

  if (!(stream->flags & UV_HANDLE_READABLE))
    return UV_ENOTCONN;

  /* The UV_HANDLE_READING flag is irrelevant of the state of the tcp - it just
   * expresses the desired state of the user.
   */
  stream->flags |= UV_HANDLE_READING;

  /* TODO: try to do the read inline? */
  /* TODO: keep track of tcp state. If we've gotten a EOF then we should
   * not start the IO watcher.
   */
  assert(uv__stream_fd(stream) >= 0);
  assert(alloc_cb);

  stream->read_cb = read_cb;
  stream->alloc_cb = alloc_cb;

  uv__io_start(stream->loop, &stream->io_watcher, POLLIN);
  uv__handle_start(stream);
  uv__stream_osx_interrupt_select(stream);

  return 0;
}