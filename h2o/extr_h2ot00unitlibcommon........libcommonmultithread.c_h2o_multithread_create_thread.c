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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_fatal (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_strerror_r (int,char*,int) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,void* (*) (void*),void*) ; 

void h2o_multithread_create_thread(pthread_t *tid, const pthread_attr_t *attr, void *(*func)(void *), void *arg)
{
    int ret;
    if ((ret = pthread_create(tid, attr, func, arg)) != 0) {
        char buf[128];
        h2o_fatal("pthread_create: %s", h2o_strerror_r(ret, buf, sizeof(buf)));
    }
}