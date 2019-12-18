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
struct TYPE_6__ {int /*<<< orphan*/  (* read_cb ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ;int /*<<< orphan*/  io_watcher; int /*<<< orphan*/  loop; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ uv_stream_t ;
typedef  int /*<<< orphan*/  uv_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  POLLIN ; 
 int /*<<< orphan*/  POLLOUT ; 
 int /*<<< orphan*/  UV_EOF ; 
 int /*<<< orphan*/  UV_HANDLE_READING ; 
 int /*<<< orphan*/  UV_HANDLE_READ_EOF ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  uv__handle_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  uv__io_active (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv__io_stop (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv__stream_osx_interrupt_select (TYPE_1__*) ; 

__attribute__((used)) static void uv__stream_eof(uv_stream_t* stream, const uv_buf_t* buf) {
  stream->flags |= UV_HANDLE_READ_EOF;
  stream->flags &= ~UV_HANDLE_READING;
  uv__io_stop(stream->loop, &stream->io_watcher, POLLIN);
  if (!uv__io_active(&stream->io_watcher, POLLOUT))
    uv__handle_stop(stream);
  uv__stream_osx_interrupt_select(stream);
  stream->read_cb(stream, UV_EOF, buf);
}