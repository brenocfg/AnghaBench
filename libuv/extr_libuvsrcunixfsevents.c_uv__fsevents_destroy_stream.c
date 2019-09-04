#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* cf_state; } ;
typedef  TYPE_1__ uv_loop_t ;
struct TYPE_5__ {int /*<<< orphan*/ * fsevent_stream; } ;
typedef  TYPE_2__ uv__cf_loop_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  pFSEventStreamInvalidate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pFSEventStreamRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pFSEventStreamStop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void uv__fsevents_destroy_stream(uv_loop_t* loop) {
  uv__cf_loop_state_t* state;

  state = loop->cf_state;

  if (state->fsevent_stream == NULL)
    return;

  /* Stop emitting events */
  pFSEventStreamStop(state->fsevent_stream);

  /* Release stream */
  pFSEventStreamInvalidate(state->fsevent_stream);
  pFSEventStreamRelease(state->fsevent_stream);
  state->fsevent_stream = NULL;
}