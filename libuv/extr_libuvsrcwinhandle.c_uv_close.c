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
typedef  int /*<<< orphan*/  uv_udp_t ;
typedef  int /*<<< orphan*/  uv_tty_t ;
typedef  int /*<<< orphan*/  uv_timer_t ;
typedef  int /*<<< orphan*/  uv_tcp_t ;
typedef  int /*<<< orphan*/  uv_signal_t ;
typedef  int /*<<< orphan*/  uv_process_t ;
typedef  int /*<<< orphan*/  uv_prepare_t ;
typedef  int /*<<< orphan*/  uv_poll_t ;
typedef  int /*<<< orphan*/  uv_pipe_t ;
typedef  int /*<<< orphan*/  uv_loop_t ;
typedef  int /*<<< orphan*/  uv_idle_t ;
struct TYPE_5__ {int flags; int type; int /*<<< orphan*/  close_cb; int /*<<< orphan*/ * loop; } ;
typedef  TYPE_1__ uv_handle_t ;
typedef  int /*<<< orphan*/  uv_fs_poll_t ;
typedef  int /*<<< orphan*/  uv_fs_event_t ;
typedef  int /*<<< orphan*/  uv_close_cb ;
typedef  int /*<<< orphan*/  uv_check_t ;
typedef  int /*<<< orphan*/  uv_async_t ;

/* Variables and functions */
#define  UV_ASYNC 141 
#define  UV_CHECK 140 
#define  UV_FS_EVENT 139 
#define  UV_FS_POLL 138 
 int UV_HANDLE_CLOSING ; 
#define  UV_IDLE 137 
#define  UV_NAMED_PIPE 136 
#define  UV_POLL 135 
#define  UV_PREPARE 134 
#define  UV_PROCESS 133 
#define  UV_SIGNAL 132 
#define  UV_TCP 131 
#define  UV_TIMER 130 
#define  UV_TTY 129 
#define  UV_UDP 128 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv__fs_poll_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv__handle_closing (TYPE_1__*) ; 
 int /*<<< orphan*/  uv_async_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_check_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_fs_event_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_idle_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_pipe_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_poll_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_prepare_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_process_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_signal_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_tcp_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_timer_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_tty_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_udp_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_want_endgame (int /*<<< orphan*/ *,TYPE_1__*) ; 

void uv_close(uv_handle_t* handle, uv_close_cb cb) {
  uv_loop_t* loop = handle->loop;

  if (handle->flags & UV_HANDLE_CLOSING) {
    assert(0);
    return;
  }

  handle->close_cb = cb;

  /* Handle-specific close actions */
  switch (handle->type) {
    case UV_TCP:
      uv_tcp_close(loop, (uv_tcp_t*)handle);
      return;

    case UV_NAMED_PIPE:
      uv_pipe_close(loop, (uv_pipe_t*) handle);
      return;

    case UV_TTY:
      uv_tty_close((uv_tty_t*) handle);
      return;

    case UV_UDP:
      uv_udp_close(loop, (uv_udp_t*) handle);
      return;

    case UV_POLL:
      uv_poll_close(loop, (uv_poll_t*) handle);
      return;

    case UV_TIMER:
      uv_timer_stop((uv_timer_t*)handle);
      uv__handle_closing(handle);
      uv_want_endgame(loop, handle);
      return;

    case UV_PREPARE:
      uv_prepare_stop((uv_prepare_t*)handle);
      uv__handle_closing(handle);
      uv_want_endgame(loop, handle);
      return;

    case UV_CHECK:
      uv_check_stop((uv_check_t*)handle);
      uv__handle_closing(handle);
      uv_want_endgame(loop, handle);
      return;

    case UV_IDLE:
      uv_idle_stop((uv_idle_t*)handle);
      uv__handle_closing(handle);
      uv_want_endgame(loop, handle);
      return;

    case UV_ASYNC:
      uv_async_close(loop, (uv_async_t*) handle);
      return;

    case UV_SIGNAL:
      uv_signal_close(loop, (uv_signal_t*) handle);
      return;

    case UV_PROCESS:
      uv_process_close(loop, (uv_process_t*) handle);
      return;

    case UV_FS_EVENT:
      uv_fs_event_close(loop, (uv_fs_event_t*) handle);
      return;

    case UV_FS_POLL:
      uv__fs_poll_close((uv_fs_poll_t*) handle);
      uv__handle_closing(handle);
      return;

    default:
      /* Not supported */
      abort();
  }
}