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
typedef  int /*<<< orphan*/  uv_timer_t ;
typedef  int /*<<< orphan*/  uv_tcp_t ;
typedef  int /*<<< orphan*/  uv_stream_t ;
typedef  int /*<<< orphan*/  uv_signal_t ;
typedef  int /*<<< orphan*/  uv_process_t ;
typedef  int /*<<< orphan*/  uv_prepare_t ;
typedef  int /*<<< orphan*/  uv_poll_t ;
typedef  int /*<<< orphan*/  uv_pipe_t ;
typedef  int /*<<< orphan*/  uv_idle_t ;
struct TYPE_5__ {int type; int /*<<< orphan*/  close_cb; int /*<<< orphan*/  flags; } ;
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
 int /*<<< orphan*/  UV_HANDLE_CLOSING ; 
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
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  uv__async_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv__check_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv__fs_event_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv__fs_poll_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv__idle_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv__is_closing (TYPE_1__*) ; 
 int /*<<< orphan*/  uv__make_close_pending (TYPE_1__*) ; 
 int /*<<< orphan*/  uv__pipe_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv__poll_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv__prepare_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv__process_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv__signal_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv__stream_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv__tcp_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv__timer_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv__udp_close (int /*<<< orphan*/ *) ; 

void uv_close(uv_handle_t* handle, uv_close_cb close_cb) {
  assert(!uv__is_closing(handle));

  handle->flags |= UV_HANDLE_CLOSING;
  handle->close_cb = close_cb;

  switch (handle->type) {
  case UV_NAMED_PIPE:
    uv__pipe_close((uv_pipe_t*)handle);
    break;

  case UV_TTY:
    uv__stream_close((uv_stream_t*)handle);
    break;

  case UV_TCP:
    uv__tcp_close((uv_tcp_t*)handle);
    break;

  case UV_UDP:
    uv__udp_close((uv_udp_t*)handle);
    break;

  case UV_PREPARE:
    uv__prepare_close((uv_prepare_t*)handle);
    break;

  case UV_CHECK:
    uv__check_close((uv_check_t*)handle);
    break;

  case UV_IDLE:
    uv__idle_close((uv_idle_t*)handle);
    break;

  case UV_ASYNC:
    uv__async_close((uv_async_t*)handle);
    break;

  case UV_TIMER:
    uv__timer_close((uv_timer_t*)handle);
    break;

  case UV_PROCESS:
    uv__process_close((uv_process_t*)handle);
    break;

  case UV_FS_EVENT:
    uv__fs_event_close((uv_fs_event_t*)handle);
    break;

  case UV_POLL:
    uv__poll_close((uv_poll_t*)handle);
    break;

  case UV_FS_POLL:
    uv__fs_poll_close((uv_fs_poll_t*)handle);
    /* Poll handles use file system requests, and one of them may still be
     * running. The poll code will call uv__make_close_pending() for us. */
    return;

  case UV_SIGNAL:
    uv__signal_close((uv_signal_t*) handle);
    /* Signal handles may not be closed immediately. The signal code will
     * itself close uv__make_close_pending whenever appropriate. */
    return;

  default:
    assert(0);
  }

  uv__make_close_pending(handle);
}