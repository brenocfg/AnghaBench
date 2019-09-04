#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* cf_state; int /*<<< orphan*/  cf_mutex; int /*<<< orphan*/  cf_signals; } ;
typedef  TYPE_1__ uv_loop_t ;
typedef  int /*<<< orphan*/  uv_fs_event_t ;
struct TYPE_7__ {int /*<<< orphan*/  loop; int /*<<< orphan*/  signal_source; } ;
typedef  TYPE_2__ uv__cf_loop_state_t ;
typedef  int /*<<< orphan*/  uv__cf_loop_signal_type_t ;
struct TYPE_8__ {int /*<<< orphan*/  member; int /*<<< orphan*/  type; int /*<<< orphan*/ * handle; } ;
typedef  TYPE_3__ uv__cf_loop_signal_t ;

/* Variables and functions */
 int /*<<< orphan*/  QUEUE_INSERT_TAIL (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int UV_ENOMEM ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pCFRunLoopSourceSignal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pCFRunLoopWakeUp (int /*<<< orphan*/ ) ; 
 TYPE_3__* uv__malloc (int) ; 
 int /*<<< orphan*/  uv_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_mutex_unlock (int /*<<< orphan*/ *) ; 

int uv__cf_loop_signal(uv_loop_t* loop,
                       uv_fs_event_t* handle,
                       uv__cf_loop_signal_type_t type) {
  uv__cf_loop_signal_t* item;
  uv__cf_loop_state_t* state;

  item = uv__malloc(sizeof(*item));
  if (item == NULL)
    return UV_ENOMEM;

  item->handle = handle;
  item->type = type;

  uv_mutex_lock(&loop->cf_mutex);
  QUEUE_INSERT_TAIL(&loop->cf_signals, &item->member);
  uv_mutex_unlock(&loop->cf_mutex);

  state = loop->cf_state;
  assert(state != NULL);
  pCFRunLoopSourceSignal(state->signal_source);
  pCFRunLoopWakeUp(state->loop);

  return 0;
}