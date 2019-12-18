#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct deferred_test_data {int /*<<< orphan*/ * cbs; int /*<<< orphan*/  queue; } ;
typedef  int /*<<< orphan*/  THREAD_FN ;

/* Variables and functions */
 size_t CB_COUNT ; 
 int /*<<< orphan*/  SLEEP_MS (int) ; 
 int /*<<< orphan*/  THREAD_RETURN () ; 
 int /*<<< orphan*/  deferred_callback ; 
 int /*<<< orphan*/  event_deferred_cb_init_ (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_deferred_cb_schedule_ (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static THREAD_FN
load_deferred_queue(void *arg)
{
	struct deferred_test_data *data = arg;
	size_t i;

	for (i = 0; i < CB_COUNT; ++i) {
		event_deferred_cb_init_(&data->cbs[i], 0, deferred_callback,
		    NULL);
		event_deferred_cb_schedule_(data->queue, &data->cbs[i]);
		SLEEP_MS(1);
	}

	THREAD_RETURN();
}