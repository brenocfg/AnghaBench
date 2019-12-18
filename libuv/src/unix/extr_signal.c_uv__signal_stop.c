#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ signum; int flags; scalar_t__ caught_signals; scalar_t__ dispatched_signals; } ;
typedef  TYPE_1__ uv_signal_t ;
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 TYPE_1__* RB_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int UV_SIGNAL_ONE_SHOT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  uv__handle_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  uv__signal_block_and_lock (int /*<<< orphan*/ *) ; 
 TYPE_1__* uv__signal_first_handle (scalar_t__) ; 
 int uv__signal_register_handler (scalar_t__,int) ; 
 int /*<<< orphan*/  uv__signal_tree ; 
 int /*<<< orphan*/  uv__signal_tree_s ; 
 int /*<<< orphan*/  uv__signal_unlock_and_unblock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv__signal_unregister_handler (scalar_t__) ; 

__attribute__((used)) static void uv__signal_stop(uv_signal_t* handle) {
  uv_signal_t* removed_handle;
  sigset_t saved_sigmask;
  uv_signal_t* first_handle;
  int rem_oneshot;
  int first_oneshot;
  int ret;

  /* If the watcher wasn't started, this is a no-op. */
  if (handle->signum == 0)
    return;

  uv__signal_block_and_lock(&saved_sigmask);

  removed_handle = RB_REMOVE(uv__signal_tree_s, &uv__signal_tree, handle);
  assert(removed_handle == handle);
  (void) removed_handle;

  /* Check if there are other active signal watchers observing this signal. If
   * not, unregister the signal handler.
   */
  first_handle = uv__signal_first_handle(handle->signum);
  if (first_handle == NULL) {
    uv__signal_unregister_handler(handle->signum);
  } else {
    rem_oneshot = handle->flags & UV_SIGNAL_ONE_SHOT;
    first_oneshot = first_handle->flags & UV_SIGNAL_ONE_SHOT;
    if (first_oneshot && !rem_oneshot) {
      ret = uv__signal_register_handler(handle->signum, 1);
      assert(ret == 0);
    }
  }

  uv__signal_unlock_and_unblock(&saved_sigmask);

  handle->signum = 0;
  if (handle->caught_signals == handle->dispatched_signals)
    uv__handle_stop(handle);
}