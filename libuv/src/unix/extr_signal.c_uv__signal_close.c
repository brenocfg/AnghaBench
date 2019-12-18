#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ caught_signals; scalar_t__ dispatched_signals; } ;
typedef  TYPE_1__ uv_signal_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  uv__make_close_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv__signal_stop (TYPE_1__*) ; 

void uv__signal_close(uv_signal_t* handle) {

  uv__signal_stop(handle);

  /* If there are any caught signals "trapped" in the signal pipe, we can't
   * call the close callback yet. Otherwise, add the handle to the finish_close
   * queue.
   */
  if (handle->caught_signals == handle->dispatched_signals) {
    uv__make_close_pending((uv_handle_t*) handle);
  }
}