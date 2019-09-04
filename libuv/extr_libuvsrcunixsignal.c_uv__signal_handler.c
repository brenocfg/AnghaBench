#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int signum; int /*<<< orphan*/  caught_signals; TYPE_1__* loop; } ;
typedef  TYPE_2__ uv_signal_t ;
struct TYPE_11__ {int signum; TYPE_2__* handle; } ;
typedef  TYPE_3__ uv__signal_msg_t ;
struct TYPE_9__ {int /*<<< orphan*/ * signal_pipefd; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINTR ; 
 int EWOULDBLOCK ; 
 TYPE_2__* RB_NEXT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int errno ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* uv__signal_first_handle (int) ; 
 scalar_t__ uv__signal_lock () ; 
 int /*<<< orphan*/  uv__signal_tree ; 
 int /*<<< orphan*/  uv__signal_tree_s ; 
 int /*<<< orphan*/  uv__signal_unlock () ; 
 int write (int /*<<< orphan*/ ,TYPE_3__*,int) ; 

__attribute__((used)) static void uv__signal_handler(int signum) {
  uv__signal_msg_t msg;
  uv_signal_t* handle;
  int saved_errno;

  saved_errno = errno;
  memset(&msg, 0, sizeof msg);

  if (uv__signal_lock()) {
    errno = saved_errno;
    return;
  }

  for (handle = uv__signal_first_handle(signum);
       handle != NULL && handle->signum == signum;
       handle = RB_NEXT(uv__signal_tree_s, &uv__signal_tree, handle)) {
    int r;

    msg.signum = signum;
    msg.handle = handle;

    /* write() should be atomic for small data chunks, so the entire message
     * should be written at once. In theory the pipe could become full, in
     * which case the user is out of luck.
     */
    do {
      r = write(handle->loop->signal_pipefd[1], &msg, sizeof msg);
    } while (r == -1 && errno == EINTR);

    assert(r == sizeof msg ||
           (r == -1 && (errno == EAGAIN || errno == EWOULDBLOCK)));

    if (r != -1)
      handle->caught_signals++;
  }

  uv__signal_unlock();
  errno = saved_errno;
}