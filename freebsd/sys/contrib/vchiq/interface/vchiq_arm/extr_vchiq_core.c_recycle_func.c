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
struct TYPE_4__ {TYPE_2__* local; } ;
typedef  TYPE_1__ VCHIQ_STATE_T ;
struct TYPE_5__ {int /*<<< orphan*/  recycle; } ;
typedef  TYPE_2__ VCHIQ_SHARED_STATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  process_free_queue (TYPE_1__*) ; 
 int /*<<< orphan*/  remote_event_wait (int /*<<< orphan*/ *) ; 

int
recycle_func(void *v)
{
	VCHIQ_STATE_T *state = (VCHIQ_STATE_T *) v;
	VCHIQ_SHARED_STATE_T *local = state->local;

	while (1) {
		remote_event_wait(&local->recycle);

		process_free_queue(state);
	}
	return 0;
}