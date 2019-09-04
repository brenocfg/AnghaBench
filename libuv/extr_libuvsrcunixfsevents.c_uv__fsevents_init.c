#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uv_handle_t ;
struct TYPE_13__ {scalar_t__ realpath_len; TYPE_4__* realpath; TYPE_4__* cf_cb; int /*<<< orphan*/  cf_mutex; TYPE_3__* loop; int /*<<< orphan*/  cf_member; scalar_t__ cf_error; int /*<<< orphan*/  cf_events; int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ uv_fs_event_t ;
struct TYPE_14__ {int fsevent_need_reschedule; int /*<<< orphan*/  fsevent_mutex; int /*<<< orphan*/  fsevent_handle_count; int /*<<< orphan*/  fsevent_handles; } ;
typedef  TYPE_2__ uv__cf_loop_state_t ;
struct TYPE_16__ {int /*<<< orphan*/  flags; TYPE_1__* data; } ;
struct TYPE_15__ {TYPE_2__* cf_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  QUEUE_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  QUEUE_INSERT_TAIL (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int UV_ENOMEM ; 
 int /*<<< orphan*/  UV_HANDLE_INTERNAL ; 
 int UV__ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  kUVCFLoopSignalRegular ; 
 TYPE_4__* realpath (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (TYPE_4__*) ; 
 int uv__cf_loop_signal (TYPE_3__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv__free (TYPE_4__*) ; 
 int /*<<< orphan*/  uv__fsevents_cb ; 
 int uv__fsevents_loop_init (TYPE_3__*) ; 
 TYPE_4__* uv__malloc (int) ; 
 int /*<<< orphan*/  uv_async_init (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_mutex_destroy (int /*<<< orphan*/ *) ; 
 int uv_mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_unref (int /*<<< orphan*/ *) ; 

int uv__fsevents_init(uv_fs_event_t* handle) {
  int err;
  uv__cf_loop_state_t* state;

  err = uv__fsevents_loop_init(handle->loop);
  if (err)
    return err;

  /* Get absolute path to file */
  handle->realpath = realpath(handle->path, NULL);
  if (handle->realpath == NULL)
    return UV__ERR(errno);
  handle->realpath_len = strlen(handle->realpath);

  /* Initialize event queue */
  QUEUE_INIT(&handle->cf_events);
  handle->cf_error = 0;

  /*
   * Events will occur in other thread.
   * Initialize callback for getting them back into event loop's thread
   */
  handle->cf_cb = uv__malloc(sizeof(*handle->cf_cb));
  if (handle->cf_cb == NULL) {
    err = UV_ENOMEM;
    goto fail_cf_cb_malloc;
  }

  handle->cf_cb->data = handle;
  uv_async_init(handle->loop, handle->cf_cb, uv__fsevents_cb);
  handle->cf_cb->flags |= UV_HANDLE_INTERNAL;
  uv_unref((uv_handle_t*) handle->cf_cb);

  err = uv_mutex_init(&handle->cf_mutex);
  if (err)
    goto fail_cf_mutex_init;

  /* Insert handle into the list */
  state = handle->loop->cf_state;
  uv_mutex_lock(&state->fsevent_mutex);
  QUEUE_INSERT_TAIL(&state->fsevent_handles, &handle->cf_member);
  state->fsevent_handle_count++;
  state->fsevent_need_reschedule = 1;
  uv_mutex_unlock(&state->fsevent_mutex);

  /* Reschedule FSEventStream */
  assert(handle != NULL);
  err = uv__cf_loop_signal(handle->loop, handle, kUVCFLoopSignalRegular);
  if (err)
    goto fail_loop_signal;

  return 0;

fail_loop_signal:
  uv_mutex_destroy(&handle->cf_mutex);

fail_cf_mutex_init:
  uv__free(handle->cf_cb);
  handle->cf_cb = NULL;

fail_cf_cb_malloc:
  uv__free(handle->realpath);
  handle->realpath = NULL;
  handle->realpath_len = 0;

  return err;
}