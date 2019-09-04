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
struct TYPE_3__ {int cf_error; int /*<<< orphan*/  cf_cb; int /*<<< orphan*/  cf_mutex; int /*<<< orphan*/  cf_events; } ;
typedef  TYPE_1__ uv_fs_event_t ;
typedef  int /*<<< orphan*/  QUEUE ;

/* Variables and functions */
 int /*<<< orphan*/  QUEUE_ADD (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  uv_async_send (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void uv__fsevents_push_event(uv_fs_event_t* handle,
                                    QUEUE* events,
                                    int err) {
  assert(events != NULL || err != 0);
  uv_mutex_lock(&handle->cf_mutex);

  /* Concatenate two queues */
  if (events != NULL)
    QUEUE_ADD(&handle->cf_events, events);

  /* Propagate error */
  if (err != 0)
    handle->cf_error = err;
  uv_mutex_unlock(&handle->cf_mutex);

  uv_async_send(handle->cf_cb);
}