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
struct TYPE_5__ {int flags; int /*<<< orphan*/ * alloc_cb; int /*<<< orphan*/ * read_cb; int /*<<< orphan*/  io_watcher; int /*<<< orphan*/  loop; } ;
typedef  TYPE_1__ uv_stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  POLLIN ; 
 int /*<<< orphan*/  POLLOUT ; 
 int UV_HANDLE_READING ; 
 int /*<<< orphan*/  uv__handle_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  uv__io_active (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv__io_stop (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv__stream_osx_interrupt_select (TYPE_1__*) ; 

int uv_read_stop(uv_stream_t* stream) {
  if (!(stream->flags & UV_HANDLE_READING))
    return 0;

  stream->flags &= ~UV_HANDLE_READING;
  uv__io_stop(stream->loop, &stream->io_watcher, POLLIN);
  if (!uv__io_active(&stream->io_watcher, POLLOUT))
    uv__handle_stop(stream);
  uv__stream_osx_interrupt_select(stream);

  stream->read_cb = NULL;
  stream->alloc_cb = NULL;
  return 0;
}