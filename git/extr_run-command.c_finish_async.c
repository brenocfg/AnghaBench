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
struct async {int /*<<< orphan*/  tid; int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ pthread_join (int /*<<< orphan*/ ,void**) ; 
 int wait_or_whine (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int finish_async(struct async *async)
{
#ifdef NO_PTHREADS
	return wait_or_whine(async->pid, "child process", 0);
#else
	void *ret = (void *)(intptr_t)(-1);

	if (pthread_join(async->tid, &ret))
		error("pthread_join failed");
	return (int)(intptr_t)ret;
#endif
}