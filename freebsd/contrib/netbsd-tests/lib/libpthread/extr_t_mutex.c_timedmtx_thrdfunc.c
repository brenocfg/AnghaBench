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
 int /*<<< orphan*/  ETIMEDOUT ; 
 int /*<<< orphan*/  PTHREAD_REQUIRE_STATUS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  ts_shortlived ; 

__attribute__((used)) static void *
timedmtx_thrdfunc(void *arg)
{
	printf("Before endeavor to reacquire timed-mutex (timeout expected)\n");
	PTHREAD_REQUIRE_STATUS(mutex_lock(&mutex, &ts_shortlived),
	    ETIMEDOUT);

	return NULL;
}