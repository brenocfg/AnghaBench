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
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int QUEUE_THREAD_COUNT ; 
 int /*<<< orphan*/  THREAD_START (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * deferred_data ; 
 int /*<<< orphan*/  load_deferred_queue ; 
 int /*<<< orphan*/ * load_threads ; 

__attribute__((used)) static void
start_threads_callback(evutil_socket_t fd, short what, void *arg)
{
	int i;

	for (i = 0; i < QUEUE_THREAD_COUNT; ++i) {
		THREAD_START(load_threads[i], load_deferred_queue,
				&deferred_data[i]);
	}
}