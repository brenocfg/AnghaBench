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
struct TYPE_3__ {int /*<<< orphan*/  pack_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  counter_mutex ; 
 int /*<<< orphan*/  deepest_delta_mutex ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  key ; 
 int nr_threads ; 
 int /*<<< orphan*/  pthread_key_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_mutex ; 
 scalar_t__ show_stat ; 
 TYPE_1__* thread_data ; 
 scalar_t__ threads_active ; 
 int /*<<< orphan*/  type_cas_mutex ; 
 int /*<<< orphan*/  work_mutex ; 

__attribute__((used)) static void cleanup_thread(void)
{
	int i;
	if (!threads_active)
		return;
	threads_active = 0;
	pthread_mutex_destroy(&read_mutex);
	pthread_mutex_destroy(&counter_mutex);
	pthread_mutex_destroy(&work_mutex);
	pthread_mutex_destroy(&type_cas_mutex);
	if (show_stat)
		pthread_mutex_destroy(&deepest_delta_mutex);
	for (i = 0; i < nr_threads; i++)
		close(thread_data[i].pack_fd);
	pthread_key_delete(key);
	free(thread_data);
}