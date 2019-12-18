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
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  pthread_attr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,void* (*) (void*),void*) ; 

int
testf_dso_pthread_create(pthread_t *thread, const pthread_attr_t *attr, 
    void *(*routine)(void *), void *arg)
{
	int ret;

	ret = pthread_create(thread, attr, routine, arg);
	ATF_REQUIRE(ret == 0);

	return 0;
}