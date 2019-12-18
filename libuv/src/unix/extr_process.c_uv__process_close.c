#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* loop; int /*<<< orphan*/  queue; } ;
typedef  TYPE_2__ uv_process_t ;
struct TYPE_5__ {int /*<<< orphan*/  child_watcher; int /*<<< orphan*/  process_handles; } ;

/* Variables and functions */
 scalar_t__ QUEUE_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  QUEUE_REMOVE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv__handle_stop (TYPE_2__*) ; 
 int /*<<< orphan*/  uv_signal_stop (int /*<<< orphan*/ *) ; 

void uv__process_close(uv_process_t* handle) {
  QUEUE_REMOVE(&handle->queue);
  uv__handle_stop(handle);
  if (QUEUE_EMPTY(&handle->loop->process_handles))
    uv_signal_stop(&handle->loop->child_watcher);
}