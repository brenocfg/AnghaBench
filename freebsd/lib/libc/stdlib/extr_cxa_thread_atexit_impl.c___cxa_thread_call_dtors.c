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

/* Variables and functions */
 int CXA_DTORS_ITERATIONS ; 
 int /*<<< orphan*/  LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _pthread_self () ; 
 int /*<<< orphan*/  cxa_thread_walk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtors ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  walk_cb_call ; 
 int /*<<< orphan*/  walk_cb_nocall ; 

void
__cxa_thread_call_dtors(void)
{
	int i;

	for (i = 0; i < CXA_DTORS_ITERATIONS && !LIST_EMPTY(&dtors); i++)
		cxa_thread_walk(walk_cb_call);

	if (!LIST_EMPTY(&dtors)) {
		fprintf(stderr, "Thread %p is exiting with more "
		    "thread-specific dtors created after %d iterations "
		    "of destructor calls\n",
		    _pthread_self(), i);
		cxa_thread_walk(walk_cb_nocall);
	}
}