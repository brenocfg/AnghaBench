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
struct TYPE_3__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  counter_lock () ; 
 int /*<<< orphan*/  counter_unlock () ; 
 int /*<<< orphan*/  display_progress (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_delta_type (int /*<<< orphan*/ ) ; 
 size_t nr_dispatched ; 
 size_t nr_objects ; 
 int /*<<< orphan*/  nr_resolved_deltas ; 
 TYPE_1__* objects ; 
 int /*<<< orphan*/  progress ; 
 int /*<<< orphan*/  resolve_base (TYPE_1__*) ; 
 int /*<<< orphan*/  set_thread_data (void*) ; 
 int /*<<< orphan*/  work_lock () ; 
 int /*<<< orphan*/  work_unlock () ; 

__attribute__((used)) static void *threaded_second_pass(void *data)
{
	set_thread_data(data);
	for (;;) {
		int i;
		counter_lock();
		display_progress(progress, nr_resolved_deltas);
		counter_unlock();
		work_lock();
		while (nr_dispatched < nr_objects &&
		       is_delta_type(objects[nr_dispatched].type))
			nr_dispatched++;
		if (nr_dispatched >= nr_objects) {
			work_unlock();
			break;
		}
		i = nr_dispatched++;
		work_unlock();

		resolve_base(&objects[i]);
	}
	return NULL;
}