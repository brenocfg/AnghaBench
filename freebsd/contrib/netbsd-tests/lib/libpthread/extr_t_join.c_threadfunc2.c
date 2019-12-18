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
typedef  int /*<<< orphan*/  pthread_attr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 uintptr_t STACKSIZE ; 
 int error ; 
 scalar_t__ pthread_attr_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_attr_get_np (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_attr_getstacksize (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  pthread_attr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_exit (void*) ; 
 int /*<<< orphan*/  pthread_self () ; 

__attribute__((used)) static void *
threadfunc2(void *arg)
{
	static uintptr_t i = 0;
	uintptr_t j;
	pthread_attr_t attr;
	size_t stacksize;

	j = (uintptr_t)arg;

#ifdef __FreeBSD__
	pthread_attr_init(&attr);
#endif
	ATF_REQUIRE(pthread_attr_get_np(pthread_self(), &attr) == 0);
	ATF_REQUIRE(pthread_attr_getstacksize(&attr, &stacksize) == 0);
	ATF_REQUIRE(stacksize == STACKSIZE * (j + 1));
	ATF_REQUIRE(pthread_attr_destroy(&attr) == 0);

	if (i++ == j)
		error = false;

	pthread_exit((void *)i);

	return NULL;
}