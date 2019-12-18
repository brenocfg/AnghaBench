#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ signum; int flags; scalar_t__ dispatched_signals; scalar_t__ caught_signals; int /*<<< orphan*/  (* signal_cb ) (TYPE_1__*,scalar_t__) ;} ;
typedef  TYPE_1__ uv_signal_t ;
struct TYPE_9__ {int /*<<< orphan*/ * signal_pipefd; } ;
typedef  TYPE_2__ uv_loop_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;
struct TYPE_10__ {scalar_t__ signum; TYPE_1__* handle; } ;
typedef  TYPE_3__ uv__signal_msg_t ;
typedef  int /*<<< orphan*/  uv__io_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 scalar_t__ EWOULDBLOCK ; 
 int UV_HANDLE_CLOSING ; 
 int UV_SIGNAL_ONE_SHOT ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 
 int read (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  uv__handle_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  uv__make_close_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv__signal_stop (TYPE_1__*) ; 

__attribute__((used)) static void uv__signal_event(uv_loop_t* loop,
                             uv__io_t* w,
                             unsigned int events) {
  uv__signal_msg_t* msg;
  uv_signal_t* handle;
  char buf[sizeof(uv__signal_msg_t) * 32];
  size_t bytes, end, i;
  int r;

  bytes = 0;
  end = 0;

  do {
    r = read(loop->signal_pipefd[0], buf + bytes, sizeof(buf) - bytes);

    if (r == -1 && errno == EINTR)
      continue;

    if (r == -1 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
      /* If there are bytes in the buffer already (which really is extremely
       * unlikely if possible at all) we can't exit the function here. We'll
       * spin until more bytes are read instead.
       */
      if (bytes > 0)
        continue;

      /* Otherwise, there was nothing there. */
      return;
    }

    /* Other errors really should never happen. */
    if (r == -1)
      abort();

    bytes += r;

    /* `end` is rounded down to a multiple of sizeof(uv__signal_msg_t). */
    end = (bytes / sizeof(uv__signal_msg_t)) * sizeof(uv__signal_msg_t);

    for (i = 0; i < end; i += sizeof(uv__signal_msg_t)) {
      msg = (uv__signal_msg_t*) (buf + i);
      handle = msg->handle;

      if (msg->signum == handle->signum) {
        assert(!(handle->flags & UV_HANDLE_CLOSING));
        handle->signal_cb(handle, handle->signum);
      }

      handle->dispatched_signals++;

      if (handle->flags & UV_SIGNAL_ONE_SHOT)
        uv__signal_stop(handle);

      /* If uv_close was called while there were caught signals that were not
       * yet dispatched, the uv__finish_close was deferred. Make close pending
       * now if this has happened.
       */
      if (handle->caught_signals == handle->dispatched_signals) {
        if (handle->signum == 0)
          uv__handle_stop(handle);
        if (handle->flags & UV_HANDLE_CLOSING)
          uv__make_close_pending((uv_handle_t*) handle);
      }
    }

    bytes -= end;

    /* If there are any "partial" messages left, move them to the start of the
     * the buffer, and spin. This should not happen.
     */
    if (bytes) {
      memmove(buf, buf + end, bytes);
      continue;
    }
  } while (end == sizeof buf);
}