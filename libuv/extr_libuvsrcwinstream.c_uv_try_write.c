#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uv_tty_t ;
typedef  int /*<<< orphan*/  uv_tcp_t ;
struct TYPE_3__ {int flags; int type; } ;
typedef  TYPE_1__ uv_stream_t ;
typedef  int /*<<< orphan*/  uv_buf_t ;

/* Variables and functions */
 int UV_EAGAIN ; 
 int UV_EBADF ; 
 int UV_ENOSYS ; 
 int UV_EPIPE ; 
 int UV_HANDLE_CLOSING ; 
 int UV_HANDLE_WRITABLE ; 
#define  UV_NAMED_PIPE 130 
#define  UV_TCP 129 
#define  UV_TTY 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int uv__tcp_try_write (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 
 int uv__tty_try_write (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 

int uv_try_write(uv_stream_t* stream,
                 const uv_buf_t bufs[],
                 unsigned int nbufs) {
  if (stream->flags & UV_HANDLE_CLOSING)
    return UV_EBADF;
  if (!(stream->flags & UV_HANDLE_WRITABLE))
    return UV_EPIPE;

  switch (stream->type) {
    case UV_TCP:
      return uv__tcp_try_write((uv_tcp_t*) stream, bufs, nbufs);
    case UV_TTY:
      return uv__tty_try_write((uv_tty_t*) stream, bufs, nbufs);
    case UV_NAMED_PIPE:
      return UV_EAGAIN;
    default:
      assert(0);
      return UV_ENOSYS;
  }
}