#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int signum; int flags; void* signal_cb; } ;
typedef  TYPE_1__ uv_signal_t ;
typedef  void* uv_signal_cb ;
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  RB_INSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int UV_EINVAL ; 
 int UV_SIGNAL_ONE_SHOT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  uv__handle_start (TYPE_1__*) ; 
 int /*<<< orphan*/  uv__is_closing (TYPE_1__*) ; 
 int /*<<< orphan*/  uv__signal_block_and_lock (int /*<<< orphan*/ *) ; 
 TYPE_1__* uv__signal_first_handle (int) ; 
 int uv__signal_register_handler (int,int) ; 
 int /*<<< orphan*/  uv__signal_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  uv__signal_tree ; 
 int /*<<< orphan*/  uv__signal_tree_s ; 
 int /*<<< orphan*/  uv__signal_unlock_and_unblock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int uv__signal_start(uv_signal_t* handle,
                            uv_signal_cb signal_cb,
                            int signum,
                            int oneshot) {
  sigset_t saved_sigmask;
  int err;
  uv_signal_t* first_handle;

  assert(!uv__is_closing(handle));

  /* If the user supplies signum == 0, then return an error already. If the
   * signum is otherwise invalid then uv__signal_register will find out
   * eventually.
   */
  if (signum == 0)
    return UV_EINVAL;

  /* Short circuit: if the signal watcher is already watching {signum} don't
   * go through the process of deregistering and registering the handler.
   * Additionally, this avoids pending signals getting lost in the small
   * time frame that handle->signum == 0.
   */
  if (signum == handle->signum) {
    handle->signal_cb = signal_cb;
    return 0;
  }

  /* If the signal handler was already active, stop it first. */
  if (handle->signum != 0) {
    uv__signal_stop(handle);
  }

  uv__signal_block_and_lock(&saved_sigmask);

  /* If at this point there are no active signal watchers for this signum (in
   * any of the loops), it's time to try and register a handler for it here.
   * Also in case there's only one-shot handlers and a regular handler comes in.
   */
  first_handle = uv__signal_first_handle(signum);
  if (first_handle == NULL ||
      (!oneshot && (first_handle->flags & UV_SIGNAL_ONE_SHOT))) {
    err = uv__signal_register_handler(signum, oneshot);
    if (err) {
      /* Registering the signal handler failed. Must be an invalid signal. */
      uv__signal_unlock_and_unblock(&saved_sigmask);
      return err;
    }
  }

  handle->signum = signum;
  if (oneshot)
    handle->flags |= UV_SIGNAL_ONE_SHOT;

  RB_INSERT(uv__signal_tree_s, &uv__signal_tree, handle);

  uv__signal_unlock_and_unblock(&saved_sigmask);

  handle->signal_cb = signal_cb;
  uv__handle_start(handle);

  return 0;
}