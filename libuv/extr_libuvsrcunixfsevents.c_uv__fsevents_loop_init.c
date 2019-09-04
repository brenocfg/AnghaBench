#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  cf_mutex; int /*<<< orphan*/  cf_sem; TYPE_2__* cf_state; int /*<<< orphan*/  cf_thread; int /*<<< orphan*/  cf_signals; } ;
typedef  TYPE_1__ uv_loop_t ;
struct TYPE_11__ {int /*<<< orphan*/  fsevent_sem; int /*<<< orphan*/  fsevent_mutex; int /*<<< orphan*/ * signal_source; scalar_t__ fsevent_handle_count; scalar_t__ fsevent_need_reschedule; int /*<<< orphan*/  fsevent_handles; } ;
typedef  TYPE_2__ uv__cf_loop_state_t ;
typedef  int /*<<< orphan*/  pthread_attr_t ;
typedef  int /*<<< orphan*/  ctx ;
struct TYPE_12__ {int /*<<< orphan*/  perform; TYPE_1__* info; } ;
typedef  TYPE_3__ CFRunLoopSourceContext ;

/* Variables and functions */
 int PTHREAD_STACK_MIN ; 
 int /*<<< orphan*/  QUEUE_INIT (int /*<<< orphan*/ *) ; 
 int UV_ENOMEM ; 
 int UV__ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * pCFRunLoopSourceCreate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  pthread_attr_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_attr_init (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_attr_setstacksize (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_2__* uv__calloc (int,int) ; 
 int /*<<< orphan*/  uv__cf_loop_cb ; 
 int /*<<< orphan*/  uv__cf_loop_runner ; 
 int /*<<< orphan*/  uv__free (TYPE_2__*) ; 
 int uv__fsevents_global_init () ; 
 int /*<<< orphan*/  uv_mutex_destroy (int /*<<< orphan*/ *) ; 
 int uv_mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_sem_destroy (int /*<<< orphan*/ *) ; 
 int uv_sem_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_sem_wait (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int uv__fsevents_loop_init(uv_loop_t* loop) {
  CFRunLoopSourceContext ctx;
  uv__cf_loop_state_t* state;
  pthread_attr_t attr_storage;
  pthread_attr_t* attr;
  int err;

  if (loop->cf_state != NULL)
    return 0;

  err = uv__fsevents_global_init();
  if (err)
    return err;

  state = uv__calloc(1, sizeof(*state));
  if (state == NULL)
    return UV_ENOMEM;

  err = uv_mutex_init(&loop->cf_mutex);
  if (err)
    goto fail_mutex_init;

  err = uv_sem_init(&loop->cf_sem, 0);
  if (err)
    goto fail_sem_init;

  QUEUE_INIT(&loop->cf_signals);

  err = uv_sem_init(&state->fsevent_sem, 0);
  if (err)
    goto fail_fsevent_sem_init;

  err = uv_mutex_init(&state->fsevent_mutex);
  if (err)
    goto fail_fsevent_mutex_init;

  QUEUE_INIT(&state->fsevent_handles);
  state->fsevent_need_reschedule = 0;
  state->fsevent_handle_count = 0;

  memset(&ctx, 0, sizeof(ctx));
  ctx.info = loop;
  ctx.perform = uv__cf_loop_cb;
  state->signal_source = pCFRunLoopSourceCreate(NULL, 0, &ctx);
  if (state->signal_source == NULL) {
    err = UV_ENOMEM;
    goto fail_signal_source_create;
  }

  /* In the unlikely event that pthread_attr_init() fails, create the thread
   * with the default stack size. We'll use a little more address space but
   * that in itself is not a fatal error.
   */
  attr = &attr_storage;
  if (pthread_attr_init(attr))
    attr = NULL;

  if (attr != NULL)
    if (pthread_attr_setstacksize(attr, 4 * PTHREAD_STACK_MIN))
      abort();

  loop->cf_state = state;

  /* uv_thread_t is an alias for pthread_t. */
  err = UV__ERR(pthread_create(&loop->cf_thread, attr, uv__cf_loop_runner, loop));

  if (attr != NULL)
    pthread_attr_destroy(attr);

  if (err)
    goto fail_thread_create;

  /* Synchronize threads */
  uv_sem_wait(&loop->cf_sem);
  return 0;

fail_thread_create:
  loop->cf_state = NULL;

fail_signal_source_create:
  uv_mutex_destroy(&state->fsevent_mutex);

fail_fsevent_mutex_init:
  uv_sem_destroy(&state->fsevent_sem);

fail_fsevent_sem_init:
  uv_sem_destroy(&loop->cf_sem);

fail_sem_init:
  uv_mutex_destroy(&loop->cf_mutex);

fail_mutex_init:
  uv__free(state);
  return err;
}