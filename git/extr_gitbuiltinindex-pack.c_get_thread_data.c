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
struct thread_local {int dummy; } ;

/* Variables and functions */
 scalar_t__ HAVE_THREADS ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key ; 
 struct thread_local nothread_data ; 
 struct thread_local* pthread_getspecific (int /*<<< orphan*/ ) ; 
 scalar_t__ threads_active ; 

__attribute__((used)) static inline struct thread_local *get_thread_data(void)
{
	if (HAVE_THREADS) {
		if (threads_active)
			return pthread_getspecific(key);
		assert(!threads_active &&
		       "This should only be reached when all threads are gone");
	}
	return &nothread_data;
}