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
typedef  int /*<<< orphan*/  uv_stream_t ;
struct TYPE_5__ {int flags; int type; int /*<<< orphan*/  (* close_cb ) (TYPE_1__*) ;int /*<<< orphan*/  handle_queue; } ;
typedef  TYPE_1__ uv_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  QUEUE_REMOVE (int /*<<< orphan*/ *) ; 
#define  UV_ASYNC 141 
#define  UV_CHECK 140 
#define  UV_FS_EVENT 139 
#define  UV_FS_POLL 138 
 int UV_HANDLE_CLOSED ; 
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
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  uv__handle_unref (TYPE_1__*) ; 
 int /*<<< orphan*/  uv__stream_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv__udp_finish_close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void uv__finish_close(uv_handle_t* handle) {
  /* Note: while the handle is in the UV_HANDLE_CLOSING state now, it's still
   * possible for it to be active in the sense that uv__is_active() returns
   * true.
   *
   * A good example is when the user calls uv_shutdown(), immediately followed
   * by uv_close(). The handle is considered active at this point because the
   * completion of the shutdown req is still pending.
   */
  assert(handle->flags & UV_HANDLE_CLOSING);
  assert(!(handle->flags & UV_HANDLE_CLOSED));
  handle->flags |= UV_HANDLE_CLOSED;

  switch (handle->type) {
    case UV_PREPARE:
    case UV_CHECK:
    case UV_IDLE:
    case UV_ASYNC:
    case UV_TIMER:
    case UV_PROCESS:
    case UV_FS_EVENT:
    case UV_FS_POLL:
    case UV_POLL:
    case UV_SIGNAL:
      break;

    case UV_NAMED_PIPE:
    case UV_TCP:
    case UV_TTY:
      uv__stream_destroy((uv_stream_t*)handle);
      break;

    case UV_UDP:
      uv__udp_finish_close((uv_udp_t*)handle);
      break;

    default:
      assert(0);
      break;
  }

  uv__handle_unref(handle);
  QUEUE_REMOVE(&handle->handle_queue);

  if (handle->close_cb) {
    handle->close_cb(handle);
  }
}